/**
 * @file    gpio.h
 * @brief   Header for the GPIO driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

#if !defined( GPIO_GPIO_H )
#define GPIO_GPIO_H

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

/**
 * @struct  gpio_config_t
 * @brief   Struct representing the configuration for a GPIO pin.
 */
typedef struct
{
    gpio_dir_t          dir;        /**< The pin's I/O direction.                       */
    union
    {
        bool            pullup_en;  /**< (for inputs) Pull-up resistor enablement.      */
        gpio_state_t    state;      /**< (for outputs) Initial state.                   */
    };
} gpio_config_t;

/* -- Procedure Prototypes -- */

/**
 * @fn      gpio_get_config( gpio_pin_t, gpio_config_t* )
 * @brief   Gets the configuration of the specified GPIO pin.
 */
void gpio_get_config( gpio_pin_t pin, gpio_config_t* config );

/**
 * @fn      gpio_get_dir( gpio_pin_t )
 * @brief   Gets the I/O direction (in or out) of the specified GPIO pin.
 */
gpio_dir_t gpio_get_dir( gpio_pin_t pin );

/**
 * @fn      gpio_get_pullup_enabled( gpio_pin_t )
 * @brief   Gets the enablement of the pull-up resistor for the specified GPIO pin.
 * @note    This is only valid if the pin is configured as an input. This is not checked by the function.
 */
bool gpio_get_pullup_enabled( gpio_pin_t pin );

/**
 * @fn      gpio_get_state( gpio_pin_t )
 * @brief   Gets the state (low or high) of the specified GPIO pin.
 */
gpio_state_t gpio_get_state( gpio_pin_t pin );

/**
 * @fn      gpio_set_config( gpio_pin_t, gpio_config_t const* )
 * @brief   Sets the configuration of the specified GPIO pin.
 */
void gpio_set_config( gpio_pin_t pin, gpio_config_t const* config );

/**
 * @fn      gpio_set_dir( gpio_pin_t, gpio_dir_t )
 * @brief   Sets the I/O direction (in or out) of the specified GPIO pin.
 */
void gpio_set_dir( gpio_pin_t pin, gpio_dir_t dir );

/**
 * @fn      gpio_set_pullup_enabled( gpio_pin_t, bool )
 * @brief   Sets the enablement of the pull-up resistor for the specified GPIO pin.
 * @note    This is only valid if the pin is configured as an input. This is not checked by the function.
 */
void gpio_set_pullup_enabled( gpio_pin_t pin, bool enabled );

/**
 * @fn      gpio_set_state( gpio_pin_t, gpio_state_t )
 * @brief   Sets the state (low or high) of the specified GPIO pin.
 */
void gpio_set_state( gpio_pin_t pin, gpio_state_t state );

/**
 * @fn      gpio_toggle_state( gpio_pin_t )
 * @brief   Toggles the state of the specified GPIO pin.
 */
void gpio_toggle_state( gpio_pin_t pin );

#endif /* !defined( GPIO_GPIO_H ) */
