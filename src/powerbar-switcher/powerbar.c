/**
 * @file    powerbar.c
 * @brief   Implementation for the powerbar management module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-03
 */

/* -- Includes -- */

#include <stdint.h>

#include "gpio/gpio.h"

#include "event.h"
#include "powerbar.h"

/* -- Constants -- */

// GPIO pins
static gpio_pin_t const LED_PIN  = GPIO_PIN_ARDUINO_BUILT_IN_LED;
static gpio_pin_t const CTRL_PIN = GPIO_PIN_ARDUINO_D14;

/* -- Variables -- */

static uint32_t s_on_tick = 0;

/* -- Procedures -- */

bool powerbar_get_enabled( void )
{
    return( gpio_get_state( CTRL_PIN ) == GPIO_STATE_HIGH );

} /* powerbar_set_enabled() */


uint32_t powerbar_get_uptime( void )
{
    if( ! powerbar_get_enabled() )
        return( 0 );

    uint32_t tick = event_tick();
    if( tick > s_on_tick )
        return( tick - s_on_tick );
    else
        return( 0 );

} /* powerbar_get_uptime() */


void powerbar_init( void )
{
    gpio_config_t config = { GPIO_DIR_OUT, GPIO_STATE_LOW };
    gpio_set_config( LED_PIN, &config );
    gpio_set_config( CTRL_PIN, &config );

} /* powerbar_init() */


void powerbar_set_enabled( bool enabled )
{
    gpio_state_t state = ( enabled ? GPIO_STATE_HIGH : GPIO_STATE_LOW );
    gpio_set_state( LED_PIN, state );
    gpio_set_state( CTRL_PIN, state );

    if( enabled )
        s_on_tick = event_tick();
    else
        s_on_tick = 0;

} /* powerbar_set_enabled() */


void powerbar_toggle( void )
{
    bool enabled = powerbar_get_enabled();
    powerbar_set_enabled( ! enabled );

} /* powerbar_toggle() */
