/**
 * @file    usart.c
 * @brief   Implementation for the USART driver library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-31
 */

/* -- Includes -- */

#include <stdint.h>

#include <avr/io.h>
#include <util/setbaud.h>

#include "zero/bit_ops.h"
#include "zero/register.h"
#include "zero/utility.h"

#include "usart.h"

/* -- Macros -- */

// Helper macro for the register table below
#define DEFINE_REGISTERS( _port )                                              \
    { REGISTER_ADDR( UDR ## _port ),                                            \
      REGISTER_ADDR( UCSR ## _port ## A ),                                      \
      REGISTER_ADDR( UCSR ## _port ## B ),                                      \
      REGISTER_ADDR( UCSR ## _port ## C ),                                      \
      REGISTER_ADDR( UBRR ## _port ## H ),                                      \
      REGISTER_ADDR( UBRR ## _port ## L ) }

// Helper macros to get specific registers
#define PORT_UDR( _port )                                                       \
    ( * s_reg_tbl[ _port ].udr )
#define PORT_UCSRA( _port )                                                     \
    ( * s_reg_tbl[ _port ].ucsra )
#define PORT_UCSRB( _port )                                                     \
    ( * s_reg_tbl[ _port ].ucsrb )
#define PORT_UCSRC( _port )                                                     \
    ( * s_reg_tbl[ _port ].ucsrc )
#define PORT_UBRRH( _port )                                                     \
    ( * s_reg_tbl[ _port ].ubrrh )
#define PORT_UBRRL( _port )                                                     \
    ( * s_reg_tbl[ _port ].ubrrl )

/* -- Constants -- */

// Register lookup table for each USART port
static struct
{
    register_t  udr;
    register_t  ucsra;
    register_t  ucsrb;
    register_t  ucsrc;
    register_t  ubrrh;
    register_t  ubrrl;
}
const s_reg_tbl[] =
{
    DEFINE_REGISTERS( 0 )
};

// Ensure register table has an entry for every defined port
_Static_assert( array_count( s_reg_tbl ) == USART_PORT_COUNT, "s_reg_tbl must have correct number of entries!" );

/* -- Procedures -- */

void usart_autoconfigure_baud( usart_port_t port )
{
    PORT_UBRRH( port ) = UBRRH_VALUE;
    PORT_UBRRL( port ) = UBRRL_VALUE;
    #if( USE_2X )
        set_bit( PORT_UCSRA( port ), U2X0 );
    #else
        clear_bit( PORT_UCSRA( port ), U2X0 );
    #endif

} /* usart_autoconfigure_baud() */


bool usart_get_rx_enabled( usart_port_t port )
{
    return( ( bool )is_bit_set( PORT_UCSRB( port ), RXEN0 ) );

} /* usart_get_rx_enabled() */


bool usart_get_tx_enabled( usart_port_t port )
{
    return( ( bool )is_bit_set( PORT_UCSRB( port ), TXEN0 ) );

} /* usart_get_tx_enabled() */


uint8_t usart_read( usart_port_t port )
{
    return( ( uint8_t )PORT_UDR( port ) );

} /* usart_read() */


uint8_t usart_rx( usart_port_t port )
{
    usart_wait_rx_complete( port );
    return( usart_read( port ) );

} /* usart_rx() */


size_t usart_rx_until( usart_port_t port, char terminator, char* buf, size_t buf_sz )
{
    size_t count = 0;
    while( count < buf_sz )
    {
        buf[ count++ ] = ( char )usart_rx( port );
        if( buf[ count - 1 ] == terminator )
            break;
    }

    return( count );

} /* usart_rx_until() */


void usart_set_data_bits( usart_port_t port, usart_data_bits_t data_bits )
{
    switch( data_bits )
    {
    case USART_DATA_BITS_5:
        // UCSZ = 000
        clear_bit( PORT_UCSRB( port ), UCSZ02 );
        clear_bit( PORT_UCSRC( port ), UCSZ01 );
        clear_bit( PORT_UCSRC( port ), UCSZ00 );
        break;

    case USART_DATA_BITS_6:
        // UCSZ = 001
        clear_bit( PORT_UCSRB( port ), UCSZ02 );
        clear_bit( PORT_UCSRC( port ), UCSZ01 );
        set_bit(   PORT_UCSRC( port ), UCSZ00 );
        break;

    case USART_DATA_BITS_7:
        // UCSZ = 010
        clear_bit( PORT_UCSRB( port ), UCSZ02 );
        set_bit(   PORT_UCSRC( port ), UCSZ01 );
        clear_bit( PORT_UCSRC( port ), UCSZ00 );
        break;

    case USART_DATA_BITS_8:
        // UCSZ = 011
        clear_bit( PORT_UCSRB( port ), UCSZ02 );
        set_bit(   PORT_UCSRC( port ), UCSZ01 );
        set_bit(   PORT_UCSRC( port ), UCSZ00 );
        break;

    default:
        break;
    }

} /* usart_set_data_bits() */


void usart_set_parity( usart_port_t port, usart_parity_t parity )
{
    switch( parity )
    {
    case USART_PARITY_NONE:
        // UPM = 00
        clear_bit( PORT_UCSRC( port ), UPM01 );
        clear_bit( PORT_UCSRC( port ), UPM00 );
        break;

    case USART_PARITY_EVEN:
        // UPM = 10
        set_bit(   PORT_UCSRC( port ), UPM01 );
        clear_bit( PORT_UCSRC( port ), UPM00 );
        break;

    case USART_PARITY_ODD:
        // UPM = 11
        set_bit(   PORT_UCSRC( port ), UPM01 );
        set_bit(   PORT_UCSRC( port ), UPM00 );
        break;

    default:
        break;
    }

} /* usart_set_parity() */


void usart_set_rx_enabled( usart_port_t port, bool enabled )
{
    assign_bit( PORT_UCSRB( port ), RXEN0, enabled );

} /* usart_set_rx_enabled() */


void usart_set_stop_bits( usart_port_t port, usart_stop_bits_t stop_bits )
{
    switch( stop_bits )
    {
    case USART_STOP_BITS_1:
        clear_bit( PORT_UCSRC( port ), USBS0 );
        break;

    case USART_STOP_BITS_2:
        set_bit( PORT_UCSRC( port ), USBS0 );
        break;

    default:
        break;
    }

} /* usart_set_stop_bits() */


void usart_set_tx_enabled( usart_port_t port, bool enabled )
{
    assign_bit( PORT_UCSRB( port ), TXEN0, enabled );

} /* usart_set_tx_enabled() */


void usart_tx( usart_port_t port, uint8_t byte )
{
    usart_wait_data_empty( port );
    usart_write( port, byte );
    usart_wait_tx_complete( port );

} /* usart_tx() */


void usart_tx_string( usart_port_t port, char const* str )
{
    while( *str )
    {
        usart_wait_data_empty( port ),
        usart_write( port, ( uint8_t )( * ( str++ ) ) );
    }
    usart_wait_tx_complete( port );

} /* usart_tx_string() */


void usart_wait_data_empty( usart_port_t port )
{
    wait_bit_set( PORT_UCSRA( port ), UDRE0 );

} /* usart_wait_data_empty() */


void usart_wait_rx_complete( usart_port_t port )
{
    wait_bit_set( PORT_UCSRA( port ), RXC0 );

} /* usart_wait_rx_complete() */


void usart_wait_tx_complete( usart_port_t port )
{
    wait_bit_set( PORT_UCSRA( port ), TXC0 );

} /* usart_wait_tx_complete() */


void usart_write( usart_port_t port, uint8_t byte )
{
    PORT_UDR( port ) = byte;

} /* usart_write() */
