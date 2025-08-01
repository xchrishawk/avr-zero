/**
 * @file    register.h
 * @brief   Header containing types and macros related to registers.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-31
 */

#if !defined( ZERO_REGISTER_H )
#define ZERO_REGISTER_H

/* -- Includes -- */

#include <stdint.h>

/* -- Types -- */

/**
 * @typedef register_t
 * @brief   Typedef for a register memory address.
 */
typedef volatile uint8_t* register_t;

/* -- Macros -- */

/**
 * @def     REGISTER_ADDR
 * @brief   Returns the address of the specified register as a `register_t`.
 */
#define REGISTER_ADDR( _reg )                                                   \
    ( ( register_t )( & ( _reg ) ) )

#endif /* !defined( ZERO_REGISTER_H ) */
