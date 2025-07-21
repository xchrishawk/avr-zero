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

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    DDRB |= ( 1 << DDB5 );

    while( true )
    {
        PORTB |= ( 1 << PORTB5 );
        _delay_ms( 25 );
        PORTB &= ~( 1 << PORTB5 );
        _delay_ms( 25 );
    }

} /* main() */
