/**
 * @file    lcd1602.h
 * @brief   Header for the lcd1602 library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-08
 */

#if !defined( LCD1602_LCD1602_H )
#define LCD1602_LCD1602_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

#include "gpio/gpio.h"

/* -- Constants -- */

/**
 * @def     LCD1602_PIN_COUNT
 * @brief   Total number of GPIO pins for the LCD1602 module.
 */
#define LCD1602_PIN_COUNT       11

/**
 * @def     LCD1602_LINE_1_ADDR
 * @brief   DDRAM address for the beginning of the LCD's first line.
 */
#define LCD1602_LINE_1_ADDRESS  0x00

/**
 * @def     LCD1602_LINE_2_ADDR
 * @brief   DDRAM address for the beginning of the LCD's second line.
 */
#define LCD1602_LINE_2_ADDRESS  0x40

/**
 * @def     LCD1602_LINE_LENGTH
 * @brief   Maximum number of displayed characters per line.
 */
#define LCD1602_LINE_LENGTH     16

/* -- Types -- */

/**
 * @typedef lcd1602_cursor_t
 * @brief   Enumeration of the cursor options for the LCD1602.
 */
typedef uint8_t lcd1602_cursor_t;
enum
{
    LCD1602_CURSOR_NONE,            /**< No cursor is displayed.                        */
    LCD1602_CURSOR_UNDERSCORE,      /**< The underscore cursor is displayed.            */
    LCD1602_CURSOR_BOX,             /**< The blinking box cursor is displayed.          */
    LCD1602_CURSOR_BOTH,            /**< Both cursors are displayed.                    */

    LCD1602_CURSOR_COUNT,           /**< Number of valid cursor options.                */
};

/**
 * @typedef lcd1602_autoshift_t
 * @brief   Enumeration of the automatic shift options for the LCD1602.
 */
typedef uint8_t lcd1602_autoshift_t;
enum
{
    LCD1602_AUTOSHIFT_CURSOR_RIGHT, /** Cursor shifts to the right after each char.     */
    LCD1602_AUTOSHIFT_CURSOR_LEFT,  /** Cursor shifts to the left after each char.      */
    LCD1602_AUTOSHIFT_DISPLAY_RIGHT,/** Display shifts to the right after each char.    */
    LCD1602_AUTOSHIFT_DISPLAY_LEFT, /** Display shifts to the left after each char.     */

    LCD1602_AUTOSHIFT_COUNT,        /**< Number of valid autoshift options.             */
};

/**
 * @struct  lcd1602_config_t
 * @brief   Struct containing configuration information for an LCD1602 module.
 */
typedef struct
{
    bool                data_8;     /**< Set to `true` if the data bus uses 8 pins.     */
    bool                lines_2;    /**< Set to `true` for 2-line display.              */
    bool                font_large; /**< Set to `true` for large font.                  */
} lcd1602_config_t;

/**
 * @struct  lcd1602_pins_t
 * @brief   Struct containing pinout information for an LCD1602 module.
 */
typedef union
{
    struct
    {
        gpio_pin_t      rs;         /**< The GPIO pin for the RS input.                 */
        gpio_pin_t      rw;         /**< The GPIO pin for the RW input.                 */
        gpio_pin_t      e;          /**< The GPIO pin for the E input.                  */
        gpio_pin_t      d0;         /**< The GPIO pin for the D0 input.                 */
        gpio_pin_t      d1;         /**< The GPIO pin for the D1 input.                 */
        gpio_pin_t      d2;         /**< The GPIO pin for the D2 input.                 */
        gpio_pin_t      d3;         /**< The GPIO pin for the D3 input.                 */
        gpio_pin_t      d4;         /**< The GPIO pin for the D4 input.                 */
        gpio_pin_t      d5;         /**< The GPIO pin for the D5 input.                 */
        gpio_pin_t      d6;         /**< The GPIO pin for the D6 input.                 */
        gpio_pin_t      d7;         /**< The GPIO pin for the D7 input.                 */
    };
    gpio_pin_t          all[ LCD1602_PIN_COUNT ];
                                    /**^ An array containing all GPIO pins.             */
} lcd1602_pins_t;

