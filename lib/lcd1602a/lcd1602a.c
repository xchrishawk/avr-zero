/**
 * @file    lcd1602a.c
 * @brief   Implementation for the LCD1602A driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-22
 */

/* -- Includes -- */

#include <string.h>

#include <util/delay.h>
#include <util/delay_basic.h>

#include "adc/adc.h"
#include "gpio/gpio.h"
#include "utility/utility.h"

#include "lcd1602a.h"

/* -- Types -- */

// Register to write to
typedef uint8_t register_t;
enum
{
    REGISTER_INSTRUCTION,
    REGISTER_DATA,
};

// Convenience typedef for configuration
typedef lcd1602a_cfg_t const* cfg_p;

/* -- Constants -- */

// Delays
#define DELAY_PULSE_ENABLE_LOOPS    1
#define DELAY_SHORT_US              50
#define DELAY_LONG_MS               2

// Maximum ADC readings for the buttons (empirically determined)
#define BUTTON_RIGHT_MAX_INPUT      45
#define BUTTON_UP_MAX_INPUT         178
#define BUTTON_DOWN_MAX_INPUT       333
#define BUTTON_LEFT_MAX_INPUT       525
#define BUTTON_SELECT_MAX_INPUT     832

/* -- Macros -- */

// Helper macro for data buffering functions
#define buffer_data_bit( _pin, _data, _bit ) \
    gpio_set_state( ( _pin ), ( ( _data ) & ( 1 << ( _bit ) ) ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW )

/* -- Procedure Prototypes -- */

/**
 * @fn      buffer_data_lo( uint8_t )
 * @brief   Sets the data bus to the low 4 bits of the specified byte.
 */
static void buffer_data_lo( cfg_p cfg, uint8_t data );

/**
 * @fn      buffer_data_hi( uint8_t )
 * @brief   Sets the data bus to the high 4 bits of the specified byte.
 */
static void buffer_data_hi( cfg_p cfg, uint8_t data );

/**
 * @fn      delay_long( void )
 * @brief   Executes a long (2 ms) delay.
 */
static void delay_long( void );

/**
 * @fn      delay_short( void )
 * @brief   Executes a short (50 us) delay.
 */
static void delay_short( void );

/**
 * @fn      pulse_enable( cfg_p )
 * @brief   Pulses the ENABLE line to the LCD, writing data.
 */
static void pulse_enable( cfg_p cfg );

/**
 * @fn      select_register( cfg_p, register_t )
 * @brief   Selects the specified register to write to.
 */
static void select_register( cfg_p cfg, register_t reg );

/**
 * @fn      send_byte( cfg_p, uint8_t )
 * @brief   Sends a full byte to the LCD over the data bus.
 */
static void send_byte( cfg_p cfg, uint8_t data );

/**
 * @fn      send_display_set( bool, bool, bool )
 * @brief   Sends the display set command with the specified parameters.
 * @param   cfg
 *          Pointer to the LCD configuration struct.
 * @param   display_on
 *          Set to `true` to turn on the entire display.
 * @param   cursor_underline_on
 *          Set to `true` to enable the underline cursor.
 * @param   cursor_blink_on
 *          Set to `true` to enable the blinking cursor.
 */
static void send_display_set( cfg_p cfg, bool display_on, bool cursor_underline_on, bool cursor_blink_on );

/**
 * @fn      send_entry_mode_set( bool, bool )
 * @brief   Sends the entry mode set command with the specified parameters.
 * @param   cfg
 *          Pointer to the LCD configuration struct.
 * @param   increment_addr
 *          Set to @c true to increment the address when data is written. Otherwise it will be decremented.
 * @param   auto_shift
 *          Set to @c true to automatically shift the entire display when a new character is entered.
 */
static void send_entry_mode_set( cfg_p cfg, bool increment_addr, bool auto_shift );

/**
 * @fn      send_function_set( bool, bool )
 * @brief   Sends the function set command with the specified parameters.
 * @param   cfg
 *          Pointer to the LCD configuration struct.
 * @param   two_line
 *          Set to @c true to enable two-line display mode.
 * @param   large_font
 *          Set to @c true to enable large (5x11) display mode.
 */
static void send_function_set( cfg_p cfg, bool two_line, bool large_font );

/* -- Procedures -- */

void lcd1602a_cfg_default( lcd1602a_cfg_t* cfg )
{
    // Clear struct
    memset( cfg, 0, sizeof( *cfg ) );

    // Assign GPIO pins
    cfg->d4_pin = GPIO_PIN_ARDUINO_D4;
    cfg->d5_pin = GPIO_PIN_ARDUINO_D5;
    cfg->d6_pin = GPIO_PIN_ARDUINO_D6;
    cfg->d7_pin = GPIO_PIN_ARDUINO_D7;
    cfg->rs_pin = GPIO_PIN_ARDUINO_D8;
    cfg->e_pin  = GPIO_PIN_ARDUINO_D9;

    // Assign ADC channels
    cfg->btn_chnl = ADC_CHANNEL_A0;

} /* lcd1602a_cfg_default() */


void lcd1602a_clear( lcd1602a_cfg_t const* cfg )
{
    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, 0x01 );
    delay_long();

} /* lcd1602a_clear() */


