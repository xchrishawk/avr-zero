/**
 * @file    main.c
 * @brief   Main entry point for the Exakey application.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "bit_ops.h"
#include "lcd1602a.h"

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    // Startup delay for LCD
    _delay_ms( 500 );

    // Initialize systems
    adc_init();
    lcd1602a_init();

    // Set voltage reference selection to AVcc and channel to A0
    adc_set_vref( ADC_VREF_AVCC );
    adc_set_channel( ADC_CHANNEL_A0 );

    // Enable the ADC
    adc_set_enabled( true );

    uint16_t count = 0;
    uint16_t result;
    char line1[ 6 ];
    char line2[ 6 ];

    lcd1602a_write_lines( "Convert ", NULL );

    while( true )
    {
        // Get value
        result = adc_read();

        // Print result to string
        sprintf( line1, "%-5u", count++ );
        sprintf( line2, "%-4u", result );

        // Update LCD
        lcd1602a_set_address( LCD1602A_ADDRESS_FIRST_LINE + 8 );
        lcd1602a_write_string( line1 );
        lcd1602a_set_address( LCD1602A_ADDRESS_SECOND_LINE );
        lcd1602a_write_string( line2 );
    }

} /* main() */
