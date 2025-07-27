/**
 * @file    adc.h
 * @brief   Header for the ADC driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-26
 */

#if !defined( ADC_H )
#define ADC_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

/* -- Types -- */

/**
 * @typedef adc_channel_t
 * @brief   Enumeration of channels supported by the ADC.
 */
typedef uint8_t adc_channel_t;
enum
{
    ADC_CHANNEL_A0,                 /**< ADC is connected to the A0 input.              */
    ADC_CHANNEL_A1,                 /**< ADC is connected to the A1 input.              */
    ADC_CHANNEL_A2,                 /**< ADC is connected to the A2 input.              */
    ADC_CHANNEL_A3,                 /**< ADC is connected to the A3 input.              */
    ADC_CHANNEL_A4,                 /**< ADC is connected to the A4 input.              */
    ADC_CHANNEL_A5,                 /**< ADC is connected to the A5 input.              */
    ADC_CHANNEL_UNUSED_ADC6,        /**< Unused channel (ADC6).                         */
    ADC_CHANNEL_UNUSED_ADC7,        /**< Unused channel (ADC7).                         */
    ADC_CHANNEL_TEMPERATURE,        /**< ADC is connected to internal temp sensor.      */
    ADC_CHANNEL_INTERNAL,           /**< ADC is connected to internal voltage ref.      */
    ADC_CHANNEL_GROUND,             /**< ADC is connected to ground.                    */
    ADC_CHANNEL_COUNT,              /**< Number of valid ADC channels.                  */
};

/**
 * @typedef adc_vref_t
 * @brief   Enumeration of voltage references supported by the ADC.
 */
typedef uint8_t adc_vref_t;
enum
{
    ADC_VREF_AREF,                  /**< Voltage reference is Aref.                     */
    ADC_VREF_AVCC,                  /**< Voltage reference is AVcc.                     */
    ADC_VREF_INTERNAL,              /**< Voltage reference is internal 1.1 V reference. */
    ADC_VREF_COUNT,                 /**< Number of valid volttage references.           */
};

/* -- Procedure Prototypes -- */

/**
 * @fn      adc_get( void )
 * @brief   Immediately retrieves the value in the ADC register.
 */
uint16_t adc_get( void );

/**
 * @fn      adc_init( void )
 * @brief   Initializes the ADC driver.
 * @note    This function must be called before any other functions in this module.
 */
void adc_init( void );

/**
 * @fn      adc_read( void )
 * @brief   Synchronously receives a sample from the ADC.
 */
uint16_t adc_read( void );

/**
 * @fn      adc_set_channel( adc_channel_t )
 * @brief   Sets the input channel connected to the ADC.
 */
void adc_set_channel( adc_channel_t chnl );

/**
 * @fn      adc_set_enabled( bool )
 * @brief   Enables or disables the power to the ADC.
 */
void adc_set_enabled( bool enabled );

/**
 * @fn      adc_set_vref( adc_vref_t )
 * @brief   Sets the voltage reference used by the ADC.
 */
void adc_set_vref( adc_vref_t vref );

/**
 * @fn      adc_start( void )
 * @brief   Starts the ADC conversion and immediately returns.
 */
void adc_start( void );

/**
 * @fn      adc_wait( void )
 * @brief   Blocks until the ADC has finished any active conversion.
 * @note    This waits for the @c ADSC bit in @c ADCSRA to be cleared.
 */
void adc_wait( void );

#endif /* !defined( ADC_H ) */
