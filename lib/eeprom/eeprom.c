/**
 * @file    eeprom.c
 * @brief   Implementation for the eeprom library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-16
 */

/* -- Includes -- */

#include <avr/interrupt.h>
#include <avr/io.h>

#include "zero/bit_ops.h"

#include "eeprom.h"

/* -- Procedure Prototypes -- */

/**
 * @fn      set_addr( eeprom_addr_t )
 * @brief   Sets the address in the `EEARH` and `EEARL` registers.
 */
static void set_addr( eeprom_addr_t addr );

/* -- Procedures -- */

uint8_t eeprom_read_byte( eeprom_addr_t addr )
{
    // EEPE must be clear before reading
    wait_bit_clear( EECR, EEPE );

    // Set address and write EERE bit
    EEAR = addr;
    set_bit( EECR, EERE );

    // Data is available immediately
    return( EEDR );

} /* eeprom_read_byte() */


void eeprom_set_interrupt_enabled( bool enabled )
{
    assign_bit( EECR, EERIE, enabled );

} /* eeprom_set_interrupt_enabled() */


void eeprom_write_byte( eeprom_addr_t addr, uint8_t data )
{
    // EEPE and SPMEN bits must be clear prior to proceeding
    wait_bit_clear( EECR, EEPE );
    wait_bit_clear( SPMCSR, SPMEN );

    // Assign address and data
    EEAR = addr;
    EEDR = data;

    // Clear interrupts, if required
    bool int_en = is_bit_set( SREG, SREG_I );
    if( int_en ) cli();

    // Write the data (EEPE must be written within 4 clock cycles after EEMPE)
    set_bit( EECR, EEMPE );
    set_bit( EECR, EEPE );

    // Restore interrupts, if required
    if( int_en ) sei();

    // EEPE is cleared once write is complete
    wait_bit_clear( EECR, EEPE );

} /* eeprom_write_byte() */
