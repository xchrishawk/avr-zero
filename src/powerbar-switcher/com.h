/**
 * @file    com.h
 * @brief   Header for the serial communication module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-03
 */

#if !defined( POWERBAR_SWITCHER_COM_H )
#define POWERBAR_SWITCHER_COM_H

/* -- Types -- */

typedef uint8_t com_rx_status_t;
enum
{
    COM_RX_STATUS_OK,               /**< Full valid input has been received.            */
    COM_RX_STATUS_WAIT,             /**< Full input has not yet been received.          */
    COM_RX_STATUS_OVERFLOW,         /**< RX buffer overflow occurred.                   */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      com_init( void )
 * @brief   Initializes the serial communication module.
 */
void com_init( void );

/**
 * @fn      com_rx( char*, size_t )
 * @brief   Checks the current RX status, and copies any complete, valid input to `buf`, if available.
 * @param   buf
 *          Buffer to receive a completed input string.
 * @param   buf_sz
 *          The size of the buffer.
 * @returns A `com_rx_status_t` indicating the current status.
 *          - `COM_RX_STATUS_OK` indicates that a complete input has been received, and was copied to `buf`.
 *          - `COM_RX_STATUS_WAIT` indicates that input is still being received. Nothing is written to `buf`.
 *          - `COM_RX_STATUS_OVERFLOW` indicates that the RX buffer overflowed without receiving the terminator. Nothing
 *            is written to `buf`.
 * @note    This procedure is expected to be called immediately in response to an EVENT_COM_RX event. The RX buffer is
 *          flushed / reset if the return status is anything other than `COM_RX_STATUS_WAIT`.
 */
com_rx_status_t com_rx( char* buf, size_t buf_sz );

/**
 * @fn      com_tx( char const* )
 * @brief   Asynchronously transmits the specified null-terminated string.
 */
void com_tx( char const* buf );

/**
 * @fn      com_tx_fmt( char const*, ... )
 * @brief   Asynchronously transmits the specified formatted null-terminated string.
 */
void com_tx_fmt( char const* fmt, ... );

#endif /* !defined( POWERBAR_SWITCHER_COM_H ) */
