/**
 * @file    utility.h
 * @brief   Header defining miscellaneous utilities.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-27
 */

#if !defined( UTILITY_UTILITY_H )
#define UTILITY_UTILITY_H

/* -- Macros -- */

/**
 * @def     array_count
 * @brief   Returns the number of elements in the specified array.
 */
#define array_count( _a )                                                       \
    ( sizeof( _a ) / sizeof( _a[ 0 ] ) )

#endif /* !defined( UTILITY_UTILITY_H ) */
