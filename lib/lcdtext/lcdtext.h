/**
 * @file    lcdtext.h
 * @brief   Header for the lcdtext library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-08
 */

#if !defined( LCDTEXT_LCDTEXT_H )
#define LCDTEXT_LCDTEXT_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

#include "gpio/gpio.h"

/* -- Constants -- */

/**
 * @def     LCDTEXT_PIN_COUNT
 * @brief   Total number of GPIO pins for the LCD 1602 / 2004 modules.
 */
#define LCDTEXT_PIN_COUNT           11

/**
 * @def     LCDTEXT_LINE_1_ADDR
 * @brief   DDRAM address for the beginning of the LCD's first line.
 */
#define LCDTEXT_LINE_1_ADDRESS      0x00

/**
 * @def     LCDTEXT_LINE_2_ADDR
 * @brief   DDRAM address for the beginning of the LCD's second line.
 */
#define LCDTEXT_LINE_2_ADDRESS      0x40

/**
 * @def     LCDTEXT_LINE_3_ADDR
 * @brief   DDRAM address for the beginning of the LCD's third line.
 */
#define LCDTEXT_LINE_3_ADDRESS      0x14

/**
 * @def     LCDTEXT_LINE_4_ADDR
 * @brief   DDRAM address for the beginning of the LCD's fourth line.
 */
#define LCDTEXT_LINE_4_ADDRESS      0x54

/**
 * @def     LCDTEXT_1602_LINE_LENGTH
 * @brief   Maximum number of displayed characters per line for the LCD1602.
 */
#define LCDTEXT_1602_LINE_LENGTH    16

/**
 * @def     LCDTEXT_2004_LINE_LENGTH
 * @brief   Maximum number of displayed characters per line for the LCD2004.
 */
#define LCDTEXT_2004_LINE_LENGTH    20

/* -- Types -- */

/**
 * @typedef lcdtext_cursor_t
 * @brief   Enumeration of the cursor options for the LCDTEXT.
 */
typedef uint8_t lcdtext_cursor_t;
enum
{
    LCDTEXT_CURSOR_NONE,            /**< No cursor is displayed.                        */
    LCDTEXT_CURSOR_UNDERSCORE,      /**< The underscore cursor is displayed.            */
    LCDTEXT_CURSOR_BOX,             /**< The blinking box cursor is displayed.          */
    LCDTEXT_CURSOR_BOTH,            /**< Both cursors are displayed.                    */

    LCDTEXT_CURSOR_COUNT,           /**< Number of valid cursor options.                */
};

/**
 * @typedef lcdtext_autoshift_t
 * @brief   Enumeration of the automatic shift options for the LCDTEXT.
 */
typedef uint8_t lcdtext_autoshift_t;
enum
{
    LCDTEXT_AUTOSHIFT_CURSOR_RIGHT, /** Cursor shifts to the right after each char.     */
    LCDTEXT_AUTOSHIFT_CURSOR_LEFT,  /** Cursor shifts to the left after each char.      */
    LCDTEXT_AUTOSHIFT_DISPLAY_RIGHT,/** Display shifts to the right after each char.    */
    LCDTEXT_AUTOSHIFT_DISPLAY_LEFT, /** Display shifts to the left after each char.     */

    LCDTEXT_AUTOSHIFT_COUNT,        /**< Number of valid autoshift options.             */
};

/**
 * @struct  lcdtext_config_t
 * @brief   Struct containing configuration information for an LCDTEXT module.
 */
typedef struct
{
    bool                data_8;     /**< Set to `true` if the data bus uses 8 pins.     */
    bool                lines_2;    /**< Set to `true` for 2-line display.              */
    bool                font_large; /**< Set to `true` for large font.                  */
} lcdtext_config_t;

/**
 * @struct  lcdtext_pins_t
 * @brief   Struct containing pinout information for an LCDTEXT module.
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
    gpio_pin_t          all[ LCDTEXT_PIN_COUNT ];
                                    /**^ An array containing all GPIO pins.             */
} lcdtext_pins_t;

// Ensure struct was correctly sized
_Static_assert( sizeof( lcdtext_pins_t ) == sizeof( gpio_pin_t ) * LCDTEXT_PIN_COUNT, "Wrong struct size!" );

/**
 * @struct  lcdtext_t
 * @brief   Struct containing configuration information for an LCDTEXT module.
 */
typedef struct
{
    lcdtext_config_t    config;     /**< Module configuration.                          */
    lcdtext_pins_t      pins;       /**< Module pinout.                                 */
} lcdtext_t;

/* -- Procedure Prototypes -- */

/**
 * @fn      lcdtext_clear( lcdtext_t const * )
 * @brief   Clears all text from the specified LCD and returns the cursor to the home position.
 */
void lcdtext_clear( lcdtext_t const * lcd );

/**
 * @fn      lcdtext_home( lcdtext_t const * )
 * @brief   Returns the cursor to the home position.
 */
void lcdtext_home( lcdtext_t const * lcd );

/**
 * @fn      lcdtext_init( lcdtext_t const * )
 * @brief   Initializes all GPIO pins for the specified LCD.
 */
void lcdtext_init( lcdtext_t const * lcd );

/**
 * @fn      lcdtext_set_addr( lcdtext_t const *, uint8_t )
 * @brief   Sets the DDRAM address for the specified LCD.
 */
void lcdtext_set_address( lcdtext_t const * lcd, uint8_t addr );

/**
 * @fn      lcdtext_set_autoshift( lcdtext_t const *, lcdtext_autoshift_t )
 * @brief   Sets the autoshift option for the specified LCD.
 */
void lcdtext_set_autoshift( lcdtext_t const * lcd, lcdtext_autoshift_t autoshift );

/**
 * @fn      lcdtext_set_display( lcdtext_t const *, bool, bool, bool )
 * @brief   Sets the display mode for the specified LCD.
 * @param   lcd
 *          Pointer to the LCD struct.
 * @param   display_on
 *          If set to `true`, the entire display is turned on.
 * @param   cursor
 *          The cursor mode to use.
 */
void lcdtext_set_display( lcdtext_t const * lcd, bool display_on, lcdtext_cursor_t cursor );

/**
 * @fn      lcdtext_shift_left( lcdtext_t const * )
 * @brief   Shifts the entire display (including the cursor position) to the left.
 * @note    This means that text will appear to scroll from right to left.
 */
void lcdtext_shift_left( lcdtext_t const * lcd );

/**
 * @fn      lcdtext_shift_right( lcdtext_t const * )
 * @brief   Shifts the entire display (including the cursor position) to the right.
 * @note    This means that text will appear to scroll from left to right.
 */
void lcdtext_shift_right( lcdtext_t const * lcd );

/**
 * @fn      lcdtext_write( lcdtext_t const *, char const * )
 * @brief   Writes the specified null-terminated string to the current cursor location.
 */
void lcdtext_write( lcdtext_t const * lcd, char const * str );

/**
 * @fn      lcdtext_write_delay( lcdtext_t const *, char const *, uint16_t )
 * @brief   Writes the specified null-terminated string to the current cursor location, pausing for the specified
 *          number of milliseconds between each character.
 */
void lcdtext_write_delay( lcdtext_t const * lcd, char const * str, uint16_t delay_ms );

/**
 * @fn      lcdtext_1602_write_lines( lcdtext_t const *, char const *, char const * )
 * @brief   Replaces the current content of the LCD1602 display with the specified strings.
 */
void lcdtext_1602_write_lines( lcdtext_t const * lcd, char const * line1, char const * line2 );

#endif /* !defined( LCDTEXT_LCDTEXT_H ) */
