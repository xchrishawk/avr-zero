/**
 * @file    lcdtext.c
 * @brief   Implementation for the lcdtext library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-08
 */

/* -- Includes -- */

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "gpio/gpio.h"
#include "zero/bit_ops.h"
#include "zero/utility.h"

#include "lcdtext.h"

/* -- Types -- */

/**
 * @typedef lcd_p
 * @brief   Convenience typedef for a `const` pointer to a `lcdtext_t` struct.
 */
typedef lcdtext_t const * lcd_p;

/**
 * @typedef lcd_register_t
 * @brief   Enumeration of the supported registers.
 */
typedef uint8_t lcd_register_t;
enum
{
    LCD_REGISTER_INSTRUCTION,
    LCD_REGISTER_DATA,
};

/* -- Macros -- */

// Helper macros to validate arguments
#define validate_autoshift( _autoshift )    validate_enum( _autoshift,  LCDTEXT_AUTOSHIFT_COUNT )
#define validate_cursor( _cursor )          validate_enum( _cursor,     LCDTEXT_CURSOR_COUNT )

/* -- Procedure Prototypes -- */

/**
 * @fn      delay_long( void )
 * @brief   Performs a long synchronous delay.
 */
static void delay_long( void );

/**
 * @fn      delay_short( void )
 * @brief   Performs a short synchronous delay.
 */
static void delay_short( void );

/**
 * @fn      delay_variable( uint16_t )
 * @brief   Delays for a variable number of milliseconds.
 */
static void delay_variable( uint16_t delay_ms );

/**
 * @fn      select_register( lcd_p )
 * @brief   Selects the specified register.
 */
static void select_register( lcd_p lcd, lcd_register_t reg );

/**
 * @fn      send_data( lcd_p, uint8_t )
 * @brief   Sends the specified data byte to the LCD.
 */
static void send_data( lcd_p lcd, uint8_t data );

/**
 * @fn      send_function_select( lcd_p )
 * @brief   Sends the function select command to the LCD.
 */
static void send_function_select( lcd_p lcd );

/**
 * @fn      set_data_4bit_hi( lcd_p, uint8_t )
 * @brief   Sets the 4-bit data bus to the high 4 bits of `data`.
 */
static void set_data_4bit_hi( lcd_p lcd, uint8_t data );

/**
 * @fn      set_data_4bit_lo( lcd_p, uint8_t )
 * @brief   Sets the 4-bit data bus to the low 4 bits of `data`.
 */
static void set_data_4bit_lo( lcd_p lcd, uint8_t data );

/**
 * @fn      set_data_8bit( lcd_p, uint8_t )
 * @brief   Sets the 8-bit data bus to the content of `data`.
 */
static void set_data_8bit( lcd_p lcd, uint8_t data );

/**
 * @fn      strobe_enable( lcd_p )
 * @brief   Strobes the enable line for the LCD.
 */
static void strobe_enable( lcd_p lcd );

/* -- Procedures -- */

void lcdtext_clear( lcdtext_t const * lcd )
{
    static uint8_t const COMMAND = 0x01;

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, COMMAND );
    delay_long();

} /* lcdtext_clear() */


void lcdtext_home( lcdtext_t const * lcd )
{
    static uint8_t const COMMAND = 0x02;

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, COMMAND );
    delay_long();

} /* lcdtext_home() */


void lcdtext_init( lcdtext_t const * lcd )
{
    // Configure all GPIO pins
    gpio_config_t config = { GPIO_DIR_OUT, GPIO_STATE_LOW };
    for( uint8_t idx = 0; idx < LCDTEXT_PIN_COUNT; idx++ )
    {
        gpio_pin_t pin = lcd->pins.all[ idx ];
        if( pin != GPIO_PIN_INVALID )
            gpio_set_config( pin, & config );
    }

    // Send function set command to initialize LCD
    send_function_select( lcd );

    // Set LCD configuration to reasonable defaults
    lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_NONE );
    lcdtext_set_autoshift( lcd, LCDTEXT_AUTOSHIFT_CURSOR_RIGHT );

    // CLear any display contents
    lcdtext_clear( lcd );

} /* lcdtext_init() */


void lcdtext_set_address( lcdtext_t const * lcd, uint8_t addr )
{
    uint8_t command = 0x80 | ( 0x7F & addr );

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, command );
    delay_short();

} /* lcdtext_set_address() */


void lcdtext_set_autoshift( lcdtext_t const * lcd, lcdtext_autoshift_t autoshift )
{
    validate_autoshift( autoshift );

    uint8_t command = 0x04;
    switch( autoshift )
    {
    case LCDTEXT_AUTOSHIFT_CURSOR_RIGHT:
        command |= 0x02;
        break;
    case LCDTEXT_AUTOSHIFT_CURSOR_LEFT:
        break;
    case LCDTEXT_AUTOSHIFT_DISPLAY_RIGHT:
        command |= 0x01;
        break;
    case LCDTEXT_AUTOSHIFT_DISPLAY_LEFT:
        command |= 0x03;
        break;
    default:
        assert( false );
        return;
    }

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, command );
    delay_short();

} /* lcdtext_set_autoshift() */