lcd1602a_button_t lcd1602a_get_button( lcd1602a_cfg_t const* cfg )
{
    adc_set_vref( ADC_VREF_AVCC );
    adc_set_channel( cfg->btn_chnl );
    uint16_t sample = adc_read();

    if( sample < BUTTON_RIGHT_MAX_INPUT )
        return LCD1602A_BUTTON_RIGHT;
    else if( sample < BUTTON_UP_MAX_INPUT )
        return LCD1602A_BUTTON_UP;
    else if( sample < BUTTON_DOWN_MAX_INPUT )
        return LCD1602A_BUTTON_DOWN;
    else if( sample < BUTTON_LEFT_MAX_INPUT )
        return LCD1602A_BUTTON_LEFT;
    else if( sample < BUTTON_SELECT_MAX_INPUT )
        return LCD1602A_BUTTON_SELECT;
    else
        return LCD1602A_BUTTON_NONE;

} /* lcd1602a_get_button() */


void lcd1602a_home( lcd1602a_cfg_t const* cfg )
{
    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, 0x02 );
    delay_long();

} /* lcd1602a_home() */


void lcd1602a_init( lcd1602a_cfg_t const* cfg )
{
    // Set configuration for all GPIO pins
    gpio_cfg_t const gpio_cfg = { GPIO_DIR_OUT, false };
    gpio_configure( cfg->d4_pin, &gpio_cfg );
    gpio_configure( cfg->d5_pin, &gpio_cfg );
    gpio_configure( cfg->d6_pin, &gpio_cfg );
    gpio_configure( cfg->d7_pin, &gpio_cfg );
    gpio_configure( cfg->rs_pin, &gpio_cfg );
    gpio_configure( cfg->e_pin,  &gpio_cfg );

    // Set initial state for all GPIO pins
    gpio_set_state( cfg->d4_pin, GPIO_STATE_LOW );
    gpio_set_state( cfg->d5_pin, GPIO_STATE_LOW );
    gpio_set_state( cfg->d6_pin, GPIO_STATE_LOW );
    gpio_set_state( cfg->d7_pin, GPIO_STATE_LOW );
    gpio_set_state( cfg->rs_pin, GPIO_STATE_LOW );
    gpio_set_state( cfg->e_pin,  GPIO_STATE_LOW );

    // Initialize and enable ADC if it's not already initialized
    adc_init();
    adc_set_enabled( true );

    // Send initialization commands
    send_function_set( cfg, true, false );
    send_display_set( cfg, true, false, false );
    send_entry_mode_set( cfg, true, false );

    // Clear any content on the LCD
    lcd1602a_clear( cfg );

} /* lcd1602a_init() */


void lcd1602a_init_default( lcd1602a_cfg_t* cfg )
{
    lcd1602a_cfg_default( cfg );
    lcd1602a_init( cfg );

} /* lcd1602a_init_default() */


void lcd1602a_set_address( lcd1602a_cfg_t const* cfg, uint8_t addr )
{
    uint8_t instruction = ( 0x80 | addr );

    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, instruction );
    delay_short();

} /* lcd1602a_set_address() */


