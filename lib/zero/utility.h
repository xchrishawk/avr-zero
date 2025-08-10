/**
 * @file    utility.h
 * @brief   Header defining miscellaneous utilities.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-27
 */

#if !defined( ZERO_UTILITY_H )
#define ZERO_UTILITY_H

/* -- Includes -- */

#include <assert.h>

/* -- Macros -- */

/**
 * @def     array_count
 * @brief   Returns the number of elements in the specified array.
 */
#define array_count( _a )                                                       \
    ( sizeof( _a ) / sizeof( _a[ 0 ] ) )

/**
 * @def     validate_enum
 * @brief   Asserts that the specified enum variable is below a maximum value.
 */
#define validate_enum( _e, _max )                                               \
    assert( ( _e ) < ( _max ) )

#endif /* !defined( ZERO_UTILITY_H ) */
