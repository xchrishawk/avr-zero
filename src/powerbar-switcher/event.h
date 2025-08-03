/**
 * @file    event.h
 * @brief   Header for the system event manager.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-03
 */

#if !defined( POWERBAR_SWITCHER_EVENT_H )
#define POWERBAR_SWITCHER_EVENT_H

/* -- Includes -- */

#include <stdint.h>

/* -- Types -- */

/**
 * @typedef event_t
 * @brief   Enumeration of the supported system events.
 */
typedef uint8_t event_t;
enum
{
    EVENT_NONE,                     /**< No event occurred.                             */
    EVENT_TICK,                     /**< 1 millisecond tick event.                      */
    EVENT_COM_RX,                   /**< Received serial data.                          */
    EVENT_COUNT,                    /**< Number of valid events.                        */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      event_init( void )
 * @brief   Initializes the system event manager.
 */
void event_init( void );

/**
 * @fn      event_set_pending( void )
 * @brief   Sets the specified event as pending.
 * @note    This function should only be called by interrupt handlers.
 */
void event_set_pending( event_t event );

/**
 * @fn      event_tick( void )
 * @brief   Returns the current system tick count.
 */
uint32_t event_tick( void );

/**
 * @fn      event_wait( void )
 * @brief   Waits for the next system event.
 */
event_t event_wait( void );

#endif /* !defined( POWERBAR_SWITCHER_EVENT_H ) */