void lcd1602a_write_char( lcd1602a_cfg_t const* cfg, char c )
{
    select_register( cfg, REGISTER_DATA );
    send_byte( cfg, ( uint8_t )c );
    delay_short();

} /* lcd1602a_write_char() */


void lcd1602a_write_lines( lcd1602a_cfg_t const* cfg, char const* s1, char const* s2 )
{
    lcd1602a_clear( cfg );

    // Write first line
    if( s1 )
    {
        lcd1602a_set_address( cfg, LCD1602A_ADDRESS_FIRST_LINE );
        lcd1602a_write_string( cfg, s1 );
    }

    // Write second line
    if( s2 )
    {
        lcd1602a_set_address( cfg, LCD1602A_ADDRESS_SECOND_LINE );
        lcd1602a_write_string( cfg, s2 );
    }

} /* lcd1602a_write_lines() */


void lcd1602a_write_string( lcd1602a_cfg_t const* cfg, char const* s )
{
    select_register( cfg, REGISTER_DATA );
    while( *s )
    {
        send_byte( cfg, ( uint8_t )*s );
        delay_short();
        s++;
    }

} /* lcd1602a_write_string() */


static void buffer_data_lo( cfg_p cfg, uint8_t data )
{
    // Low order 4 bits
    buffer_data_bit( cfg->d4_pin, data, 0 );
    buffer_data_bit( cfg->d5_pin, data, 1 );
    buffer_data_bit( cfg->d6_pin, data, 2 );
    buffer_data_bit( cfg->d7_pin, data, 3 );

} /* buffer_data_lo() */


static void buffer_data_hi( cfg_p cfg, uint8_t data )
{
    // High order 4 bits
    buffer_data_bit( cfg->d4_pin, data, 4 );
    buffer_data_bit( cfg->d5_pin, data, 5 );
    buffer_data_bit( cfg->d6_pin, data, 6 );
    buffer_data_bit( cfg->d7_pin, data, 7 );

} /* buffer_data_hi() */


static void delay_long( void )
{
    _delay_ms( DELAY_LONG_MS );

} /* delay_long() */


static void delay_short( void )
{
    _delay_us( DELAY_SHORT_US );

} /* delay_short() */


static void pulse_enable( cfg_p cfg )
{
    gpio_set_state( cfg->e_pin, GPIO_STATE_LOW );
    _delay_loop_1( DELAY_PULSE_ENABLE_LOOPS );
    gpio_set_state( cfg->e_pin, GPIO_STATE_HIGH );
    _delay_loop_1( DELAY_PULSE_ENABLE_LOOPS );
    gpio_set_state( cfg->e_pin, GPIO_STATE_LOW );

} /* pulse_enable() */


static void select_register( cfg_p cfg, register_t reg )
{
    gpio_set_state( cfg->rs_pin, ( reg == REGISTER_DATA ? GPIO_STATE_HIGH : GPIO_STATE_LOW ) );

} /* select_register() */


static void send_byte( cfg_p cfg, uint8_t data )
{
    buffer_data_hi( cfg, data );
    pulse_enable( cfg );

    buffer_data_lo( cfg, data );
    pulse_enable( cfg );

} /* send_byte() */


static void send_display_set( cfg_p cfg, bool display_on, bool cursor_underline_on, bool cursor_blink_on )
{
    uint8_t instruction = 0x08;
    if( display_on )
        instruction |= 0x04;
    if( cursor_underline_on )
        instruction |= 0x02;
    if( cursor_blink_on )
        instruction |= 0x01;

    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, instruction );
    delay_short();

} /* send_display_set() */


static void send_entry_mode_set( cfg_p cfg, bool increment_addr, bool auto_shift )
{
    uint8_t instruction = 0x04;
    if( increment_addr )
        instruction |= 0x02;
    if( auto_shift )
        instruction |= 0x01;

    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, instruction );
    delay_short();

} /* send_entry_mode_set() */


static void send_function_set( cfg_p cfg, bool two_line, bool large_font )
{
    uint8_t instruction = 0x20;
    if( two_line )
        instruction |= 0x08;
    if( large_font )
        instruction |= 0x04;

    select_register( cfg, REGISTER_INSTRUCTION );
    send_byte( cfg, instruction );
    delay_short();

} /* send_function_set() */
