/**
 * @file    bit_ops.h
 * @brief   Header containing utilities for bit operations.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

#if !defined( ZERO_BIT_OPS_H )
#define ZERO_BIT_OPS_H

/* -- Macros -- */

/**
 * @def     bitmask( _b )
 * @brief   Returns a bitmask for the specified single zero-indexed bit.
 */
#define bitmask( _b )                                                           \
    ( 1 << ( _b ) )

/**
 * @def     bitmask1( _b1 )
 * @brief   Returns a bitmask for the specified single zero-indexed bit.
 */
#define bitmask1( _b1 )                                                         \
    ( bitmask( _b1 ) )

/**
 * @def     bitmask2( _b1, _b2 )
 * @brief   Returns a bitmask for the two specified zero-indexed bits.
 */
#define bitmask2( _b1, _b2 )                                                    \
    ( bitmask1( _b1 ) | bitmask( _b2 ) )

/**
 * @def     bitmask3( _b1, _b2. _b3 )
 * @brief   Returns a bitmask for the three specified zero-indexed bits.
 */
#define bitmask3( _b1, _b2, _b3 )                                               \
    ( bitmask2( _b1, _b2 ) | bitmask( _b3 ) )

/**
 * @def     bitmask4( _b1, _b2. _b3, _b4 )
 * @brief   Returns a bitmask for the four specified zero-indexed bits.
 */
#define bitmask4( _b1, _b2, _b3, _b4 )                                          \
    ( bitmask3( _b1, _b2, _b3 ) | bitmask( _b4 ) )

/**
 * @def     bitmask5( _b1, _b2. _b3, _b4, _b5 )
 * @brief   Returns a bitmask for the five specified zero-indexed bits.
 */
#define bitmask5( _b1, _b2, _b3, _b4, _b5 )                                     \
    ( bitmask4( _b1, _b2, _b3, _b4 ) | bitmask( _b5 ) )

/**
 * @def     bitmask6( _b1, _b2. _b3, _b4, _b5, _b6 )
 * @brief   Returns a bitmask for the six specified zero-indexed bits.
 */
#define bitmask6( _b1, _b2, _b3, _b4, _b5, _b6 )                                \
    ( bitmask5( _b1, _b2, _b3, _b4, _b5 ) | bitmask( _b6 ) )

/**
 * @def     bitmask7( _b1, _b2. _b3, _b4, _b5, _b6, _b7 )
 * @brief   Returns a bitmask for the seven specified zero-indexed bits.
 */
#define bitmask7( _b1, _b2, _b3, _b4, _b5, _b6, _b7 )                           \
    ( bitmask6( _b1, _b2, _b3, _b4, _b5, _b6 ) | bitmask( _b7 ) )

/**
 * @def     bitmask8( _b1, _b2. _b3, _b4, _b5, _b6, _b7, _b8 )
 * @brief   Returns a bitmask for the eight specified zero-indexed bits.
 */
#define bitmask8( _b1, _b2, _b3, _b4, _b5, _b6, _b7, _b8 )                      \
    ( bitmask7( _b1, _b2, _b3, _b4, _b5, _b6, _b7 ) | bitmask( _b8 ) )

/**
 * @def     clear_bitmask( _tgt, _m )
 * @brief   Clears all bits in @c _tgt which are specified in the @c _m bitmask.
 */
#define clear_bitmask( _tgt, _m )                                               \
    ( _tgt ) &= ( ~ ( _m ) )

/**
 * @def     set_bitmask( _tgt, _m )
 * @brief   Sets all bits in @c _tgt which are specified in the @c _m bitmask.
 */
#define set_bitmask( _tgt, _m )                                                 \
    ( _tgt ) |= ( _m )

/**
 * @def     toggle_bitmask( _tgt, _m )
 * @brief   Toggles all bits in @c _tgt which are specified in the @c _m bitmask.
 */
#define toggle_bitmask( _tgt, _m )                                              \
    ( _tgt ) ^= ( _m )

