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

// Argument validation macros
#define validate_pin( _pin )                                                    \
    assert( ( _pin ) < GPIO_PIN_COUNT )
#define validate_dir( _dir )                                                    \
    assert( ( _dir ) < GPIO_DIR_COUNT )
#define validate_state( _state )                                                \
    assert( ( _state ) < GPIO_STATE_COUNT )

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
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D0_PORT,      _GPIO_PIN_ARDUINO_D0_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D1_PORT,      _GPIO_PIN_ARDUINO_D1_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D2_PORT,      _GPIO_PIN_ARDUINO_D2_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D3_PORT,      _GPIO_PIN_ARDUINO_D3_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D4_PORT,      _GPIO_PIN_ARDUINO_D4_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D5_PORT,      _GPIO_PIN_ARDUINO_D5_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D6_PORT,      _GPIO_PIN_ARDUINO_D6_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D7_PORT,      _GPIO_PIN_ARDUINO_D7_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D8_PORT,      _GPIO_PIN_ARDUINO_D8_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D9_PORT,      _GPIO_PIN_ARDUINO_D9_PIN    ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D10_PORT,     _GPIO_PIN_ARDUINO_D10_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D11_PORT,     _GPIO_PIN_ARDUINO_D11_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D12_PORT,     _GPIO_PIN_ARDUINO_D12_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D13_PORT,     _GPIO_PIN_ARDUINO_D13_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D14_PORT,     _GPIO_PIN_ARDUINO_D14_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D15_PORT,     _GPIO_PIN_ARDUINO_D15_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D16_PORT,     _GPIO_PIN_ARDUINO_D16_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D17_PORT,     _GPIO_PIN_ARDUINO_D17_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D18_PORT,     _GPIO_PIN_ARDUINO_D18_PIN   ),
    DEFINE_REGISTERS(   _GPIO_PIN_ARDUINO_D19_PORT,     _GPIO_PIN_ARDUINO_D19_PIN   ),
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
