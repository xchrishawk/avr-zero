/**
 * @file    main.c
 * @brief   Main module for the shield-lcd1602a-demo executable.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-16
 */

/* -- Includes -- */

#include "lcdtext/lcdtext.h"
#include "shield/lcd1602a/shield-lcd1602a.h"

/* -- Procedures -- */

int main( void )
{
    // Get LCD and initialize
    shield_lcd1602a_init();
    lcdtext_t const * lcd = shield_lcd1602a_lcd();

    while( true )
    {
        lcdtext_go_line_1( lcd );
        shield_lcd1602a_button_t button = shield_lcd1602a_get_button();
        switch( button )
        {
        case SHIELD_LCD1602A_BUTTON_SELECT:
            lcdtext_write( lcd, "Select          " );
            break;
        case SHIELD_LCD1602A_BUTTON_UP:
            lcdtext_write( lcd, "Up              " );
            break;
        case SHIELD_LCD1602A_BUTTON_DOWN:
            lcdtext_write( lcd, "Down            " );
            break;
        case SHIELD_LCD1602A_BUTTON_LEFT:
            lcdtext_write( lcd, "Left            " );
            break;
        case SHIELD_LCD1602A_BUTTON_RIGHT:
            lcdtext_write( lcd, "Right           " );
            break;
        default:
            lcdtext_write( lcd, "None            " );
            break;
        }
    }


} /* main() */
