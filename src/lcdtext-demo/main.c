/**
 * @file    main.c
 * @brief   Main module for the lcdtext-demo executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-09
 */

/* -- Includes -- */

#include <stdlib.h>

#include <util/delay.h>

#include "gpio/gpio.h"
#include "lcdtext/lcdtext.h"

/* -- Constants -- */

#define DELAY_MS        ( 2000 )

/* -- Procedure Prototypes -- */

/**
 * @fn      demo_autoshift( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of the autoshift options.
 */
static void demo_autoshift( lcdtext_t const * lcd );

/**
 * @fn      demo_clear_home( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of the home and clear functions.
 */
static void demo_clear_home( lcdtext_t const * lcd );

/**
 * @fn      demo_cursors( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of the available cursor options.
 */
static void demo_cursors( lcdtext_t const * lcd );

/**
 * @fn      demo_display_on_off( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of turning the display on and off.
 */
static void demo_display_on_off( lcdtext_t const * lcd );

/**
 * @fn      demo_set_address( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of setting the LCD's data address.
 */
static void demo_set_address( lcdtext_t const * lcd );

/**
 * @fn      demo_shift( lcdtext_t const * )
 * @brief   Displays an infinitely repeating demo of the LCD's display shift functions.
 */
static void demo_shift( lcdtext_t const * lcd );

/* -- Procedures -- */

int main( void )
{
    _delay_ms( 500 );

    lcdtext_t lcd = { 0 };

#if( 1 )
    // 8 line interface
    lcd.pins.rs             = GPIO_PIN_ARDUINO_D12;
    lcd.pins.rw             = GPIO_PIN_ARDUINO_D11;
    lcd.pins.e              = GPIO_PIN_ARDUINO_D10;
    lcd.pins.d0             = GPIO_PIN_ARDUINO_D02;
    lcd.pins.d1             = GPIO_PIN_ARDUINO_D03;
    lcd.pins.d2             = GPIO_PIN_ARDUINO_D04;
    lcd.pins.d3             = GPIO_PIN_ARDUINO_D05;
    lcd.pins.d4             = GPIO_PIN_ARDUINO_D06;
    lcd.pins.d5             = GPIO_PIN_ARDUINO_D07;
    lcd.pins.d6             = GPIO_PIN_ARDUINO_D08;
    lcd.pins.d7             = GPIO_PIN_ARDUINO_D09;
    lcd.config.data_8       = true;
    lcd.config.lines_2      = true;
    lcd.config.font_large   = false;
#else
    // 4 line interface
    lcd.pins.rs             = GPIO_PIN_ARDUINO_D12;
    lcd.pins.rw             = GPIO_PIN_ARDUINO_D11;
    lcd.pins.e              = GPIO_PIN_ARDUINO_D10;
    lcd.pins.d0             = GPIO_PIN_INVALID;
    lcd.pins.d1             = GPIO_PIN_INVALID;
    lcd.pins.d2             = GPIO_PIN_INVALID;
    lcd.pins.d3             = GPIO_PIN_INVALID;
    lcd.pins.d4             = GPIO_PIN_ARDUINO_D06;
    lcd.pins.d5             = GPIO_PIN_ARDUINO_D07;
    lcd.pins.d6             = GPIO_PIN_ARDUINO_D08;
    lcd.pins.d7             = GPIO_PIN_ARDUINO_D09;
    lcd.config.data_8       = false;
    lcd.config.lines_2      = true;
    lcd.config.font_large   = false;
#endif

    lcdtext_init( & lcd );

    // demo_autoshift( & lcd );
    // demo_clear_home( & lcd );
    demo_cursors( & lcd );
    // demo_display_on_off( & lcd );
    // demo_set_address( & lcd );
    // demo_shift( & lcd );

} /* main() */


