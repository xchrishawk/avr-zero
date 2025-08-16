/**
 * @file    shield-lcd1602a.h
 * @brief   Header for the shield-lcd1602a library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-16
 */

#if !defined( SHIELDS_LCD1602A_SHIELD_LCD1602A_H )
#define SHIELDS_LCD1602A_SHIELD_LCD1602A_H

/* -- Includes -- */

#include <stdint.h>

#include "lcdtext/lcdtext.h"

/* -- Types -- */

/**
 * @typedef shield_lcd1602a_button_t
 * @brief   Enumeration of the buttons supported by the LCD1602A shield.
 */
typedef uint8_t shield_lcd1602a_button_t;
enum
{
    SHIELD_LCD1602A_BUTTON_SELECT,  /**< Select button is pressed.              */
    SHIELD_LCD1602A_BUTTON_UP,      /**< Up button is pressed.                  */
    SHIELD_LCD1602A_BUTTON_DOWN,    /**< Down button is pressed.                */
    SHIELD_LCD1602A_BUTTON_LEFT,    /**< Left button is pressed.                */
    SHIELD_LCD1602A_BUTTON_RIGHT,   /**< Right button is pressed.               */

    SHIELD_LCD1602A_BUTTON_COUNT,   /**< Number of valid buttons.               */

    SHIELD_LCD1602A_BUTTON_NONE     /**< No button is pressed.                  */
        = SHIELD_LCD1602A_BUTTON_COUNT,
};

/* -- Procedure Prototypes -- */

/**
 * @fn      shield_lcd1602a_get_button( void )
 * @brief   Returns the currently pressed button, if any.
 */
shield_lcd1602a_button_t shield_lcd1602a_get_button( void );

/**
 * @fn      shield_lcd1602a_init( void )
 * @brief   Initializes the LCD1602A shield module.
 */
void shield_lcd1602a_init( void );

/**
 * @fn      shield_lcd1602a_lcd( void )
 * @brief   Returns a pointer to the `lcdtext_t` instance used by the module.
 */
lcdtext_t const * shield_lcd1602a_lcd( void );

#endif /* !defined( SHIELDS_LCD1602A_SHIELD_LCD1602A_H ) */
