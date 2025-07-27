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
    // Startup delay for LCD
    _delay_ms( 500 );

    // Initialize systems
    lcd1602a_init();

    lcd1602a_write_lines( "Button:", NULL );

    while( true )
    {
        // Get value
        lcd1602a_button_t button = lcd1602a_get_button();
        lcd1602a_set_address( LCD1602A_ADDRESS_SECOND_LINE );
        switch( button )
        {
        case LCD1602A_BUTTON_NONE:
            lcd1602a_write_string( "None  " );
            break;
        case LCD1602A_BUTTON_UP:
            lcd1602a_write_string( "Up    " );
            break;
        case LCD1602A_BUTTON_DOWN:
            lcd1602a_write_string( "Down  " );
            break;
        case LCD1602A_BUTTON_LEFT:
            lcd1602a_write_string( "Left  " );
            break;
        case LCD1602A_BUTTON_RIGHT:
            lcd1602a_write_string( "Right " );
            break;
        case LCD1602A_BUTTON_SELECT:
            lcd1602a_write_string( "Select" );
            break;
        }
    }

} /* main() */
