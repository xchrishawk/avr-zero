/**
 * @file    main.c
 * @brief   Main module for the powerbar switcher app.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-01
 */

/* -- Includes -- */

#include <stdbool.h>
#include <string.h>

#include <avr/interrupt.h>
#include <util/delay.h>

#include "gpio/gpio.h"
#include "usart/usart.h"

/* -- Constants -- */

#define PORT            USART_PORT_0
#define LED_PIN         GPIO_PIN_ARDUINO_BUILT_IN_LED
#define CTRL_PIN        GPIO_PIN_ARDUINO_D14

#define ON_CMD          'n'
#define OFF_CMD         'f'

/* -- Procedure Prototypes -- */

/**
 * @fn      set_power( bool )
 * @brief   Activates or deactivates the power.
 */
static void set_power( bool on );

/* -- Procedures -- */

int main( void )
{
    // Configure GPIO
    gpio_cfg_t cfg = { GPIO_DIR_OUT };
    gpio_configure( LED_PIN, &cfg );
    gpio_configure( CTRL_PIN, &cfg );

    // Initialize GPIO state
    set_power( false );

    // Configure USART
    usart_set_data_bits( PORT, USART_DATA_BITS_8 );
    usart_set_stop_bits( PORT, USART_STOP_BITS_1 );
    usart_set_parity( PORT, USART_PARITY_NONE );
    usart_autoconfigure_baud( PORT );

    // Enable USART
    usart_set_tx_enabled( PORT, true );
    usart_set_rx_enabled( PORT, true );

    // Enter main loop
    while( true )
    {
        // Receive message and execute command
        char c = ( char )usart_rx( PORT );
        switch( c )
        {
        case ON_CMD:
            set_power( true );
            usart_tx_string( PORT, "Power: ON\r\n" );
            break;

        case OFF_CMD:
            set_power( false );
            usart_tx_string( PORT, "Power: OFF\r\n" );
            break;

        default:
            usart_tx_string( PORT, "Invalid command: " );
            usart_tx( PORT, c );
            usart_tx_string( PORT, "\r\n" );
            break;
        }
    }

} /* main() */


static void set_power( bool on )
{
    gpio_set_state( LED_PIN,  on ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( CTRL_PIN, on ? GPIO_STATE_HIGH : GPIO_STATE_LOW );

} /* set_power_on() */
