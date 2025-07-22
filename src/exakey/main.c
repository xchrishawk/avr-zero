/**
 * @file    main.c
 * @brief   Main entry point for the Exakey application.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <util/delay.h>

#include "bit_ops.h"
#include "gpio.h"

/* -- Macros -- */

#define D1      GPIO_PIN_ARDUINO_D13
#define D2      GPIO_PIN_ARDUINO_D12
#define D3      GPIO_PIN_ARDUINO_D11
#define D4      GPIO_PIN_ARDUINO_D10

#define S1      GPIO_PIN_ARDUINO_D15
#define S2      GPIO_PIN_ARDUINO_D16
#define S3      GPIO_PIN_ARDUINO_D17

#define ON      GPIO_STATE_LOW
#define OFF     GPIO_STATE_HIGH

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    gpio_set_dir( D1, GPIO_DIR_OUT );
    gpio_set_dir( D2, GPIO_DIR_OUT );
    gpio_set_dir( D3, GPIO_DIR_OUT );
    gpio_set_dir( D4, GPIO_DIR_OUT );

    gpio_set_dir( S1, GPIO_DIR_IN );
    gpio_set_dir( S2, GPIO_DIR_IN );
    gpio_set_dir( S3, GPIO_DIR_IN );

    gpio_set_state( D1, OFF );
    gpio_set_state( D2, OFF );
    gpio_set_state( D3, OFF );
    gpio_set_state( D4, OFF );

    while( true )
    {
        gpio_set_state( D1, gpio_get_state( S1 ) );
        gpio_set_state( D2, gpio_get_state( S2 ) );
        gpio_set_state( D3, gpio_get_state( S3 ) );
    }

} /* main() */
