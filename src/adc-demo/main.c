/**
 * @file    main.c
 * @brief   Main module for the adc-demo executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-10
 */

/* -- Includes -- */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/interrupt.h>
#include <util/delay.h>

#include "adc/adc.h"
#include "lcdtext/lcdtext.h"
#include "zero/utility.h"

/* -- Variables -- */

// LCD struct
static lcdtext_t s_lcd;
#define lcd ( ( lcdtext_t const * ) & s_lcd )

// Most recent converted value
static uint16_t value = 0;

/* -- Procedure Prototypes -- */

static void init_lcd( void );

/* -- Procedures -- */

int main( void )
{
    // Initialize and configure LCD
    init_lcd();

    // Print a hello message
    lcdtext_write( lcd, "ADC Demo" );

    // Initialize and configure ADC
    adc_init();
    adc_set_vref( ADC_VREF_AVCC );
    adc_set_channel( ADC_CHANNEL_ARDUINO_A0 );
    adc_set_autotrigger_type( ADC_AUTOTRIGGER_FREE_RUN );
    adc_set_autotrigger_enabled( true );
    adc_set_interrupt_enabled( true );

    // Enable interrupts
    sei();

    // Trigger a conversion to start free running mode
    adc_set_enabled( true );
    adc_start();

    // Main loop
    char buf[ LCDTEXT_2004_LINE_LENGTH + 1 ];
    while( true )
    {
        // Delay some reasonable value
        _delay_ms( 50 );

        // Get copy of value
        cli();
        uint16_t value_copy = value;
        sei();

        // Print to the LCD
        sprintf( buf, "%-" stringize_value( LCDTEXT_2004_LINE_LENGTH ) "d", value );
        lcdtext_set_address( lcd, LCDTEXT_LINE_2_ADDRESS );
        lcdtext_write( lcd, buf );
    }

} /* main() */


static void init_lcd( void )
{
    // Set configuration
    s_lcd.config.data_8     = true;
    s_lcd.config.lines_2    = true;
    s_lcd.config.font_large = false;

    // Set pinout
    s_lcd.pins.rs           = GPIO_PIN_ARDUINO_D12;
    s_lcd.pins.rw           = GPIO_PIN_ARDUINO_D11;
    s_lcd.pins.e            = GPIO_PIN_ARDUINO_D10;
    s_lcd.pins.d0           = GPIO_PIN_ARDUINO_D02;
    s_lcd.pins.d1           = GPIO_PIN_ARDUINO_D03;
    s_lcd.pins.d2           = GPIO_PIN_ARDUINO_D04;
    s_lcd.pins.d3           = GPIO_PIN_ARDUINO_D05;
    s_lcd.pins.d4           = GPIO_PIN_ARDUINO_D06;
    s_lcd.pins.d5           = GPIO_PIN_ARDUINO_D07;
    s_lcd.pins.d6           = GPIO_PIN_ARDUINO_D08;
    s_lcd.pins.d7           = GPIO_PIN_ARDUINO_D09;

    // Initialize LCD
    lcdtext_init( & s_lcd );

} /* init_lcd() */


ISR( ADC_vect )
{
    value = adc_get();

} /* ISR( ADC_vect ) */
