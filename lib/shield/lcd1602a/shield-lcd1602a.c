/**
 * @file    shield-lcd1602a.c
 * @brief   Implementation for the shield-lcd1602a library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-16
 */

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

#include "adc/adc.h"
#include "lcdtext/lcdtext.h"

#include "shield-lcd1602a.h"

/* -- Variables -- */

static lcdtext_t lcd_struct;
#define lcd ( ( lcdtext_t const * ) & lcd_struct )

/* -- Procedures -- */

shield_lcd1602a_button_t shield_lcd1602a_get_button( void )
{
    adc_set_channel( ADC_CHANNEL_ARDUINO_A0 );
    uint16_t value = adc_read();
    if( value <= 60 )
        return( SHIELD_LCD1602A_BUTTON_RIGHT );
    else if( value <= 200 )
        return( SHIELD_LCD1602A_BUTTON_UP );
    else if( value <= 400 )
        return( SHIELD_LCD1602A_BUTTON_DOWN );
    else if( value <= 600 )
        return( SHIELD_LCD1602A_BUTTON_LEFT );
    else if( value <= 800 )
        return( SHIELD_LCD1602A_BUTTON_SELECT );
    else
        return( SHIELD_LCD1602A_BUTTON_NONE );

} /* shield_lcd1602a_get_button() */


void shield_lcd1602a_init( void )
{
    // Initialice LCD configuration
    lcd_struct.config.data_8        = false;
    lcd_struct.config.font_large    = false;
    lcd_struct.config.lines_2       = true;

    // Initialize LCD pinout
    lcd_struct.pins.rs              = GPIO_PIN_ARDUINO_D08;
    lcd_struct.pins.rw              = GPIO_PIN_INVALID;
    lcd_struct.pins.e               = GPIO_PIN_ARDUINO_D09;
    lcd_struct.pins.d0              = GPIO_PIN_INVALID;
    lcd_struct.pins.d1              = GPIO_PIN_INVALID;
    lcd_struct.pins.d2              = GPIO_PIN_INVALID;
    lcd_struct.pins.d3              = GPIO_PIN_INVALID;
    lcd_struct.pins.d4              = GPIO_PIN_ARDUINO_D04;
    lcd_struct.pins.d5              = GPIO_PIN_ARDUINO_D05;
    lcd_struct.pins.d6              = GPIO_PIN_ARDUINO_D06;
    lcd_struct.pins.d7              = GPIO_PIN_ARDUINO_D07;

    // Init LCD
    lcdtext_init( lcd );

    // Initialize ADC
    adc_init();
    adc_set_vref( ADC_VREF_AVCC );
    adc_set_enabled( true );

} /* shield_lcd1602a_init() */


lcdtext_t const * shield_lcd1602a_lcd( void )
{
    return( lcd );

} /* shield_lcd1602a_lcd() */
