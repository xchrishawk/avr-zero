/**
 * @file    adc.c
 * @brief   Implementation for the ADC driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-26
 */

/* -- Includes -- */

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "zero/bit_ops.h"
#include "zero/utility.h"

#include "adc.h"

/* -- Macros -- */

// Helper macros to validate enums
#define validate_autotrigger( _autotrigger )    validate_enum( _autotrigger,    ADC_AUTOTRIGGER_COUNT )
#define validate_channel( _channel )            validate_enum( _channel,        ADC_CHANNEL_COUNT )
#define validate_vref( _vref )                  validate_enum( _vref,           ADC_VREF_COUNT )

/* -- Procedures -- */

uint16_t adc_get( void )
{
    return( ADC );

} /* adc_get() */


void adc_init( void )
{
    // Set clock prescaler
    // TODO: Calculate this dynamically based on F_CPU???
    _Static_assert( F_CPU == 16000000UL, "ADC module assumes a different CPU frequency!" );
    set_bit( ADCSRA, ADPS2 );
    set_bit( ADCSRA, ADPS1 );
    set_bit( ADCSRA, ADPS0 );

    // Make result right-presented
    clear_bit( ADMUX, ADLAR );

} /* adc_init() */


uint16_t adc_read( void )
{
    adc_start();
    adc_wait();
    return( adc_get() );

} /* adc_read() */


void adc_set_autotrigger_enabled( bool enabled )
{
    assign_bit( ADCSRA, ADATE, enabled );

} /* adc_set_autotrigger_enabled() */


void adc_set_autotrigger_type( adc_autotrigger_t autotrigger )
{
    validate_autotrigger( autotrigger );

    // Array is ordered according to the adc_autotrigger_t enum
    static uint8_t const BITS[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
    _Static_assert( array_count( BITS ) == ADC_AUTOTRIGGER_COUNT, "Table has wrong size!" );

    ADCSRB = ( ( ADCSRB & 0xF8 ) | BITS[ autotrigger ] );

} /* adc_set_autotrigger_type() */


void adc_set_channel( adc_channel_t chnl )
{
    validate_channel( chnl );

    // Array is ordered according to the adc_channel_t enum
    static uint8_t const BITS[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0E, 0x0F };
    _Static_assert( array_count( BITS ) == ADC_CHANNEL_COUNT, "Table has wrong size!" );

    ADMUX = ( ( 0xF0 & ADMUX ) | BITS[ chnl ] );

} /* adc_set_channel() */


void adc_set_enabled( bool enabled )
{
    assign_bit( ADCSRA, ADEN, enabled );

} /* adc_set_enabled() */


void adc_set_interrupt_enabled( bool enabled )
{
    assign_bit( ADCSRA, ADIE, enabled );

} /* adc_set_interrupt_enabled() */


void adc_set_vref( adc_vref_t vref )
{
    validate_vref( vref );

    // Array is ordered according to the adc_vref_t enum
    static uint8_t const BITS[] = { 0x00, bitmask( REFS0 ), bitmask( REFS0 ) | bitmask( REFS1 ) };
    _Static_assert( array_count( BITS ) == ADC_VREF_COUNT, "Table has wrong size!" );

    ADMUX = ( ( 0x3F & ADMUX ) | BITS[ vref ] );

} /* adc_set_vref() */


void adc_start( void )
{
    set_bit( ADCSRA, ADSC );

} /* adc_start() */


void adc_wait( void )
{
    while( is_bit_set( ADCSRA, ADSC ) );

} /* adc_wait() */