// Ensure struct was correctly sized
_Static_assert( sizeof( lcd1602_pins_t ) == sizeof( gpio_pin_t ) * LCD1602_PIN_COUNT, "Wrong struct size!" );

/**
 * @struct  lcd1602_t
 * @brief   Struct containing configuration information for an LCD1602 module.
 */
typedef struct
{
    lcd1602_config_t    config;     /**< Module configuration.                          */
    lcd1602_pins_t      pins;       /**< Module pinout.                                 */
} lcd1602_t;

/* -- Procedure Prototypes -- */

/**
 * @fn      lcd1602_clear( lcd1602_t const * )
 * @brief   Clears all text from the specified LCD and returns the cursor to the home position.
 */
void lcd1602_clear( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_go_line_1( lcd1602_t const * )
 * @brief   Moves the cursor to the beginning of line 1.
 */
void lcd1602_go_line_1( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_go_line_2( lcd1602_t const * )
 * @brief   Moves the cursor to the beginning of line 2.
 */
void lcd1602_go_line_2( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_home( lcd1602_t const * )
 * @brief   Returns the cursor to the home position.
 */
void lcd1602_home( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_init( lcd1602_t const * )
 * @brief   Initializes all GPIO pins for the specified LCD.
 */
void lcd1602_init( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_set_addr( lcd1602_t const *, uint8_t )
 * @brief   Sets the DDRAM address for the specified LCD.
 */
void lcd1602_set_address( lcd1602_t const * lcd, uint8_t addr );

/**
 * @fn      lcd1602_set_autoshift( lcd1602_t const *, lcd1602_autoshift_t )
 * @brief   Sets the autoshift option for the specified LCD.
 */
void lcd1602_set_autoshift( lcd1602_t const * lcd, lcd1602_autoshift_t autoshift );

/**
 * @fn      lcd1602_set_display( lcd1602_t const *, bool, bool, bool )
 * @brief   Sets the display mode for the specified LCD.
 * @param   lcd
 *          Pointer to the LCD struct.
 * @param   display_on
 *          If set to `true`, the entire display is turned on.
 * @param   cursor
 *          The cursor mode to use.
 */
void lcd1602_set_display( lcd1602_t const * lcd, bool display_on, lcd1602_cursor_t cursor );

/**
 * @fn      lcd1602_shift_left( lcd1602_t const * )
 * @brief   Shifts the entire display (including the cursor position) to the left.
 * @note    This means that text will appear to scroll from right to left.
 */
void lcd1602_shift_left( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_shift_right( lcd1602_t const * )
 * @brief   Shifts the entire display (including the cursor position) to the right.
 * @note    This means that text will appear to scroll from left to right.
 */
void lcd1602_shift_right( lcd1602_t const * lcd );

/**
 * @fn      lcd1602_write( lcd1602_t const *, char const * )
 * @brief   Writes the specified null-terminated string to the current cursor location.
 */
void lcd1602_write( lcd1602_t const * lcd, char const * str );

/**
 * @fn      lcd1602_write_delay( lcd1602_t const *, char const *, uint16_t )
 * @brief   Writes the specified null-terminated string to the current cursor location, pausing for the specified
 *          number of milliseconds between each character.
 */
void lcd1602_write_delay( lcd1602_t const * lcd, char const * str, uint16_t delay_ms );

/**
 * @fn      lcd1602_write_lines( lcd1602_t const *, char const *, char const * )
 * @brief   Replaces the current content of the display with the specified strings.
 */
void lcd1602_write_lines( lcd1602_t const * lcd, char const * line1, char const * line2 );

#endif /* !defined( LCD1602_LCD1602_H ) */
