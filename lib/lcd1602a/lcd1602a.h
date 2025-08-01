/**
 * @file    lcd1602a.h
 * @brief   Header for the LCD1602A driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-22
 */

#if !defined( LCD1602A_LCD1602A_H )
#define LCD1602A_LCD1602A_H

/* -- Includes -- */

#include <stdint.h>

#include "adc/adc.h"
#include "gpio/gpio.h"

/* -- Constants -- */

/**
 * @def     LCD1602A_ADDRESS_FIRST_LINE
 * @brief   DDRAM address for the first character in the first line.
 */
#define LCD1602A_ADDRESS_FIRST_LINE     ( 0x00 )

/**
 * @def     LCD1602A_ADDRESS_SECOND_LINE
 * @brief   DDRAM address for the first character in the second line.
 */
#define LCD1602A_ADDRESS_SECOND_LINE    ( 0x40 )

/* -- Types -- */

/**
 * @typedef lcd1602a_button_t
 * @brief   Enumeration of buttons supported by the LCD1602A shield.
 */
typedef uint8_t lcd1602a_button_t;
enum
{
    LCD1602A_BUTTON_NONE,           /**< No button is selected.                         */
    LCD1602A_BUTTON_UP,             /**< The UP button is selected.                     */
    LCD1602A_BUTTON_DOWN,           /**< The DOWN button is selected.                   */
    LCD1602A_BUTTON_LEFT,           /**< The LEFT button is selected.                   */
    LCD1602A_BUTTON_RIGHT,          /**< The RIGHT button is selected.                  */
    LCD1602A_BUTTON_SELECT,         /**< The SELECT button is selected.                 */
    LCD1602A_BUTTON_COUNT,          /**< Number of valid buttons.                       */
};

/**
 * @typedef lcd1602a_cfg_t
 * @brief   Struct containing configuration information for an LCD1602A shield.
 */
typedef struct
{
    gpio_pin_t      d4_pin;         /**< GPIO pin for the D4 input.                     */
    gpio_pin_t      d5_pin;         /**< GPIO pin for the D5 input.                     */
    gpio_pin_t      d6_pin;         /**< GPIO pin for the D6 input.                     */
    gpio_pin_t      d7_pin;         /**< GPIO pin for the D7 input.                     */
    gpio_pin_t      rs_pin;         /**< GPIO pin for the RS input.                     */
    gpio_pin_t      e_pin;          /**< GPIO pin for the E input.                      */
    adc_channel_t   btn_chnl;       /**< ADC channel for the button input.              */
} lcd1602a_cfg_t;

/* -- Procedure Prototypes -- */

/**
 * @fn      lcd1602a_cfg_default( lcd1602a_cfg_t* )
 * @brief   Initializes the specified configuration struct with the default configuration.
 */
void lcd1602a_cfg_default( lcd1602a_cfg_t* cfg );

/**
 * @fn      lcd1602a_clear( lcd1602a_cfg_t const* )
 * @brief   Clears the LCD display and returns the cursor to the home position.
 * @note    This function blocks for ~2 milliseconds.
 */
void lcd1602a_clear( lcd1602a_cfg_t const* cfg );

/**
 * @fn      lcd1602a_get_button( lcd1602a_cfg_t const* )
 * @brief   Returns the currently pressed button, if any.
 */
lcd1602a_button_t lcd1602a_get_button( lcd1602a_cfg_t const* cfg );

/**
 * @fn      lcd1602a_home( lcd1602a_cfg_t const* )
 * @brief   Returns the cursor to the home position, without changing any data contents.
 * @note    This function blocks for ~2 milliseconds.
 */
void lcd1602a_home( lcd1602a_cfg_t const* cfg );

/**
 * @fn      lcd1602a_init( lcd1602a_cfg_t const* )
 * @brief   Initializes the LCD1602A driver.
 * @note    Must be called prior to calling any other function in this module.
 */
void lcd1602a_init( lcd1602a_cfg_t const* cfg );

/**
 * @fn      lcd1602a_init_default( lcd1602a_cfg_t* )
 * @brief   Initializes the specified configuration struct with the default configuration, then immediately calls
 *          `lcd1602a_init()` with the initialized configuration.
 */
void lcd1602a_init_default( lcd1602a_cfg_t* cfg );

/**
 * @fn      lcd1602a_set_address( lcd1602a_cfg_t const*, uint8_t )
 * @brief   Sets the LCD1602A's DDRAM (i.e., data) address to the specified address.
 */
void lcd1602a_set_address( lcd1602a_cfg_t const* cfg, uint8_t addr );

/**
 * @fn      lcd1602a_write_char( lcd1602a_cfg_t const*, char )
 * @brief   Writes the specified character to the display.
 */
void lcd1602a_write_char( lcd1602a_cfg_t const* cfg, char c );

/**
 * @fn      lcd1602a_write_lines( lcd1602a_cfg_t const*, char const*, char const* )
 * @brief   Clears the display and writes the specified strings to each line.
 * @param   cfg
 *          Pointer to the LCD configuration struct.
 * @param   s1
 *          The null-terminated string to write to the first line.
 * @param   s2
 *          The null-terminated string to write to the second line.
 * @note    This function blocks for ~2 milliseconds.
 */
void lcd1602a_write_lines( lcd1602a_cfg_t const* cfg, char const* s1, char const* s2 );

/**
 * @fn      lcd1602a_write_string( lcd1602a_cfg_t const*, char const* )
 * @brief   Writes the specified null-terminated string to the display.
 */
void lcd1602a_write_string( lcd1602a_cfg_t const* cfg, char const* s );

#endif /* !defined( LCD1602A_LCD1602A_H ) */
