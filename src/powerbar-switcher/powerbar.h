/**
 * @file    powerbar.h
 * @brief   Header for the powerbar management module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-03
 */

#if !defined( POWERBAR_SWITCHER_POWERBAR_H )
#define POWERBAR_SWITCHER_POWERBAR_H

/* -- Includes -- */

#include <stdbool.h>

/* -- Procedure Prototypes -- */

/**
 * @fn      powerbar_get_enabled( void )
 * @brief   Returns `true` if the powerbar is currently turned on.
 */
bool powerbar_get_enabled( void );

/**
 * @fn      powerbar_get_uptime( void )
 * @brief   Returns the current uptime of the powerbar, in ticks.
 */
uint32_t powerbar_get_uptime( void );

/**
 * @fn      powerbar_init( void )
 * @brief   Initializes the powerbar management module.
 */
void powerbar_init( void );

/**
 * @fn      powerbar_set_enabled( bool )
 * @brief   Turns the powerbar on or off.
 */
void powerbar_set_enabled( bool enabled );

/**
 * @fn      powerbar_toggle( void )
 * @brief   Toggles the powerbar on or off.
 */
void powerbar_toggle( void );

#endif /* !defined( POWERBAR_SWITCHER_POWERBAR_H ) */
