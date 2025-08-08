/**
 * @file    main.c
 * @brief   Main module for the hw262_demo executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-07
 */

/* -- Includes -- */

#include <stdbool.h>

#include <util/delay.h>

#include "shields/hw262/hw262.h"

/* -- Procedures -- */

int main( void )
{
    hw262_init();

    hw262_led_t active_led = HW262_LED_D1;
    while( true )
    {
        if( hw262_button_get( HW262_BUTTON_S1 ) )
            active_led = ( active_led == 0 ? HW262_LED_COUNT - 1 : active_led - 1 );
        if( hw262_button_get( HW262_BUTTON_S3 ) )
            active_led = ( active_led == HW262_LED_COUNT - 1 ? 0 : active_led + 1 );
        if( hw262_button_get( HW262_BUTTON_S2 ) )
            active_led = 0;

        for( hw262_led_t led = 0; led < HW262_LED_COUNT; led++ )
            hw262_led_set( led, led == active_led );

        _delay_ms( 50 );
    }

} /* main() */
