/**
 * @file    main.c
 * @brief   Main entry point for the Exakey application.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "bit_ops.h"

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    set_bit( DDRB, DDB5 );

    while( true )
    {
        set_bit( PORTB, PORTB5 );
        _delay_ms( 25 );
        clear_bit( PORTB, PORTB5 );
        _delay_ms( 975 );
    }

} /* main() */
