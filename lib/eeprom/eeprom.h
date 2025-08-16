/**
 * @file    eeprom.h
 * @brief   Header for the eeprom library.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-16
 */

#if !defined( EEPROM_EEPROM_H )
#define EEPROM_EEPROM_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

/* -- Types -- */

/**
 * @typedef eeprom_addr_t
 * @brief   Typedef representing an EEPROM address.
 */
typedef uint16_t eeprom_addr_t;

/* -- Procedures -- */

/**
 * @fn      eeprom_read_byte
 * @brief   Synchronously reads the byte at the specified EEPROM address.
 */
uint8_t eeprom_read_byte( eeprom_addr_t addr );

/**
 * @fn      eeprom_set_interrupt_enabled
 * @brief   Enables or disables the EEPROM ready interrupt.
 */
void eeprom_set_interrupt_enabled( bool enabled );

/**
 * @fn      eeprom_write_byte
 * @brief   Synchronously writes the byte at the specified EEPROM address.
 */
void eeprom_write_byte( eeprom_addr_t addr, uint8_t byte );

#endif /* !defined( EEPROM_EEPROM_H ) */
