/**
 * @file    hw262.c
 * @brief   Implementation for the hw262 library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-07
 */

/* -- Includes -- */

#include <assert.h>
#include <stdint.h>

#include "gpio/gpio.h"
#include "zero/utility.h"

#include "hw262.h"

/* -- Constants -- */

// Array of pins for buttons.
static gpio_pin_t s_button_pin_tbl[] =
{
    GPIO_PIN_ARDUINO_D15,
    GPIO_PIN_ARDUINO_D16,
    GPIO_PIN_ARDUINO_D17,
};
_Static_assert( array_count( s_button_pin_tbl ) == HW262_BUTTON_COUNT, "Button pin table must have correct size!" );

// Array of pins for LEDs
static gpio_pin_t s_led_pin_tbl[] =
{
    GPIO_PIN_ARDUINO_D13,
    GPIO_PIN_ARDUINO_D12,
    GPIO_PIN_ARDUINO_D11,
    GPIO_PIN_ARDUINO_D10,
};
_Static_assert( array_count( s_led_pin_tbl ) == HW262_LED_COUNT, "LED pin table must have correct size!" );

/* -- Macros -- */

#define validate_button( _button )                                              \
    assert( ( _button ) < HW262_BUTTON_COUNT )
#define validate_led( _led )                                                    \
    assert( ( _led ) < HW262_LED_COUNT )

/* -- Procedures -- */

bool hw262_button_get( hw262_button_t button )
{
    return( gpio_get_state( hw262_button_pin( button ) ) == GPIO_STATE_LOW );

} /* hw262_button_get() */


gpio_pin_t hw262_button_pin( hw262_button_t button )
{
    validate_button( button );
    return( s_button_pin_tbl[ button ] );

} /* hw262_button_pin() */


void hw262_init( void )
{
    // Configure GPIO inputs
    gpio_config_t input_config = { GPIO_DIR_IN, false };
    for( hw262_button_t button = 0; button < HW262_BUTTON_COUNT; button++ )
        gpio_set_config( hw262_button_pin( button ), & input_config );

    // Configure GPIO outputs
    gpio_config_t output_config = { GPIO_DIR_OUT, GPIO_STATE_HIGH };
    for( hw262_led_t led = 0; led < HW262_LED_COUNT; led++ )
        gpio_set_config( hw262_led_pin( led ), & output_config );

} /* hw262_init() */


gpio_pin_t hw262_led_pin( hw262_led_t led )
{
    validate_led( led );
    return( s_led_pin_tbl[ led ] );

} /* hw262_led_pin() */


void hw262_led_set( hw262_led_t led, bool on )
{
    gpio_set_state( hw262_led_pin( led ), on ? GPIO_STATE_LOW : GPIO_STATE_HIGH );

} /* hw262_led_set() */
