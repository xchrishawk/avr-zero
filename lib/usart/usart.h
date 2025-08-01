/**
 * @file    usart.h
 * @brief   Header for the USART driver library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-31
 */

#if !defined( USART_H )
#define USART_H

/* -- Includes -- */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* -- Types -- */

/**
 * @typedef usart_data_bits_t
 * @brief   Enumeration of the supported USART data bits settings.
 * @note    9-bit frames are not currently supported.
 */
typedef uint8_t usart_data_bits_t;
enum
{
    USART_DATA_BITS_5,              /**< 5 data bits per frame.                         */
    USART_DATA_BITS_6,              /**< 6 data bits per frame.                         */
    USART_DATA_BITS_7,              /**< 7 data bits per frame.                         */
    USART_DATA_BITS_8,              /**< 8 data bits per frame.                         */
    USART_DATA_BITS_COUNT,          /**< Number of valid data bits settings.            */
};

/**
 * @typedef usart_parity_t
 * @brief   Enumeration of the supported USART parity settings.
 */
typedef uint8_t usart_parity_t;
enum
{
    USART_PARITY_NONE,              /**< No parity is enabled.                          */
    USART_PARITY_EVEN,              /**< Even parity is enabled.                        */
    USART_PARITY_ODD,               /**< Odd parity is enabled.                         */
    USART_PARITY_COUNT,             /**< Number of valid parity settings.               */
};

/**
 * @typedef usart_port_t
 * @brief   Enumeration of the supported USART ports.
 */
typedef uint8_t usart_port_t;
enum
{
    USART_PORT_0,                   /**< USART port 0.                                  */
    USART_PORT_COUNT,               /**< Number of valid USART ports.                   */
};

/**
 * @typedef usart_stop_bits_t
 * @brief   Enumeration of the supported USART stop bits settings.
 */
typedef uint8_t usart_stop_bits_t;
enum
{
    USART_STOP_BITS_1,              /**< Each frame has 1 stop bit.                     */
    USART_STOP_BITS_2,              /**< Each frame has 2 stop bits.                    */
    USART_STOP_BITS_COUNT,          /**< Number of valid stop bits settings.            */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      usart_autoconfigure_baud( usart_port_t )
 * @brief   Automatically configures the baud rate for the specified USART port based on the `BAUD` macro.
 */
void usart_autoconfigure_baud( usart_port_t port );

/**
 * @fn      usart_get_rx_enabled( usart_port_t )
 * @brief   Returns `true` if RX is enabled for the specified USART port.
 */
bool usart_get_rx_enabled( usart_port_t port );

/**
 * @fn      usart_get_tx_enabled( usart_port_t )
 * @brief   Returns `true` if TX is enabled for the specified USART port.
 */
bool usart_get_tx_enabled( usart_port_t port );

/**
 * @fn      usart_read( usart_port_t )
 * @brief   Immediately returns the content of the data register for the specified USART port.
 */
uint8_t usart_read( usart_port_t port );

/**
 * @fn      usart_rx( usart_port_t )
 * @brief   Synchronously receives a byte from the specified USART port.
 * @note    Blocks until a byte is received.
 */
uint8_t usart_rx( usart_port_t port );

/**
 * @fn      usart_rx_until( usart_port_t, char, char*, size_t )
 * @brief   Synchronously receives bytes into the specified buffer until the specified character is received, or the
 *          buffer is full, whichever happens first.
 * @param   port
 *          The port to receive data from.
 * @param   terminator
 *          The function will return after this character is received.
 * @param   buf
 *          The buffer to write the received data into.
 * @param   buf_sz
 *          The maximum number of characters which can be written into the buffer.
 * @returns The total number of characters received.
 */
size_t usart_rx_until( usart_port_t port, char terminator, char* buf, size_t buf_sz );

/**
 * @fn      usart_set_data_bits( usart_port_t, usart_data_bits_t )
 * @brief   Sets the number of data bits per frame for the specified USART port.
 */
void usart_set_data_bits( usart_port_t port, usart_data_bits_t data_bits );

/**
 * @fn      usart_set_parity( usart_port_t, usart_parity_t )
 * @brief   Sets the parity of the specified USART port.
 */
void usart_set_parity( usart_port_t port, usart_parity_t parity );

/**
 * @fn      usart_set_rx_enabled( usart_port_t, bool )
 * @brief   Enables or disables RX for the specified USART port.
 */
void usart_set_rx_enabled( usart_port_t port, bool enabled );

/**
 * @fn      usart_set_stop_bits( usart_port_t, usart_stop_bits_t )
 * @brief   Sets the number of stop bits per frame for the specified USART port.
 */
void usart_set_stop_bits( usart_port_t port, usart_stop_bits_t stop_bits );

/**
 * @fn      usart_set_tx_enabled( usart_port_t, bool )
 * @brief   Enables or disables TX for the specified USART port.
 */
void usart_set_tx_enabled( usart_port_t port, bool enabled );

/**
 * @fn      usart_tx( usart_port_t, uint8_t )
 * @brief   Synchronously transmits a single byte.
 * @note    Blocks until the byte has completed transmission.
 */
void usart_tx( usart_port_t port, uint8_t byte );

/**
 * @fn      usart_tx_string( usart_port_t, char const* )
 * @brief   Synchronously transmits a string of characters.
 * @note    Blocks until all characters have completed transmission.
 */
void usart_tx_string( usart_port_t port, char const* str );

/**
 * @brief   usart_wait_data_empty( usart_port_t )
 * @brief   Waits for the data register for the specified port to be empty.
 */
void usart_wait_data_empty( usart_port_t port );

/**
 * @fn      usart_wait_rx_complete( usart_port_t )
 * @brief   Synchronously waits for any pending RX operation to complete.
 */
void usart_wait_rx_complete( usart_port_t port );

/**
 * @fn      usart_wait_tx_complete( usart_port_t )
 * @brief   Synchronously waits for any pending TX operation to complete.
 */
void usart_wait_tx_complete( usart_port_t port );

/**
 * @fn      usart_write( usart_port_t, uint8_t )
 * @brief   Immediately sets the content of the data register for the specified USART port.
 */
void usart_write( usart_port_t port, uint8_t byte );

#endif /* !defined( USART_H ) */
