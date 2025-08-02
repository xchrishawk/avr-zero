/**
 * @file    main.c
 * @brief   Main module for the blink executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-01
 */

/* -- Includes -- */

#include <stdbool.h>

#include <util/delay.h>

#include "gpio/gpio.h"

/* -- Constants -- */

#define DELAY   ( 100 )

/* -- Procedures -- */

int main( void )
{
    gpio_cfg_t cfg = { GPIO_DIR_OUT };
    gpio_configure( GPIO_PIN_ARDUINO_BUILT_IN_LED, &cfg );

    while( true )
    {
        gpio_set_state( GPIO_PIN_ARDUINO_BUILT_IN_LED, GPIO_STATE_HIGH );
        _delay_ms( DELAY );
        gpio_set_state( GPIO_PIN_ARDUINO_BUILT_IN_LED, GPIO_STATE_LOW );
        _delay_ms( DELAY );
    }

} /* main() */
