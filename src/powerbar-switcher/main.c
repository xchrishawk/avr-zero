/**
 * @file    main.c
 * @brief   Main module for the powerbar switcher app.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-01
 */

/* -- Includes -- */

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart/usart.h"

#include "com.h"
#include "event.h"
#include "powerbar.h"

/* -- Constants -- */

#define INPUT_BUF_SIZE      32

static const uint32_t       TIMEOUT_MS = 10800000; // 3 hours in milliseconds

/* -- Procedure Prototypes -- */

/**
 * @fn      handle_com_rx( void )
 * @brief   Handles serial communication RX events.
 */
static void handle_com_rx( void );

/**
 * @fn      handle_tick( void )
 * @brief   Handles the 1 millisecond tick count timer.
 */
static void handle_tick( void );

/**
 * @fn      process_command( char const* )
 * @brief   Processes the specified command.
 */
static void process_command( char const* cmd );

/* -- Variables -- */

static bool s_timeout = true;

/* -- Procedures -- */

int main( void )
{
    // Initialize hardware
    com_init();
    powerbar_init();

    // Initialize event manager
    event_init();

    while( true )
    {
        event_t event = event_wait();
        switch( event )
        {
        case EVENT_TICK:
            handle_tick();
            break;

        case EVENT_COM_RX:
            handle_com_rx();
            break;

        default:
            assert( false );
            break;
        }
    }

} /* main() */


static void handle_com_rx( void )
{
    // Read status from com module
    static char input[ INPUT_BUF_SIZE ];
    com_rx_status_t status = com_rx( input, INPUT_BUF_SIZE );
    switch( status )
    {
    case COM_RX_STATUS_WAIT:
        // No action required
        break;

    case COM_RX_STATUS_OK:
        // Valid command!
        process_command( input );
        break;

    case COM_RX_STATUS_OVERFLOW:
        // RX buffer overflow!
        com_tx( "invalid command\r\n" );
        break;

    default:
        // ...??
        assert( false );
        break;
    }

} /* handle_com_rx() */


static void handle_tick( void )
{
    // Turn off the powerbar if the timeout has expired
    if( s_timeout && powerbar_get_enabled() && powerbar_get_uptime() > TIMEOUT_MS )
        powerbar_set_enabled( false );

} /* handle_tick() */


static void process_command( char const* cmd )
{
    // Helper macros
    #define send_power_state()                                                  \
        com_tx_fmt( "power: %s (%lu ms)\r\n",                                   \
                    powerbar_get_enabled() ? "on" : "off",                      \
                    powerbar_get_uptime() )
    #define send_timeout_state()                                                \
        com_tx_fmt( "timeout: %s (%lu ms)\r\n",                                 \
                    s_timeout ? "on" : "off",                                   \
                    TIMEOUT_MS )

    // Check against all known commands
    if( ! strcmp( cmd, "power" ) )
    {
        // Return current state
        send_power_state();
    }
    else if( ! strcmp( cmd, "power on" ) )
    {
        // Turn the power on
        powerbar_set_enabled( true );
        send_power_state();
    }
    else if( ! strcmp( cmd, "power off" ) )
    {
        // Turn the power off
        powerbar_set_enabled( false );
        send_power_state();
    }
    else if( ! strcmp( cmd, "timeout" ) )
    {
        send_timeout_state();
    }
    else if( ! strcmp( cmd, "timeout on" ) )
    {
        s_timeout = true;
        send_timeout_state();
    }
    else if( ! strcmp( cmd, "timeout off" ) )
    {
        s_timeout = false;
        send_timeout_state();
    }
    else
    {
        // ...??
        com_tx_fmt( "invalid command: %s\r\n", cmd );
    }

    // Cleanup
    #undef send_power_state
    #undef send_timeout_state

} /* process_command() */
