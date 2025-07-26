/**
 * @file    lcd1602a.c
 * @brief   Implementation for the LCD1602A driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-22
 */

/* -- Includes -- */

#include <util/delay.h>
#include <util/delay_basic.h>

#include "gpio.h"
#include "lcd1602a.h"

/* -- Types -- */

// Register to write to
typedef uint8_t register_t;
enum
{
    REGISTER_INSTRUCTION,
    REGISTER_DATA,
};

/* -- Constants -- */

// Delays
#define DELAY_PULSE_ENABLE_LOOPS    ( 1 )
#define DELAY_SHORT_US              ( 50 )
#define DELAY_LONG_MS               ( 2 )

// GPIO aliases for LCD pins
#define LCD_D4                      GPIO_PIN_ARDUINO_D4
#define LCD_D5                      GPIO_PIN_ARDUINO_D5
#define LCD_D6                      GPIO_PIN_ARDUINO_D6
#define LCD_D7                      GPIO_PIN_ARDUINO_D7
#define LCD_RS                      GPIO_PIN_ARDUINO_D8
#define LCD_E                       GPIO_PIN_ARDUINO_D9

/* -- Macros -- */

// Helper macro for data buffering functions
#define buffer_data_bit( _pin, _data, _bit ) \
    gpio_set_state( ( _pin ), ( ( _data ) & ( 1 << ( _bit ) ) ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW )

/* -- Procedure Prototypes -- */

/**
 * @fn      buffer_data_lo( uint8_t )
 * @brief   Sets the data bus to the low 4 bits of the specified byte.
 */
static void buffer_data_lo( uint8_t data );

/**
 * @fn      buffer_data_hi( uint8_t )
 * @brief   Sets the data bus to the high 4 bits of the specified byte.
 */
static void buffer_data_hi( uint8_t data );

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
 * @fn      pulse_enable( void )
 * @brief   Pulses the ENABLE line to the LCD, writing data.
 */
static void pulse_enable( void );

/**
 * @fn      select_register( register_t )
 * @brief   Selects the specified register to write to.
 */
static void select_register( register_t reg );

/**
 * @fn      send_byte( uint8_t )
 * @brief   Sends a full byte to the LCD over the data bus.
 */
static void send_byte( uint8_t data );

/**
 * @fn      send_display_set( bool, bool, bool )
 * @brief   Sends the display set command with the specified parameters.
 * @param   display_on
 *          Set to @c true to turn on the entire display.
 * @param   cursor_underline_on
 *          Set to @c true to enable the underline cursor.
 * @param   cursor_blink_on
 *          Set to @c true to enable the blinking cursor.
 */
static void send_display_set( bool display_on, bool cursor_underline_on, bool cursor_blink_on );

/**
 * @fn      send_entry_mode_set( bool, bool )
 * @brief   Sends the entry mode set command with the specified parameters.
 * @param   increment_addr
 *          Set to @c true to increment the address when data is written. Otherwise it will be decremented.
 * @param   auto_shift
 *          Set to @c true to automatically shift the entire display when a new character is entered.
 */
static void send_entry_mode_set( bool increment_addr, bool auto_shift );

/**
 * @fn      send_function_set( bool, bool )
 * @brief   Sends the function set command with the specified parameters.
 * @param   two_line
 *          Set to @c true to enable two-line display mode.
 * @param   large_font
 *          Set to @c true to enable large (5x11) display mode.
 */
static void send_function_set( bool two_line, bool large_font );

/* -- Procedures -- */

void lcd1602a_clear( void )
{
    select_register( REGISTER_INSTRUCTION );
    send_byte( 0x01 );
    delay_long();

} /* lcd1602a_clear() */


void lcd1602a_init( void )
{
    // Set GPIO directions for all relevant pins
    gpio_set_dir( LCD_D4, GPIO_DIR_OUT );
    gpio_set_dir( LCD_D5, GPIO_DIR_OUT );
    gpio_set_dir( LCD_D6, GPIO_DIR_OUT );
    gpio_set_dir( LCD_D7, GPIO_DIR_OUT );
    gpio_set_dir( LCD_RS, GPIO_DIR_OUT );
    gpio_set_dir( LCD_E,  GPIO_DIR_OUT );

    // Initialize pin states
    gpio_set_state( LCD_D4, GPIO_STATE_LOW );
    gpio_set_state( LCD_D5, GPIO_STATE_LOW );
    gpio_set_state( LCD_D6, GPIO_STATE_LOW );
    gpio_set_state( LCD_D7, GPIO_STATE_LOW );
    gpio_set_state( LCD_RS, GPIO_STATE_LOW );
    gpio_set_state( LCD_E,  GPIO_STATE_LOW );

    // Send initialization commands
    send_function_set( true, false );
    send_display_set( true, false, false );
    send_entry_mode_set( true, false );

    // Clear any content on the LCD
    lcd1602a_clear();

} /* lcd1602a_init() */


void lcd1602a_set_address( uint8_t addr )
{
    uint8_t instruction = ( 0x80 | addr );

    select_register( REGISTER_INSTRUCTION );
    send_byte( instruction );
    delay_short();

} /* lcd1602a_set_address() */


void lcd1602a_write_char( char c )
{
    select_register( REGISTER_DATA );
    send_byte( ( uint8_t )c );
    delay_short();

} /* lcd1602a_write_char() */


void lcd1602a_write_lines( char const* s1, char const* s2 )
{
    lcd1602a_clear();

    // Write first line
    if( s1 )
    {
        lcd1602a_set_address( LCD1602A_ADDRESS_FIRST_LINE );
        lcd1602a_write_string( s1 );
    }

    // Write second line
    if( s2 )
    {
        lcd1602a_set_address( LCD1602A_ADDRESS_SECOND_LINE );
        lcd1602a_write_string( s2 );
    }

} /* lcd1602a_write_lines() */


void lcd1602a_write_string( char const* s )
{
    select_register( REGISTER_DATA );
    while( *s )
    {
        send_byte( ( uint8_t )*s );
        delay_short();
        s++;
    }

} /* lcd1602a_write_string() */


static void buffer_data_lo( uint8_t data )
{
    // Low order 4 bits
    buffer_data_bit( LCD_D4, data, 0 );
    buffer_data_bit( LCD_D5, data, 1 );
    buffer_data_bit( LCD_D6, data, 2 );
    buffer_data_bit( LCD_D7, data, 3 );

} /* buffer_data_lo() */


static void buffer_data_hi( uint8_t data )
{
    // High order 4 bits
    buffer_data_bit( LCD_D4, data, 4 );
    buffer_data_bit( LCD_D5, data, 5 );
    buffer_data_bit( LCD_D6, data, 6 );
    buffer_data_bit( LCD_D7, data, 7 );

} /* buffer_data_hi() */


static void delay_long( void )
{
    _delay_ms( DELAY_LONG_MS );

} /* delay_long() */


static void delay_short( void )
{
    _delay_us( DELAY_SHORT_US );

} /* delay_short() */


static void pulse_enable( void )
{
    gpio_set_state( LCD_E, GPIO_STATE_LOW );
    _delay_loop_1( DELAY_PULSE_ENABLE_LOOPS );
    gpio_set_state( LCD_E, GPIO_STATE_HIGH );
    _delay_loop_1( DELAY_PULSE_ENABLE_LOOPS );
    gpio_set_state( LCD_E, GPIO_STATE_LOW );

} /* pulse_enable() */


static void select_register( register_t reg )
{
    gpio_set_state( LCD_RS, ( reg == REGISTER_DATA ? GPIO_STATE_HIGH : GPIO_STATE_LOW ) );

} /* select_register() */


static void send_byte( uint8_t data )
{
    buffer_data_hi( data );
    pulse_enable();

    buffer_data_lo( data );
    pulse_enable();

} /* send_byte() */


static void send_display_set( bool display_on, bool cursor_underline_on, bool cursor_blink_on )
{
    uint8_t instruction = 0x08;
    if( display_on )
        instruction |= 0x04;
    if( cursor_underline_on )
        instruction |= 0x02;
    if( cursor_blink_on )
        instruction |= 0x01;

    select_register( REGISTER_INSTRUCTION );
    send_byte( instruction );
    delay_short();

} /* send_display_set() */


static void send_entry_mode_set( bool increment_addr, bool auto_shift )
{
    uint8_t instruction = 0x04;
    if( increment_addr )
        instruction |= 0x02;
    if( auto_shift )
        instruction |= 0x01;

    select_register( REGISTER_INSTRUCTION );
    send_byte( instruction );
    delay_short();

} /* send_entry_mode_set() */


static void send_function_set( bool two_line, bool large_font )
{
    uint8_t instruction = 0x20;
    if( two_line )
        instruction |= 0x08;
    if( large_font )
        instruction |= 0x04;

    select_register( REGISTER_INSTRUCTION );
    send_byte( instruction );
    delay_short();

} /* send_function_set() */
