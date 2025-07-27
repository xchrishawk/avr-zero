/**
 * @file    main.c
 * @brief   Main entry point for the Exakey application.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

#include "lcd1602a/lcd1602a.h"

/* -- Procedures -- */

/**
 * @fn      int main( void )
 * @brief   Main entry point for the Exakey application.
 */
int main( void )
{
    _delay_ms( 500 );

    lcd1602a_cfg_t lcd;
    lcd1602a_init_default( &lcd );
    lcd1602a_write_string( &lcd, "Button:" );

    while( true )
    {
        static const char* STRINGS[] = { "NONE  ", "UP    ", "DOWN  ", "LEFT  ", "RIGHT ", "SELECT" };
        lcd1602a_button_t button = lcd1602a_get_button( &lcd );
        lcd1602a_set_address( &lcd, LCD1602A_ADDRESS_SECOND_LINE );
        lcd1602a_write_string( &lcd, STRINGS[ button ] );
    }

} /* main() */
