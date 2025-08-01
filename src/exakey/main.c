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

#include "gpio/gpio.h"
#include "usart/usart.h"

/* -- Constants -- */

#define D1_PIN      GPIO_PIN_ARDUINO_D13
#define D2_PIN      GPIO_PIN_ARDUINO_D12
#define D3_PIN      GPIO_PIN_ARDUINO_D11
#define D4_PIN      GPIO_PIN_ARDUINO_D10
#define USART_PORT  USART_PORT_0
#define BUF_SZ      ( 256 )
#define NULL_CHAR   ( ( char )0 )

/* -- Macros -- */

#define SET_LED( _pin, _on )                                                    \
    gpio_set_state( _pin, _on ? GPIO_STATE_LOW : GPIO_STATE_HIGH )

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    static char buf[ BUF_SZ ];

    // Configure GPIO
    gpio_cfg_t gpio_cfg = { GPIO_DIR_OUT };
    gpio_configure( D1_PIN, &gpio_cfg );
    gpio_configure( D2_PIN, &gpio_cfg );
    gpio_configure( D3_PIN, &gpio_cfg );
    gpio_configure( D4_PIN, &gpio_cfg );

    // Initialize GPIO
    SET_LED( D1_PIN, false );
    SET_LED( D2_PIN, false );
    SET_LED( D3_PIN, false );
    SET_LED( D4_PIN, false );

    // Configure USART
    usart_autoconfigure_baud( USART_PORT );
    usart_set_data_bits( USART_PORT, USART_DATA_BITS_8 );
    usart_set_stop_bits( USART_PORT, USART_STOP_BITS_1 );
    usart_set_parity( USART_PORT, USART_PARITY_NONE );

    // Enable USART
    usart_set_rx_enabled( USART_PORT, true );
    usart_set_tx_enabled( USART_PORT, true );

    // Loop until the universe burns down
    while( true )
    {
        // Receive command and reply
        size_t count = usart_rx_until( USART_PORT, NULL_CHAR, buf, BUF_SZ );
        if( buf[ count - 1 ] == NULL_CHAR )
        {
            usart_tx_string( USART_PORT, "Received: " );
            usart_tx_string( USART_PORT, buf );
            usart_tx_string( USART_PORT, "\r\n" );

            if(      ! strcmp( buf, "on 1" ) )  SET_LED( D1_PIN, true );
            else if( ! strcmp( buf, "on 2" ) )  SET_LED( D2_PIN, true );
            else if( ! strcmp( buf, "on 3" ) )  SET_LED( D3_PIN, true );
            else if( ! strcmp( buf, "on 4" ) )  SET_LED( D4_PIN, true );
            else if( ! strcmp( buf, "off 1" ) ) SET_LED( D1_PIN, false );
            else if( ! strcmp( buf, "off 2" ) ) SET_LED( D2_PIN, false );
            else if( ! strcmp( buf, "off 3" ) ) SET_LED( D3_PIN, false );
            else if( ! strcmp( buf, "off 4" ) ) SET_LED( D4_PIN, false );
            else usart_tx_string( USART_PORT, "Invalid command!\r\n" );
        }
        else
        {
            usart_tx_string( USART_PORT, "Invalid command!\r\n" );
        }
    }

} /* main() */
