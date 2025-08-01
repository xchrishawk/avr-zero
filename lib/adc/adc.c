/**
 * @file    adc.c
 * @brief   Implementation for the ADC driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-26
 */

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "zero/bit_ops.h"

#include "adc.h"

/* -- Procedures -- */

uint16_t adc_get( void )
{
    return( ADC );

} /* adc_get() */


void adc_init( void )
{
    // Set clock prescaler
    // TODO: Calculate this dynamically based on F_CPU???
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


void adc_set_channel( adc_channel_t chnl )
{
    static uint8_t const MASK = 0xF0;
    switch( chnl )
    {
    case ADC_CHANNEL_A0:
        ADMUX = ( MASK & ADMUX );
        break;

    case ADC_CHANNEL_A1:
        ADMUX = ( MASK & ADMUX ) | 0x01;
        break;

    case ADC_CHANNEL_A2:
        ADMUX = ( MASK & ADMUX ) | 0x02;
        break;

    case ADC_CHANNEL_A3:
        ADMUX = ( MASK & ADMUX ) | 0x03;
        break;

    case ADC_CHANNEL_A4:
        ADMUX = ( MASK & ADMUX ) | 0x04;
        break;

    case ADC_CHANNEL_A5:
        ADMUX = ( MASK & ADMUX ) | 0x05;
        break;

    case ADC_CHANNEL_UNUSED_ADC6:
        ADMUX = ( MASK & ADMUX ) | 0x06;
        break;

    case ADC_CHANNEL_UNUSED_ADC7:
        ADMUX = ( MASK & ADMUX ) | 0x07;
        break;

    case ADC_CHANNEL_TEMPERATURE:
        ADMUX = ( MASK & ADMUX ) | 0x08;
        break;

    case ADC_CHANNEL_INTERNAL:
        ADMUX = ( MASK & ADMUX ) | 0x0E;
        break;

    case ADC_CHANNEL_GROUND:
        ADMUX = ( MASK & ADMUX ) | 0x0F;
        break;

    default:
        break;
    }

} /* adc_set_channel() */


void adc_set_enabled( bool enabled )
{
    assign_bit( ADCSRA, ADEN, enabled );

} /* adc_set_enabled() */


void adc_set_vref( adc_vref_t vref )
{
    static uint8_t const MASK = 0x3F;
    switch( vref )
    {
    case ADC_VREF_AREF:
        ADMUX = ( MASK & ADMUX );
        break;

    case ADC_VREF_AVCC:
        ADMUX = ( MASK & ADMUX ) | bitmask( REFS0 );
        break;

    case ADC_VREF_INTERNAL:
        ADMUX = ( MASK & ADMUX ) | bitmask( REFS0 ) | bitmask( REFS1 );
        break;

    default:
        break;
    }

} /* adc_set_vref() */


void adc_start( void )
{
    set_bit( ADCSRA, ADSC );

} /* adc_start() */


void adc_wait( void )
{
    while( is_bit_set( ADCSRA, ADSC ) );

} /* adc_wait() */
