/**
 * @file    util.h
 * @brief   Header defining miscellaneous utilities.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-27
 */

#if !defined( UTIL_H )
#define UTIL_H

/* -- Macros -- */

/**
 * @def     array_count
 * @brief   Returns the number of elements in the specified array.
 */
#define array_count( _a )                                                       \
    ( sizeof( _a ) / sizeof( _a[ 0 ] ) )

#endif /* !defined( UTIL_H ) */