static void demo_autoshift( lcdtext_t const * lcd )
{
    while( true )
    {
        static uint16_t const DELAY = 150;

        lcdtext_clear( lcd );
        lcdtext_set_autoshift( lcd, LCDTEXT_AUTOSHIFT_CURSOR_RIGHT );
        lcdtext_write_delay( lcd, "Cursor Right", DELAY );

        lcdtext_clear( lcd );
        lcdtext_set_address( lcd, 16 );
        lcdtext_set_autoshift( lcd, LCDTEXT_AUTOSHIFT_DISPLAY_LEFT );
        lcdtext_write_delay( lcd, "Display Left", DELAY );

        lcdtext_clear( lcd );
        lcdtext_set_address( lcd, 15 );
        lcdtext_set_autoshift( lcd, LCDTEXT_AUTOSHIFT_CURSOR_LEFT );
        lcdtext_write_delay( lcd, "Cursor Left", DELAY );

        lcdtext_clear( lcd );
        lcdtext_set_autoshift( lcd, LCDTEXT_AUTOSHIFT_DISPLAY_RIGHT );
        lcdtext_write_delay( lcd, "isplay Right", DELAY );
    }

} /* demo_autoshift() */


static void demo_clear_home( lcdtext_t const * lcd )
{
    while( true )
    {
        lcdtext_1602_write_lines( lcd, "XXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXX" );
        _delay_ms( DELAY_MS );

        lcdtext_home( lcd );
        lcdtext_write( lcd, "Called Home()" );
        _delay_ms( DELAY_MS );

        lcdtext_clear( lcd );
        lcdtext_write( lcd, "Called Clear()" );
        _delay_ms( DELAY_MS );
    }

} /* demo_clear_home() */


static void demo_cursors( lcdtext_t const * lcd )
{
    while( true )
    {
        lcdtext_clear( lcd );
        lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_NONE );
        lcdtext_1602_write_lines( lcd, "Cursor Demo", "No Cursor" );
        _delay_ms( DELAY_MS );

        lcdtext_clear( lcd );
        lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_UNDERSCORE );
        lcdtext_1602_write_lines( lcd, "Cursor Demo", "Underscore" );
        _delay_ms( DELAY_MS );

        lcdtext_clear( lcd );
        lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_BOX );
        lcdtext_1602_write_lines( lcd, "Cursor Demo", "Box" );
        _delay_ms( DELAY_MS );

        lcdtext_clear( lcd );
        lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_BOTH );
        lcdtext_1602_write_lines( lcd, "Cursor Demo", "Both" );
        _delay_ms( DELAY_MS );
    }

} /* demo_cursors() */


static void demo_display_on_off( lcdtext_t const * lcd )
{
    lcdtext_1602_write_lines( lcd, "Display Demo", "Toggle On/Off" );
    while( true )
    {
        lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_NONE );
        _delay_ms( DELAY_MS );

        lcdtext_set_display( lcd, false, LCDTEXT_CURSOR_NONE );
        _delay_ms( DELAY_MS );
    }

} /* demo_display_on_off() */


static void demo_set_address( lcdtext_t const * lcd )
{
    lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_NONE );
    while( true )
    {
        lcdtext_clear( lcd );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_1 + 0 );
        lcdtext_write( lcd, "0" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_2 + 0 );
        lcdtext_write( lcd, "1" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_1 + 1 );
        lcdtext_write( lcd, "2" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_2 + 1 );
        lcdtext_write( lcd, "3" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_1 + 2 );
        lcdtext_write( lcd, "4" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_2 + 2 );
        lcdtext_write( lcd, "5" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_1 + 3 );
        lcdtext_write( lcd, "6" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_2 + 3 );
        lcdtext_write( lcd, "7" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_1 + 4 );
        lcdtext_write( lcd, "8" ),
        _delay_ms( DELAY_MS );

        lcdtext_set_address( lcd, LCDTEXT_ADDRESS_LINE_2 + 4 );
        lcdtext_write( lcd, "9" ),
        _delay_ms( DELAY_MS );
    }

} /* demo_set_address() */


static void demo_shift( lcdtext_t const * lcd )
{
    lcdtext_set_display( lcd, true, LCDTEXT_CURSOR_NONE );
    lcdtext_1602_write_lines( lcd, "Shift Demo", "Shift Demo" );
    while( true )
    {
        for( uint8_t idx = 0; idx < 6; idx++ )
        {
            lcdtext_shift_right( lcd );
            _delay_ms( 500 );
        }
        for( uint8_t idx = 0; idx < 6; idx++ )
        {
            lcdtext_shift_left( lcd );
            _delay_ms( 500 );
        }
    }
} /* demo_shift() */
