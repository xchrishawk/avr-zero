/**
 * @file    main.c
 * @brief   Main module for the lcd1602-demo executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-09
 */

/* -- Includes -- */

#include <stdlib.h>

#include <util/delay.h>

#include "gpio/gpio.h"
#include "lcd1602/lcd1602.h"

/* -- Constants -- */

#define DELAY_MS        ( 2000 )

/* -- Procedure Prototypes -- */

/**
 * @fn      demo_autoshift( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of the autoshift options.
 */
static void demo_autoshift( lcd1602_t const * lcd );

/**
 * @fn      demo_clear_home( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of the home and clear functions.
 */
static void demo_clear_home( lcd1602_t const * lcd );

/**
 * @fn      demo_cursors( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of the available cursor options.
 */
static void demo_cursors( lcd1602_t const * lcd );

/**
 * @fn      demo_display_on_off( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of turning the display on and off.
 */
static void demo_display_on_off( lcd1602_t const * lcd );

/**
 * @fn      demo_set_address( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of setting the LCD's data address.
 */
static void demo_set_address( lcd1602_t const * lcd );

/**
 * @fn      demo_shift( lcd1602_t const * )
 * @brief   Displays an infinitely repeating demo of the LCD's display shift functions.
 */
static void demo_shift( lcd1602_t const * lcd );

/* -- Procedures -- */

int main( void )
{
    _delay_ms( 500 );

    lcd1602_t lcd = { 0 };

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

    lcd1602_init( & lcd );

    // demo_autoshift( & lcd );
    // demo_clear_home( & lcd );
    demo_cursors( & lcd );
    // demo_display_on_off( & lcd );
    // demo_set_address( & lcd );
    // demo_shift( & lcd );

} /* main() */


static void demo_autoshift( lcd1602_t const * lcd )
{
    while( true )
    {
        static uint16_t const DELAY = 150;

        lcd1602_clear( lcd );
        lcd1602_set_autoshift( lcd, LCD1602_AUTOSHIFT_CURSOR_RIGHT );
        lcd1602_write_delay( lcd, "Cursor Right", DELAY );

        lcd1602_clear( lcd );
        lcd1602_set_address( lcd, 16 );
        lcd1602_set_autoshift( lcd, LCD1602_AUTOSHIFT_DISPLAY_LEFT );
        lcd1602_write_delay( lcd, "Display Left", DELAY );

        lcd1602_clear( lcd );
        lcd1602_set_address( lcd, 15 );
        lcd1602_set_autoshift( lcd, LCD1602_AUTOSHIFT_CURSOR_LEFT );
        lcd1602_write_delay( lcd, "Cursor Left", DELAY );

        lcd1602_clear( lcd );
        lcd1602_set_autoshift( lcd, LCD1602_AUTOSHIFT_DISPLAY_RIGHT );
        lcd1602_write_delay( lcd, "isplay Right", DELAY );
    }

} /* demo_autoshift() */


static void demo_clear_home( lcd1602_t const * lcd )
{
    while( true )
    {
        lcd1602_write_lines( lcd, "XXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXX" );
        _delay_ms( DELAY_MS );

        lcd1602_home( lcd );
        lcd1602_write( lcd, "Called Home()" );
        _delay_ms( DELAY_MS );

        lcd1602_clear( lcd );
        lcd1602_write( lcd, "Called Clear()" );
        _delay_ms( DELAY_MS );
    }

} /* demo_clear_home() */


static void demo_cursors( lcd1602_t const * lcd )
{
    while( true )
    {
        lcd1602_clear( lcd );
        lcd1602_set_display( lcd, true, LCD1602_CURSOR_NONE );
        lcd1602_write_lines( lcd, "Cursor Demo", "No Cursor" );
        _delay_ms( DELAY_MS );

        lcd1602_clear( lcd );
        lcd1602_set_display( lcd, true, LCD1602_CURSOR_UNDERSCORE );
        lcd1602_write_lines( lcd, "Cursor Demo", "Underscore" );
        _delay_ms( DELAY_MS );

        lcd1602_clear( lcd );
        lcd1602_set_display( lcd, true, LCD1602_CURSOR_BOX );
        lcd1602_write_lines( lcd, "Cursor Demo", "Box" );
        _delay_ms( DELAY_MS );

        lcd1602_clear( lcd );
        lcd1602_set_display( lcd, true, LCD1602_CURSOR_BOTH );
        lcd1602_write_lines( lcd, "Cursor Demo", "Both" );
        _delay_ms( DELAY_MS );
    }

} /* demo_cursors() */


static void demo_display_on_off( lcd1602_t const * lcd )
{
    lcd1602_write_lines( lcd, "Display Demo", "Toggle On/Off" );
    while( true )
    {
        lcd1602_set_display( lcd, true, LCD1602_CURSOR_NONE );
        _delay_ms( DELAY_MS );

        lcd1602_set_display( lcd, false, LCD1602_CURSOR_NONE );
        _delay_ms( DELAY_MS );
    }

} /* demo_display_on_off() */


static void demo_set_address( lcd1602_t const * lcd )
{
    lcd1602_set_display( lcd, true, LCD1602_CURSOR_NONE );
    while( true )
    {
        lcd1602_clear( lcd );

        lcd1602_set_address( lcd, LCD1602_LINE_1_ADDRESS + 0 );
        lcd1602_write( lcd, "0" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_2_ADDRESS + 0 );
        lcd1602_write( lcd, "1" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_1_ADDRESS + 1 );
        lcd1602_write( lcd, "2" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_2_ADDRESS + 1 );
        lcd1602_write( lcd, "3" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_1_ADDRESS + 2 );
        lcd1602_write( lcd, "4" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_2_ADDRESS + 2 );
        lcd1602_write( lcd, "5" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_1_ADDRESS + 3 );
        lcd1602_write( lcd, "6" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_2_ADDRESS + 3 );
        lcd1602_write( lcd, "7" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_1_ADDRESS + 4 );
        lcd1602_write( lcd, "8" ),
        _delay_ms( DELAY_MS );

        lcd1602_set_address( lcd, LCD1602_LINE_2_ADDRESS + 4 );
        lcd1602_write( lcd, "9" ),
        _delay_ms( DELAY_MS );
    }

} /* demo_set_address() */


static void demo_shift( lcd1602_t const * lcd )
{
    lcd1602_set_display( lcd, true, LCD1602_CURSOR_NONE );
    lcd1602_write_lines( lcd, "Shift Demo", "Shift Demo" );
    while( true )
    {
        for( uint8_t idx = 0; idx < 6; idx++ )
        {
            lcd1602_shift_right( lcd );
            _delay_ms( 500 );
        }
        for( uint8_t idx = 0; idx < 6; idx++ )
        {
            lcd1602_shift_left( lcd );
            _delay_ms( 500 );
        }
    }
} /* demo_shift() */
