/**
 * @file    adc.h
 * @brief   Header for the ADC driver module.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-26
 */

#if !defined( ADC_ADC_H )
#define ADC_ADC_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdint.h>

/* -- Types -- */

/**
 * @typedef adc_autotrigger_t
 * @brief   Enumeration of the autotrigger types supported by the ADC.
 */
typedef uint8_t adc_autotrigger_t;
enum
{
    ADC_AUTOTRIGGER_FREE_RUN,       /**< ADC continuously acquires samples.             */
    ADC_AUTOTRIGGER_ANLG_COMPARATOR,/**< ADC acquires when analog comparator fires.     */
    ADC_AUTOTRIGGER_EXT_IRQ_0,      /**< ADC acquires on external IRQ 0.                */
    ADC_AUTOTRIGGER_TC0_COMP_MATCH_A, /**< ADC acquires on timer 0 compare match A.     */
    ADC_AUTOTRIGGER_TC0_OVERFLOW,   /**< ADC acquires on timer 0 overflow.              */
    ADC_AUTOTRIGGER_TC1_COMP_MATCH_B, /**< ADC acquires on timer 1 compare match B.     */
    ADC_AUTOTRIGGER_TC1_OVERFLOW,   /**< ADC acquires on timer 1 overflow.              */
    ADC_AUTOTRIGGER_TC1_CAPTURE,    /**< ADC acquires on timer 1 capture event.         */

    ADC_AUTOTRIGGER_COUNT,          /**< Number of valid autotrigger options.           */
};

/**
 * @typedef adc_channel_t
 * @brief   Enumeration of channels supported by the ADC.
 */
typedef uint8_t adc_channel_t;
enum
{
    ADC_CHANNEL_ARDUINO_A0,         /**< ADC is connected to the Arduino A0 input.      */
    ADC_CHANNEL_ARDUINO_A1,         /**< ADC is connected to the Arduino A1 input.      */
    ADC_CHANNEL_ARDUINO_A2,         /**< ADC is connected to the Arduino A2 input.      */
    ADC_CHANNEL_ARDUINO_A3,         /**< ADC is connected to the Arduino A3 input.      */
    ADC_CHANNEL_ARDUINO_A4,         /**< ADC is connected to the Arduino A4 input.      */
    ADC_CHANNEL_ARDUINO_A5,         /**< ADC is connected to the Arduino A5 input.      */
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
 * @fn      adc_set_autotrigger_enabled( bool )
 * @brief   Enables or disables automatic triggering of ADC samples.
 */
void adc_set_autotrigger_enabled( bool enabled );

/**
 * @fn      adc_set_autotrigger_type( adc_autotrigger_t )
 * @brief   Sets the autotrigger type used by the ADC.
 */
void adc_set_autotrigger_type( adc_autotrigger_t autotrigger );

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
 * @fn      adc_set_interrupt_enabled( bool )
 * @brief   Enables or disables the ADC conversion complete interrupt.
 */
void adc_set_interrupt_enabled( bool enabled );

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

#endif /* !defined( ADC_ADC_H ) */
