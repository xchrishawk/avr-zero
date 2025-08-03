/**
 * @file    com.c
 * @brief   Implementation for the serial communication module.
 *
 * @author  Chris Vig
 * @date    2025-08-03
 */

/* -- Includes -- */

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <avr/interrupt.h>

#include "usart/usart.h"

#include "com.h"
#include "event.h"

/* -- Constants -- */

#define BUF_SIZE    ( 64 )
#define TERMINATOR  ( ( char )13 )
#define PORT        ( USART_PORT_0 )

/* -- Variables -- */

// Receive buffer
char        s_rx_buf[ BUF_SIZE ];
uint8_t     s_rx_cnt = 0;

// Transmit buffer
char        s_tx_buf[ BUF_SIZE ];
uint8_t     s_tx_idx = 0;

/* -- Procedures -- */

void com_init( void )
{
    // Initialize USART hardware
    usart_autoconfigure_baud( PORT );
    usart_set_data_bits( PORT, USART_DATA_BITS_8 );
    usart_set_stop_bits( PORT, USART_STOP_BITS_1 );
    usart_set_parity( PORT, USART_PARITY_NONE );

    // Enable USART
    usart_set_tx_enabled( PORT, true );
    usart_set_rx_enabled( PORT, true );

    // Enable interrupt for RX complete
    usart_set_rx_complete_interrupt_enabled( PORT, true );

} /* com_init() */


com_rx_status_t com_rx( char* buf, size_t buf_sz )
{
    if( // We have received at least one character
        s_rx_cnt > 0 &&
        // The received characters fit into the buffer provided by the caller
        s_rx_cnt < buf_sz &&
        // The most recently received character was the terminator
        s_rx_buf[ s_rx_cnt - 1 ] == TERMINATOR )
    {
        // Complete, properly terminated input has been received
        // Copy to output buffer, replacing the terminator character with a null
        memcpy( buf, s_rx_buf, s_rx_cnt );
        buf[ s_rx_cnt - 1 ] = '\0';
        s_rx_cnt = 0;
        return( COM_RX_STATUS_OK );
    }
    else if( s_rx_cnt == BUF_SIZE )
    {
        // Buffer overflowed before receiving terminating char
        // Reset the buffer and return an error code
        s_rx_cnt = 0;
        return( COM_RX_STATUS_OVERFLOW );
    }
    else
    {
        // Receiving characters, but no terminator received yet, and still room in buffer
        return( COM_RX_STATUS_WAIT );
    }

} /* com_rx() */


void com_tx( char const* buf )
{
    // Copy string into the transmit buffer
    strncpy( s_tx_buf, buf, BUF_SIZE );
    s_tx_idx = 0;

    // Enable the data register empty interrupt, which will fire immediately
    usart_set_data_empty_interrupt_enabled( PORT, true );

} /* com_tx() */


void com_tx_fmt( char const* fmt, ... )
{
    // Copy string into the transmit buffer
    va_list args;
    va_start( args, fmt );
    vsnprintf( s_tx_buf, BUF_SIZE, fmt, args );
    s_tx_idx = 0;
    va_end( args );

    // Enable the data register empty interrupt, which will fire immediately
    usart_set_data_empty_interrupt_enabled( PORT, true );

} /* com_tx_fmt() */


ISR( USART_RX_vect )
{
    // Write to RX buffer if there's space remaining
    if( s_rx_cnt < BUF_SIZE )
        s_rx_buf[ s_rx_cnt++ ] = usart_read( PORT );
    else
        ( void )usart_read( PORT );

    // Trigger the COM_RX event
    event_set_pending( EVENT_COM_RX );

} /* ISR( USART_RX_vect ) */


ISR( USART_UDRE_vect )
{
    // Write to the data register if we still have data left
    if( s_tx_idx < BUF_SIZE && s_tx_buf[ s_tx_idx ] != '\0' )
        usart_write( PORT, ( uint8_t )s_tx_buf[ s_tx_idx++ ] );
    else
        usart_set_data_empty_interrupt_enabled( PORT, false );

} /* ISR( USART_UDRE_vect ) */
