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

#include "zero/pinout.h"

/* -- Types -- */

/**
 * @typedef gpio_pin_t
 * @brief   Enumeration of supported GPIO pins.
 */
typedef uint8_t gpio_pin_t;
enum
{
#if( _GPIO_PIN_COUNT > 0 )
    GPIO_PIN_ARDUINO_D00,           /**< Arduino GPIO pin D0.                           */
#endif
#if( _GPIO_PIN_COUNT > 1 )
    GPIO_PIN_ARDUINO_D01,           /**< Arduino GPIO pin D1.                           */
#endif
#if( _GPIO_PIN_COUNT > 2 )
    GPIO_PIN_ARDUINO_D02,           /**< Arduino GPIO pin D2.                           */
#endif
#if( _GPIO_PIN_COUNT > 3 )
    GPIO_PIN_ARDUINO_D03,           /**< Arduino GPIO pin D3.                           */
#endif
#if( _GPIO_PIN_COUNT > 4 )
    GPIO_PIN_ARDUINO_D04,           /**< Arduino GPIO pin D4.                           */
#endif
#if( _GPIO_PIN_COUNT > 5 )
    GPIO_PIN_ARDUINO_D05,           /**< Arduino GPIO pin D5.                           */
#endif
#if( _GPIO_PIN_COUNT > 6 )
    GPIO_PIN_ARDUINO_D06,           /**< Arduino GPIO pin D6.                           */
#endif
#if( _GPIO_PIN_COUNT > 7 )
    GPIO_PIN_ARDUINO_D07,           /**< Arduino GPIO pin D7.                           */
#endif
#if( _GPIO_PIN_COUNT > 8 )
    GPIO_PIN_ARDUINO_D08,           /**< Arduino GPIO pin D8.                           */
#endif
#if( _GPIO_PIN_COUNT > 9 )
    GPIO_PIN_ARDUINO_D09,           /**< Arduino GPIO pin D9.                           */
#endif
#if( _GPIO_PIN_COUNT > 10 )
    GPIO_PIN_ARDUINO_D10,           /**< Arduino GPIO pin D10.                          */
#endif
#if( _GPIO_PIN_COUNT > 11 )
    GPIO_PIN_ARDUINO_D11,           /**< Arduino GPIO pin D11.                          */
#endif
#if( _GPIO_PIN_COUNT > 12 )
    GPIO_PIN_ARDUINO_D12,           /**< Arduino GPIO pin D12.                          */
#endif
#if( _GPIO_PIN_COUNT > 13 )
    GPIO_PIN_ARDUINO_D13,           /**< Arduino GPIO pin D13.                          */
#endif
#if( _GPIO_PIN_COUNT > 14 )
    GPIO_PIN_ARDUINO_D14,           /**< Arduino GPIO pin D14.                          */
#endif
#if( _GPIO_PIN_COUNT > 15 )
    GPIO_PIN_ARDUINO_D15,           /**< Arduino GPIO pin D15.                          */
#endif
#if( _GPIO_PIN_COUNT > 16 )
    GPIO_PIN_ARDUINO_D16,           /**< Arduino GPIO pin D16.                          */
#endif
#if( _GPIO_PIN_COUNT > 17 )
    GPIO_PIN_ARDUINO_D17,           /**< Arduino GPIO pin D17.                          */
#endif
#if( _GPIO_PIN_COUNT > 18 )
    GPIO_PIN_ARDUINO_D18,           /**< Arduino GPIO pin D18.                          */
#endif
#if( _GPIO_PIN_COUNT > 19 )
    GPIO_PIN_ARDUINO_D19,           /**< Arduino GPIO pin D19.                          */
#endif
#if( _GPIO_PIN_COUNT > 20 )
    GPIO_PIN_ARDUINO_D20,           /**< Arduino GPIO pin D20.                          */
#endif
#if( _GPIO_PIN_COUNT > 21 )
    GPIO_PIN_ARDUINO_D21,           /**< Arduino GPIO pin D21.                          */
#endif
#if( _GPIO_PIN_COUNT > 22 )
    GPIO_PIN_ARDUINO_D22,           /**< Arduino GPIO pin D22.                          */
#endif
#if( _GPIO_PIN_COUNT > 23 )
    GPIO_PIN_ARDUINO_D23,           /**< Arduino GPIO pin D23.                          */
#endif
#if( _GPIO_PIN_COUNT > 24 )
    GPIO_PIN_ARDUINO_D24,           /**< Arduino GPIO pin D24.                          */
#endif
#if( _GPIO_PIN_COUNT > 25 )
    GPIO_PIN_ARDUINO_D25,           /**< Arduino GPIO pin D25.                          */
#endif
#if( _GPIO_PIN_COUNT > 26 )
    GPIO_PIN_ARDUINO_D26,           /**< Arduino GPIO pin D26.                          */
#endif
#if( _GPIO_PIN_COUNT > 27 )
    GPIO_PIN_ARDUINO_D27,           /**< Arduino GPIO pin D27.                          */
#endif
#if( _GPIO_PIN_COUNT > 28 )
    GPIO_PIN_ARDUINO_D28,           /**< Arduino GPIO pin D28.                          */
#endif
#if( _GPIO_PIN_COUNT > 29 )
    GPIO_PIN_ARDUINO_D29,           /**< Arduino GPIO pin D29.                          */
#endif
#if( _GPIO_PIN_COUNT > 30 )
    GPIO_PIN_ARDUINO_D30,           /**< Arduino GPIO pin D30.                          */
#endif
#if( _GPIO_PIN_COUNT > 31 )
    GPIO_PIN_ARDUINO_D31,           /**< Arduino GPIO pin D31.                          */
#endif
#if( _GPIO_PIN_COUNT > 32 )
    GPIO_PIN_ARDUINO_D32,           /**< Arduino GPIO pin D32.                          */
#endif
#if( _GPIO_PIN_COUNT > 33 )
    GPIO_PIN_ARDUINO_D33,           /**< Arduino GPIO pin D33.                          */
#endif
#if( _GPIO_PIN_COUNT > 34 )
    GPIO_PIN_ARDUINO_D34,           /**< Arduino GPIO pin D34.                          */
#endif
#if( _GPIO_PIN_COUNT > 35 )
    GPIO_PIN_ARDUINO_D35,           /**< Arduino GPIO pin D35.                          */
#endif
#if( _GPIO_PIN_COUNT > 36 )
    GPIO_PIN_ARDUINO_D36,           /**< Arduino GPIO pin D36.                          */
#endif
#if( _GPIO_PIN_COUNT > 37 )
    GPIO_PIN_ARDUINO_D37,           /**< Arduino GPIO pin D37.                          */
#endif
#if( _GPIO_PIN_COUNT > 38 )
    GPIO_PIN_ARDUINO_D38,           /**< Arduino GPIO pin D38.                          */
#endif
#if( _GPIO_PIN_COUNT > 39 )
    GPIO_PIN_ARDUINO_D39,           /**< Arduino GPIO pin D39.                          */
#endif
#if( _GPIO_PIN_COUNT > 40 )
    GPIO_PIN_ARDUINO_D40,           /**< Arduino GPIO pin D40.                          */
#endif
#if( _GPIO_PIN_COUNT > 41 )
    GPIO_PIN_ARDUINO_D41,           /**< Arduino GPIO pin D41.                          */
#endif
#if( _GPIO_PIN_COUNT > 42 )
    GPIO_PIN_ARDUINO_D42,           /**< Arduino GPIO pin D42.                          */
#endif
#if( _GPIO_PIN_COUNT > 43 )
    GPIO_PIN_ARDUINO_D43,           /**< Arduino GPIO pin D43.                          */
#endif
#if( _GPIO_PIN_COUNT > 44 )
    GPIO_PIN_ARDUINO_D44,           /**< Arduino GPIO pin D44.                          */
#endif
#if( _GPIO_PIN_COUNT > 45 )
    GPIO_PIN_ARDUINO_D45,           /**< Arduino GPIO pin D45.                          */
#endif
#if( _GPIO_PIN_COUNT > 46 )
    GPIO_PIN_ARDUINO_D46,           /**< Arduino GPIO pin D46.                          */
#endif
#if( _GPIO_PIN_COUNT > 47 )
    GPIO_PIN_ARDUINO_D47,           /**< Arduino GPIO pin D47.                          */
#endif
#if( _GPIO_PIN_COUNT > 48 )
    GPIO_PIN_ARDUINO_D48,           /**< Arduino GPIO pin D48.                          */
#endif
#if( _GPIO_PIN_COUNT > 49 )
    GPIO_PIN_ARDUINO_D49,           /**< Arduino GPIO pin D49.                          */
#endif
#if( _GPIO_PIN_COUNT > 50 )
    GPIO_PIN_ARDUINO_D50,           /**< Arduino GPIO pin D50.                          */
#endif
#if( _GPIO_PIN_COUNT > 51 )
    GPIO_PIN_ARDUINO_D51,           /**< Arduino GPIO pin D51.                          */
#endif
#if( _GPIO_PIN_COUNT > 52 )
    GPIO_PIN_ARDUINO_D52,           /**< Arduino GPIO pin D52.                          */
#endif
#if( _GPIO_PIN_COUNT > 53 )
    GPIO_PIN_ARDUINO_D53,           /**< Arduino GPIO pin D53.                          */
#endif
#if( _GPIO_PIN_COUNT > 54 )
    GPIO_PIN_ARDUINO_D54,           /**< Arduino GPIO pin D54.                          */
#endif
#if( _GPIO_PIN_COUNT > 55 )
    GPIO_PIN_ARDUINO_D55,           /**< Arduino GPIO pin D55.                          */
#endif
#if( _GPIO_PIN_COUNT > 56 )
    GPIO_PIN_ARDUINO_D56,           /**< Arduino GPIO pin D56.                          */
#endif
#if( _GPIO_PIN_COUNT > 57 )
    GPIO_PIN_ARDUINO_D57,           /**< Arduino GPIO pin D57.                          */
#endif
#if( _GPIO_PIN_COUNT > 58 )
    GPIO_PIN_ARDUINO_D58,           /**< Arduino GPIO pin D58.                          */
#endif
#if( _GPIO_PIN_COUNT > 59 )
    GPIO_PIN_ARDUINO_D59,           /**< Arduino GPIO pin D59.                          */
#endif
#if( _GPIO_PIN_COUNT > 60 )
    GPIO_PIN_ARDUINO_D60,           /**< Arduino GPIO pin D60.                          */
#endif
#if( _GPIO_PIN_COUNT > 61 )
    GPIO_PIN_ARDUINO_D61,           /**< Arduino GPIO pin D61.                          */
#endif
#if( _GPIO_PIN_COUNT > 62 )
    GPIO_PIN_ARDUINO_D62,           /**< Arduino GPIO pin D62.                          */
#endif
#if( _GPIO_PIN_COUNT > 63 )
    GPIO_PIN_ARDUINO_D63,           /**< Arduino GPIO pin D63.                          */
#endif
#if( _GPIO_PIN_COUNT > 64 )
    GPIO_PIN_ARDUINO_D64,           /**< Arduino GPIO pin D64.                          */
#endif
#if( _GPIO_PIN_COUNT > 65 )
    GPIO_PIN_ARDUINO_D65,           /**< Arduino GPIO pin D65.                          */
#endif
#if( _GPIO_PIN_COUNT > 66 )
    GPIO_PIN_ARDUINO_D66,           /**< Arduino GPIO pin D66.                          */
#endif
#if( _GPIO_PIN_COUNT > 67 )
    GPIO_PIN_ARDUINO_D67,           /**< Arduino GPIO pin D67.                          */
#endif
#if( _GPIO_PIN_COUNT > 68 )
    GPIO_PIN_ARDUINO_D68,           /**< Arduino GPIO pin D68.                          */
#endif
#if( _GPIO_PIN_COUNT > 69 )
    GPIO_PIN_ARDUINO_D69,           /**< Arduino GPIO pin D69.                          */
#endif

    GPIO_PIN_COUNT,                 /**< Number of valid GPIO pins.                     */

    GPIO_PIN_INVALID                /**< Invalid, unspecified, or unknown GPIO pin.     */
        = GPIO_PIN_COUNT,
    GPIO_PIN_ARDUINO_BUILT_IN_LED   /**< Arduino built-in LED.                          */
        = GPIO_PIN_ARDUINO_D13,
};

// Ensure pin count is correct
_Static_assert( GPIO_PIN_COUNT == _GPIO_PIN_COUNT, "GPIO pin count is incorrect!" );

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