/**
 * @def     assign_bitmask( _tgt, _m, _value )
 * @brief   Sets or clears all bits in @c _tgt which are specified in the @c _m bitmask, based on whether @c _value
 *          evaluates to @c true or not.
 */
#define assign_bitmask( _tgt, _m, _value )                                      \
    do                                                                          \
    {                                                                           \
        if( _value )                                                            \
            set_bitmask( _tgt, _m );                                            \
        else                                                                    \
            clear_bitmask( _tgt, _m );                                          \
    }                                                                           \
    while( 0 )

/**
 * @def     clear_bit( _tgt, _b )
 * @brief   Clears the zero-indexed bit specified by @c _b in @c _tgt .
 */
#define clear_bit( _tgt, _b )                                                   \
    clear_bitmask( _tgt, bitmask( _b ) )

/**
 * @def     set_bit( _tgt, _b )
 * @brief   Sets the zero-indexed bit specified by @c _b in @c _tgt .
 */
#define set_bit( _tgt, _b )                                                     \
    set_bitmask( _tgt, bitmask( _b ) )

/**
 * @def     toggle_bit( _tgt, _b )
 * @brief   Toggles the zero-indexed bit specified by @c _b in @c _tgt .
 */
#define toggle_bit( _tgt, _b )                                                  \
    toggle_bitmask( _tgt, bitmask( _b ) )

/**
 * @def     assign_bit( _tgt, _b, _value )
 * @brief   Sets or clears the zero-indexed bit specified by @c _b in @c _tgt , based on whether @c _value evaluates to
 *          @c true or not.
 */
#define assign_bit( _tgt, _b, _value )                                          \
    assign_bitmask( _tgt, bitmask( _b ), _value )

/**
 * @def     is_bitmask_set( _tgt, _m )
 * @brief   Returns @c true if all bits specified by @c _m in @c _tgt are set.
 */
#define is_bitmask_set( _tgt, _m )                                              \
    ( ( ( _tgt ) & ( _m ) ) == ( _m ) )

/**
 * @def     is_bitmask_clear( _tgt, _m )
 * @brief   Returns @c true if all bits specified by @c _m in @c _tgt are clear.
 */
#define is_bitmask_clear( _tgt, _m )                                            \
    ( ( ( _tgt ) & ( _m ) ) == 0 )

/**
 * @def     is_bit_set( _tgt, _b )
 * @brief   Returns @c true if the zero-indexed bit specified by @c _b in @c _tgt is set.
 */
#define is_bit_set( _tgt, _b )                                                  \
    is_bitmask_set( _tgt, bitmask( _b ) )

/**
 * @def     is_bit_clear( _tgt, _b )
 * @brief   Returns @c true if the zero-indexed bit specified by @c _b in @c _tgt is clear.
 */
#define is_bit_clear( _tgt, _b )                                                \
    is_bitmask_clear( _tgt, bitmask( _b ) )

/**
 * @def     wait_bitmask_clear( _tgt, _m )
 * @brief   Waits in a spin loop until all bits specified by @c _m in @c _tgt are clear.
 */
#define wait_bitmask_clear( _tgt, _m )                                          \
    do { } while( ! is_bitmask_clear( _tgt, _m ) )

/**
 * @def     wait_bitmask_set( _tgt, _m )
 * @brief   Waits in a spin loop until all bits specified by @c _m in @c _tgt are set.
 */
#define wait_bitmask_set( _tgt, _m )                                            \
    do { } while( ! is_bitmask_set( _tgt, _m ) )

/**
 * @def     wait_bit_clear( _tgt, _b )
 * @brief   Waits in a spin loop until the zero-indexed bit specified by @c _b in @c _tgt is clear.
 */
#define wait_bit_clear( _tgt, _b )                                              \
    do { } while( ! is_bit_clear( _tgt, _b ) )

/**
 * @def     wait_bit_set( _tgt, _b )
 * @brief   Waits in a spin loop until the zero-indexed bit specified by @c _b in @c _tgt is set.
 */
#define wait_bit_set( _tgt, _b )                                                \
    do { } while( ! is_bit_set( _tgt, _b ) )

#endif /* !defined( ZERO_BIT_OPS_H ) */
