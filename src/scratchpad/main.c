/**
 * @file    main.c
 * @brief   Main module for the scratchpad executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-10
 */

/* -- Includes -- */

#include <stdio.h>
#include <string.h>

#include <util/delay.h>

#include "eeprom/eeprom.h"
#include "lcdtext/lcdtext.h"

/* -- Procedures -- */

int main( void )
{
    _delay_ms( 500 );

    // Initialize LCD
    lcdtext_t lcd = { 0 };
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
    lcdtext_init( & lcd );

    lcdtext_write( & lcd, "Hello" );

    // eeprom_write( 15, 0xEE );

    uint8_t result = eeprom_read( 15 );

    lcdtext_go_line_2( & lcd );
    char buf[ 16 ];
    sprintf( buf, "Read: %d", result );
    lcdtext_write( & lcd, buf );


} /* main() */
