/**
 * @file    event.c
 * @brief   Implementation for the system event manager.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-08-03
 */

/* -- Includes -- */

#include <assert.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#include "zero/bit_ops.h"

#include "event.h"

/* -- Macros -- */

/**
 * @def     EVENT_VALID
 * @brief   Returns `true` if the specified event is valid and not `EVENT_NONE`.
 */
#define EVENT_VALID( _event )                                                   \
    ( ( _event ) < EVENT_COUNT && ( _event ) != EVENT_NONE )

/* -- Variables -- */

uint32_t    s_tick              = 0;
event_t     s_pending_event     = EVENT_NONE;

/* -- Procedure Prototypes -- */

/**
 * @fn      sleep_until_interrupt( void )
 * @brief   Puts the processor in idle mode until the next interrupt.
 */
static void sleep_until_interrupt( void );

/* -- Procedures -- */

void event_init( void )
{
    // Disable interrupts
    cli();

    // Initialize timer 0 as the primary system clock:
    // - Waveform generation mode set to CTC
    // - Clock prescale set to /64
    // - Compare register set to 250 (1 millisecond at 16 MHz F_CPU)
    set_bit( TCCR0A, WGM01 );
    set_bit( TCCR0B, CS00 );
    set_bit( TCCR0B, CS01 );
    OCR0A = 250;

    // Enable OCRA interrupt
    set_bit( TIMSK0, OCIE0A );

} /* event_init() */


void event_set_pending( event_t event )
{
    assert( EVENT_VALID( event ) );
    s_pending_event = event;

} /* event_set_pending() */


uint32_t event_tick( void )
{
    return s_tick;

} /* event_tick() */


event_t event_wait( void )
{
    // Wait for next interrupt which sets a pending event
    while( s_pending_event == EVENT_NONE )
        sleep_until_interrupt();

    // Check the pending event, and reset it
    assert( EVENT_VALID( s_pending_event ) );
    event_t ret = s_pending_event;
    s_pending_event = EVENT_NONE;

    return( ret );

} /* event_wait() */


static void sleep_until_interrupt( void )
{
    set_sleep_mode( SLEEP_MODE_IDLE );
    sei();
    sleep_mode();
    cli();

} /* sleep_until_interrupt() */


ISR( TIMER0_COMPA_vect )
{
    s_tick++;
    event_set_pending( EVENT_TICK );

} /* ISR( TIMER0_COMPA_vect ) */
