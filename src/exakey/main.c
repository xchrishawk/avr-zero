/**
 * @file    main.c
 * @brief   Main entry point for the Exakey application.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <stdbool.h>

#include <util/delay.h>

#include "lcd1602a.h"

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    _delay_ms( 1000 );

    lcd1602a_init();

    char a[] = "ABC";
    char b[] = "xyz";

    while( true )
    {
        lcd1602a_write_lines( a, b );

        a[ 0 ]++;
        a[ 1 ]++;
        a[ 2 ]++;

        b[ 0 ]--;
        b[ 1 ]--;
        b[ 2 ]--;

        _delay_ms( 1000 );
    }

} /* main() */
