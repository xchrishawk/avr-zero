/**
 * @file    shield-hw262.h
 * @brief   Header for the hw262 library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-07
 */

#if !defined( SHIELD_HW262_SHIELD_HW262_H )
#define SHIELD_HW262_SHIELD_HW262_H

/* -- Includes -- */

#include <stdint.h>

#include "gpio/gpio.h"

/* -- Types -- */

/**
 * @typedef hw262_button_t
 * @brief   Enumeration of the buttons available on the HW262 shield.
 */
typedef uint8_t hw262_button_t;
enum
{
    HW262_BUTTON_S1,                /**< Button S1.                             */
    HW262_BUTTON_S2,                /**< Button S2.                             */
    HW262_BUTTON_S3,                /**< Button S3.                             */

    HW262_BUTTON_COUNT,             /**< Number of valid buttons.               */
};

/**
 * @typedef hw262_led_t
 * @brief   Enumeration of the LEDs available on the HW262 shield.
 */
typedef uint8_t hw262_led_t;
enum
{
    HW262_LED_D1,                   /**< LED D1.                                */
    HW262_LED_D2,                   /**< LED D2.                                */
    HW262_LED_D3,                   /**< LED D3.                                */
    HW262_LED_D4,                   /**< LED D4.                                */

    HW262_LED_COUNT,                /**< Number of valid LEDs.                  */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      hw262_button_get( hw262_button_t )
 * @brief   Returns the state of the specified button.
 * @returns `true` if the button is currently pressed.
 */
bool hw262_button_get( hw262_button_t button );

/**
 * @fn      hw262_button_pin( hw262_button_t )
 * @brief   Returns the GPIO pin associated with the specified button.
 */
gpio_pin_t hw262_button_pin( hw262_button_t button );

/**
 * @fn      hw262_init( void )
 * @brief   Initializes the HW262 module.
 */
void hw262_init( void );

/**
 * @fn      hw262_led_pin( hw262_led_t )
 * @brief   Returns the GPIO pin associated with the specified LED.
 */
gpio_pin_t hw262_led_pin( hw262_led_t led );

/**
 * @fn      hw262_led_set( hw262_led_t, bool )
 * @brief   Sets the specified LED to on if the argument is `true`, or off otherwise.
 */
void hw262_led_set( hw262_led_t led, bool on );

#endif /* !defined( SHIELD_HW262_SHIELD_HW262_H ) */
