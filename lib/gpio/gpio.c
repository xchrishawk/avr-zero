/**
 * @file    gpio.c
 * @brief   Implementation for the GPIO driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

/* -- Includes -- */

#include <assert.h>

#include <avr/io.h>

#include "zero/bit_ops.h"
#include "zero/pinout.h"
#include "zero/register.h"
#include "zero/utility.h"

#include "gpio.h"

/* -- Macros -- */

// Helper macro for the register table below
#define DEFINE_REGISTERS( _port, _pin )                                         \
    _DEFINE_REGISTERS( _port, _pin )
#define _DEFINE_REGISTERS( _port, _pin )                                        \
    { REGISTER_ADDR( DDR ## _port ),  ( 1 << DD ## _port ## _pin ),             \
      REGISTER_ADDR( PORT ## _port ), ( 1 << PORT ## _port ## _pin ),           \
      REGISTER_ADDR( PIN ## _port ),  ( 1 << PIN ## _port ## _pin ) }

// Helper macros to validate arguments
#define validate_pin( _pin )        validate_enum( _pin,    GPIO_PIN_COUNT )
#define validate_dir( _dir )        validate_enum( _dir,    GPIO_DIR_COUNT )
#define validate_state( _state )    validate_enum( _state,  GPIO_STATE_COUNT )

/* -- Constants -- */

// Register lookup table for each GPIO pin
static struct
{
    register_t  ddr_reg;
    uint8_t     ddr_mask;
    register_t  out_reg;
    uint8_t     out_mask;
    register_t  in_reg;
    uint8_t     in_mask;
}
const s_reg_tbl[] =
{
#if( _GPIO_PIN_COUNT > 0 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D00_PORT,     _GPIO_PIN_ARDUINO_D00_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 1 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D01_PORT,     _GPIO_PIN_ARDUINO_D01_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 2 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D02_PORT,     _GPIO_PIN_ARDUINO_D02_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 3 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D03_PORT,     _GPIO_PIN_ARDUINO_D03_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 4 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D04_PORT,     _GPIO_PIN_ARDUINO_D04_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 5 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D05_PORT,     _GPIO_PIN_ARDUINO_D05_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 6 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D06_PORT,     _GPIO_PIN_ARDUINO_D06_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 7 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D07_PORT,     _GPIO_PIN_ARDUINO_D07_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 8 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D08_PORT,     _GPIO_PIN_ARDUINO_D08_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 9 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D09_PORT,     _GPIO_PIN_ARDUINO_D09_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 10 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D10_PORT,     _GPIO_PIN_ARDUINO_D10_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 11 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D11_PORT,     _GPIO_PIN_ARDUINO_D11_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 12 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D12_PORT,     _GPIO_PIN_ARDUINO_D12_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 13 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D13_PORT,     _GPIO_PIN_ARDUINO_D13_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 14 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D14_PORT,     _GPIO_PIN_ARDUINO_D14_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 15 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D15_PORT,     _GPIO_PIN_ARDUINO_D15_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 16 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D16_PORT,     _GPIO_PIN_ARDUINO_D16_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 17 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D17_PORT,     _GPIO_PIN_ARDUINO_D17_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 18 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D18_PORT,     _GPIO_PIN_ARDUINO_D18_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 19 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D19_PORT,     _GPIO_PIN_ARDUINO_D19_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 20 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D20_PORT,     _GPIO_PIN_ARDUINO_D20_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 21 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D21_PORT,     _GPIO_PIN_ARDUINO_D21_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 22 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D22_PORT,     _GPIO_PIN_ARDUINO_D22_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 23 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D23_PORT,     _GPIO_PIN_ARDUINO_D23_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 24 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D24_PORT,     _GPIO_PIN_ARDUINO_D24_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 25 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D25_PORT,     _GPIO_PIN_ARDUINO_D25_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 26 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D26_PORT,     _GPIO_PIN_ARDUINO_D26_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 27 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D27_PORT,     _GPIO_PIN_ARDUINO_D27_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 28 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D28_PORT,     _GPIO_PIN_ARDUINO_D28_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 29 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D29_PORT,     _GPIO_PIN_ARDUINO_D29_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 30 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D30_PORT,     _GPIO_PIN_ARDUINO_D30_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 31 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D31_PORT,     _GPIO_PIN_ARDUINO_D31_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 32 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D32_PORT,     _GPIO_PIN_ARDUINO_D32_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 33 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D33_PORT,     _GPIO_PIN_ARDUINO_D33_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 34 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D34_PORT,     _GPIO_PIN_ARDUINO_D34_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 35 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D35_PORT,     _GPIO_PIN_ARDUINO_D35_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 36 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D36_PORT,     _GPIO_PIN_ARDUINO_D36_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 37 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D37_PORT,     _GPIO_PIN_ARDUINO_D37_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 38 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D38_PORT,     _GPIO_PIN_ARDUINO_D38_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 39 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D39_PORT,     _GPIO_PIN_ARDUINO_D39_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 40 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D40_PORT,     _GPIO_PIN_ARDUINO_D40_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 41 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D41_PORT,     _GPIO_PIN_ARDUINO_D41_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 42 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D42_PORT,     _GPIO_PIN_ARDUINO_D42_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 43 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D43_PORT,     _GPIO_PIN_ARDUINO_D43_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 44 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D44_PORT,     _GPIO_PIN_ARDUINO_D44_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 45 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D45_PORT,     _GPIO_PIN_ARDUINO_D45_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 46 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D46_PORT,     _GPIO_PIN_ARDUINO_D46_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 47 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D47_PORT,     _GPIO_PIN_ARDUINO_D47_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 48 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D48_PORT,     _GPIO_PIN_ARDUINO_D48_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 49 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D49_PORT,     _GPIO_PIN_ARDUINO_D49_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 50 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D50_PORT,     _GPIO_PIN_ARDUINO_D50_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 51 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D51_PORT,     _GPIO_PIN_ARDUINO_D51_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 52 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D52_PORT,     _GPIO_PIN_ARDUINO_D52_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 53 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D53_PORT,     _GPIO_PIN_ARDUINO_D53_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 54 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D54_PORT,     _GPIO_PIN_ARDUINO_D54_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 55 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D55_PORT,     _GPIO_PIN_ARDUINO_D55_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 56 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D56_PORT,     _GPIO_PIN_ARDUINO_D56_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 57 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D57_PORT,     _GPIO_PIN_ARDUINO_D57_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 58 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D58_PORT,     _GPIO_PIN_ARDUINO_D58_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 59 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D59_PORT,     _GPIO_PIN_ARDUINO_D59_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 60 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D60_PORT,     _GPIO_PIN_ARDUINO_D60_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 61 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D61_PORT,     _GPIO_PIN_ARDUINO_D61_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 62 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D62_PORT,     _GPIO_PIN_ARDUINO_D62_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 63 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D63_PORT,     _GPIO_PIN_ARDUINO_D63_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 64 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D64_PORT,     _GPIO_PIN_ARDUINO_D64_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 65 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D65_PORT,     _GPIO_PIN_ARDUINO_D65_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 66 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D66_PORT,     _GPIO_PIN_ARDUINO_D66_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 67 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D67_PORT,     _GPIO_PIN_ARDUINO_D67_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 68 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D68_PORT,     _GPIO_PIN_ARDUINO_D68_PIN   ),
#endif
#if( _GPIO_PIN_COUNT > 69 )
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D69_PORT,     _GPIO_PIN_ARDUINO_D69_PIN   ),
#endif
};

// Ensure register table has an entry for every defined pin
_Static_assert( array_count( s_reg_tbl ) == GPIO_PIN_COUNT, "s_reg_tbl must have correct number of entries!" );

/* -- Procedures -- */

void gpio_get_config( gpio_pin_t pin, gpio_config_t* config )
{
    config->dir = gpio_get_dir( pin );
    if( config->dir == GPIO_DIR_OUT )
        config->state = gpio_get_state( pin );
    else if( config->dir == GPIO_DIR_IN )
        config->pullup_en = gpio_get_pullup_enabled( pin );

} /* gpio_get_config() */


gpio_dir_t gpio_get_dir( gpio_pin_t pin )
{
    validate_pin( pin );

    return( is_bitmask_set( *s_reg_tbl[ pin ].ddr_reg,
                             s_reg_tbl[ pin ].ddr_mask ) ?
            GPIO_DIR_OUT :
            GPIO_DIR_IN );

} /* gpio_get_dir() */


bool gpio_get_pullup_enabled( gpio_pin_t pin )
{
    validate_pin( pin );

    return( ( bool )is_bitmask_set( *s_reg_tbl[ pin ].out_reg,
                                     s_reg_tbl[ pin ].out_mask ) );

} /* gpio_get_pullup_enabled() */


gpio_state_t gpio_get_state( gpio_pin_t pin )
{
    validate_pin( pin );

    return( is_bitmask_set( *s_reg_tbl[ pin ].in_reg,
                             s_reg_tbl[ pin ].in_mask ) ?
            GPIO_STATE_HIGH :
            GPIO_STATE_LOW );

} /* gpio_get_state() */


void gpio_set_config( gpio_pin_t pin, gpio_config_t const* config )
{
    gpio_set_dir( pin, config->dir );
    if( config->dir == GPIO_DIR_OUT )
        gpio_set_state( pin, config->state );
    else if( config->dir == GPIO_DIR_IN )
        gpio_set_pullup_enabled( pin, config->pullup_en );

} /* gpio_set_config() */


void gpio_set_dir( gpio_pin_t pin, gpio_dir_t dir )
{
    validate_pin( pin );
    validate_dir( dir );

    assign_bitmask( *s_reg_tbl[ pin ].ddr_reg,
                     s_reg_tbl[ pin ].ddr_mask,
                     dir == GPIO_DIR_OUT );

} /* gpio_set_dir() */


void gpio_set_pullup_enabled( gpio_pin_t pin, bool enabled )
{
    validate_pin( pin );

    assign_bitmask( *s_reg_tbl[ pin ].out_reg,
                     s_reg_tbl[ pin ].out_mask,
                     enabled );

} /* gpio_set_pullup_enabled() */


void gpio_set_state( gpio_pin_t pin, gpio_state_t state )
{
    validate_pin( pin );
    validate_state( state );

    assign_bitmask( *s_reg_tbl[ pin ].out_reg,
                     s_reg_tbl[ pin ].out_mask,
                     state == GPIO_STATE_HIGH );

} /* gpio_set_state() */


void gpio_toggle_state( gpio_pin_t pin )
{
    validate_pin( pin );

    toggle_bitmask( *s_reg_tbl[ pin ].out_reg,
                     s_reg_tbl[ pin ].out_mask );

} /* gpio_toggle_state() */
