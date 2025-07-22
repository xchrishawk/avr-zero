/**
 * @file    gpio.h
 * @brief   Header for the GPIO driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

#if !defined( GPIO_H )
#define GPIO_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

/* -- Types -- */

/**
 * @typedef gpio_pin_t
 * @brief   Enumeration of supported GPIO pins.
 */
typedef uint8_t gpio_pin_t;
enum
{
    // Default Arduino pin names
    GPIO_PIN_ARDUINO_D0 = 0,        /**< Arduino GPIO pin D0.                           */
    GPIO_PIN_ARDUINO_D1,            /**< Arduino GPIO pin D1.                           */
    GPIO_PIN_ARDUINO_D2,            /**< Arduino GPIO pin D2.                           */
    GPIO_PIN_ARDUINO_D3,            /**< Arduino GPIO pin D3.                           */
    GPIO_PIN_ARDUINO_D4,            /**< Arduino GPIO pin D4.                           */
    GPIO_PIN_ARDUINO_D5,            /**< Arduino GPIO pin D5.                           */
    GPIO_PIN_ARDUINO_D6,            /**< Arduino GPIO pin D6.                           */
    GPIO_PIN_ARDUINO_D7,            /**< Arduino GPIO pin D7.                           */
    GPIO_PIN_ARDUINO_D8,            /**< Arduino GPIO pin D8.                           */
    GPIO_PIN_ARDUINO_D9,            /**< Arduino GPIO pin D9.                           */
    GPIO_PIN_ARDUINO_D10,           /**< Arduino GPIO pin D10.                          */
    GPIO_PIN_ARDUINO_D11,           /**< Arduino GPIO pin D11.                          */
    GPIO_PIN_ARDUINO_D12,           /**< Arduino GPIO pin D12.                          */
    GPIO_PIN_ARDUINO_D13,           /**< Arduino GPIO pin D13.                          */
    GPIO_PIN_ARDUINO_D14,           /**< Arduino GPIO pin D14.                          */
    GPIO_PIN_ARDUINO_D15,           /**< Arduino GPIO pin D15.                          */
    GPIO_PIN_ARDUINO_D16,           /**< Arduino GPIO pin D16.                          */
    GPIO_PIN_ARDUINO_D17,           /**< Arduino GPIO pin D17.                          */
    GPIO_PIN_ARDUINO_D18,           /**< Arduino GPIO pin D18.                          */
    GPIO_PIN_ARDUINO_D19,           /**< Arduino GPIO pin D19.                          */

    // Count of default pin names
    GPIO_PIN_COUNT,                 /**< Number of valid GPIO pins.                     */

    // Aliases
    GPIO_PIN_ARDUINO_BUILT_IN_LED   /**< Arduino built-in LED.                          */
        = GPIO_PIN_ARDUINO_D13,
};

/**
 * @typedef gpio_dir_t
 * @brief   Enumeration of supported GPIO pin I/O directions.
 */
typedef uint8_t gpio_dir_t;
enum
{
    GPIO_DIR_IN,                    /**< Pin is an input.                               */
    GPIO_DIR_OUT,                   /**< Pin is an output.                              */
    GPIO_DIR_COUNT,                 /**< Number of valid directions.                    */
};

/**
 * @typedef gpio_state_t
 * @brief   Enumeration of the supported states for GPIO pins.
 */
typedef uint8_t gpio_state_t;
enum
{
    GPIO_STATE_LOW,                 /**< Pin is in the low state.                       */
    GPIO_STATE_HIGH,                /**< Pin is in the high state.                      */
    GPIO_STATE_COUNT,               /**< Number of valid pin states.                    */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      gpio_set_dir( gpio_pin_t, gpio_dir_t )
 * @brief   Sets the I/O direction (in or out) of the specified GPIO pin.
 */
void gpio_set_dir( gpio_pin_t pin, gpio_dir_t dir );

/**
 * @fn      gpio_get_state( gpio_pin_t )
 * @brief   Gets the state (low or high) of the specified GPIO pin.
 */
gpio_state_t gpio_get_state( gpio_pin_t pin );

/**
 * @fn      gpio_set_state( gpio_pin_t, gpio_state_t )
 * @brief   Sets the state (low or high) of the specified GPIO pin.
 */
void gpio_set_state( gpio_pin_t pin, gpio_state_t state );

#endif /* !defined( GPIO_H ) */