void lcdtext_set_display( lcdtext_t const * lcd, bool display_on, lcdtext_cursor_t cursor )
{
    validate_cursor( cursor );

    uint8_t command = 0x08;
    assign_bit( command, 2, display_on );
    assign_bit( command, 1, cursor == LCDTEXT_CURSOR_UNDERSCORE || cursor == LCDTEXT_CURSOR_BOTH );
    assign_bit( command, 0, cursor == LCDTEXT_CURSOR_BOX        || cursor == LCDTEXT_CURSOR_BOTH );

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, command );
    delay_short();

} /* lcdtext_set_display() */


void lcdtext_shift_left( lcdtext_t const * lcd )
{
    static uint8_t const COMMAND = 0x18;

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, COMMAND );
    delay_short();

} /* lcdtext_shift_left() */


void lcdtext_shift_right( lcdtext_t const * lcd )
{
    static uint8_t const COMMAND = 0x1C;

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, COMMAND );
    delay_short();

} /* lcdtext_shift_right() */


void lcdtext_write( lcdtext_t const * lcd, char const * str )
{
    lcdtext_write_delay( lcd, str, 0 );

} /* lcdtext_write() */


void lcdtext_write_delay( lcdtext_t const * lcd, char const * str, uint16_t delay_ms )
{
    select_register( lcd, LCD_REGISTER_DATA );
    while( * str )
    {
        send_data( lcd, *( str++ ) );
        delay_short();
        delay_variable( delay_ms );
    }

} /* lcdtext_write_delay() */


void lcdtext_1602_write_lines( lcdtext_t const * lcd, char const * line1, char const * line2 )
{
    lcdtext_clear( lcd );
    if( line1 )
    {
        // Already at the correct position
        lcdtext_write( lcd, line1 );
    }
    if( line2 )
    {
        lcdtext_set_address( lcd, LCDTEXT_LINE_2_ADDRESS );
        lcdtext_write( lcd, line2 );
    }

} /* lcdtext_write_lines() */


static void delay_long( void )
{
    static const uint8_t DELAY_MS = 2;
    _delay_ms( DELAY_MS );

} /* delay_long() */


static void delay_short( void )
{
    static const uint8_t DELAY_US = 50;
    _delay_us( DELAY_US );

} /* delay_short() */


static void delay_variable( uint16_t delay_ms )
{
    uint16_t LOOPS_PER_MS = ( F_CPU / 4000UL );
    while( delay_ms -- )
        _delay_loop_2( LOOPS_PER_MS );

} /* delay_variable() */


static void select_register( lcd_p lcd, lcd_register_t reg )
{
    gpio_set_state( lcd->pins.rs, ( reg == LCD_REGISTER_DATA ? GPIO_STATE_HIGH : GPIO_STATE_LOW ) );

} /* select_register() */


void send_data( lcd_p lcd, uint8_t data )
{
    if( lcd->config.data_8 )
    {
        set_data_8bit( lcd, data );
        strobe_enable( lcd );
    }
    else
    {
        set_data_4bit_hi( lcd, data );
        strobe_enable( lcd );
        set_data_4bit_lo( lcd, data );
        strobe_enable( lcd );
    }

} /* send_data() */


static void send_function_select( lcd_p lcd )
{
    uint8_t command = 0x20;
    if( lcd->config.data_8 )
        set_bit( command, 4 );
    if( lcd->config.lines_2 )
        set_bit( command, 3 );
    if( lcd->config.font_large )
        set_bit( command, 2 );

    select_register( lcd, LCD_REGISTER_INSTRUCTION );
    send_data( lcd, command );
    delay_short();

} /* send_function_select() */


static void set_data_4bit_hi( lcd_p lcd, uint8_t data )
{
    gpio_set_state( lcd->pins.d4, is_bit_set( data, 4 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d5, is_bit_set( data, 5 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d6, is_bit_set( data, 6 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d7, is_bit_set( data, 7 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );

} /* set_data_4bit_hi() */


static void set_data_4bit_lo( lcd_p lcd, uint8_t data )
{
    gpio_set_state( lcd->pins.d4, is_bit_set( data, 0 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d5, is_bit_set( data, 1 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d6, is_bit_set( data, 2 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d7, is_bit_set( data, 3 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );

} /* set_data_4bit_lo() */


static void set_data_8bit( lcd_p lcd, uint8_t data )
{
    gpio_set_state( lcd->pins.d0, is_bit_set( data, 0 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d1, is_bit_set( data, 1 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d2, is_bit_set( data, 2 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d3, is_bit_set( data, 3 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d4, is_bit_set( data, 4 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d5, is_bit_set( data, 5 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d6, is_bit_set( data, 6 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( lcd->pins.d7, is_bit_set( data, 7 ) ? GPIO_STATE_HIGH : GPIO_STATE_LOW );

} /* set_data_8bit() */


static void strobe_enable( lcd_p lcd )
{
    static uint8_t const DELAY_LOOPS = 1;

    gpio_set_state( lcd->pins.e, GPIO_STATE_LOW );
    _delay_loop_1( DELAY_LOOPS );
    gpio_set_state( lcd->pins.e, GPIO_STATE_HIGH );
    _delay_loop_1( DELAY_LOOPS );
    gpio_set_state( lcd->pins.e, GPIO_STATE_LOW );

} /* strobe_enable() */
