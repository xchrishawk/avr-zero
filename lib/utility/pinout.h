/**
 * @file    pinout.h
 * @brief   Header defining device-specific pin information.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

#if !defined( UTILITY_PINOUT_H )
#define UTILITY_PINOUT_H

/* -- Includes -- */

#include <avr/io.h>

/* -- Constants -- */

#if defined( __AVR_ATmega328P__ )

    // AVR ATMega328P
    // Assume Arduino Uno R3

    // GPIO_PIN_ARDUINO_D0
    #define _GPIO_PIN_ARDUINO_D0_PORT       D
    #define _GPIO_PIN_ARDUINO_D0_PIN        0

    // GPIO_PIN_ARDUINO_D1
    #define _GPIO_PIN_ARDUINO_D1_PORT       D
    #define _GPIO_PIN_ARDUINO_D1_PIN        1

    // GPIO_PIN_ARDUINO_D2
    #define _GPIO_PIN_ARDUINO_D2_PORT       D
    #define _GPIO_PIN_ARDUINO_D2_PIN        2

    // GPIO_PIN_ARDUINO_D3
    #define _GPIO_PIN_ARDUINO_D3_PORT       D
    #define _GPIO_PIN_ARDUINO_D3_PIN        3

    // GPIO_PIN_ARDUINO_D4
    #define _GPIO_PIN_ARDUINO_D4_PORT       D
    #define _GPIO_PIN_ARDUINO_D4_PIN        4

    // GPIO_PIN_ARDUINO_D5
    #define _GPIO_PIN_ARDUINO_D5_PORT       D
    #define _GPIO_PIN_ARDUINO_D5_PIN        5

    // GPIO_PIN_ARDUINO_D6
    #define _GPIO_PIN_ARDUINO_D6_PORT       D
    #define _GPIO_PIN_ARDUINO_D6_PIN        6

    // GPIO_PIN_ARDUINO_D7
    #define _GPIO_PIN_ARDUINO_D7_PORT       D
    #define _GPIO_PIN_ARDUINO_D7_PIN        7

    // GPIO_PIN_ARDUINO_D8
    #define _GPIO_PIN_ARDUINO_D8_PORT       B
    #define _GPIO_PIN_ARDUINO_D8_PIN        0

    // GPIO_PIN_ARDUINO_D9
    #define _GPIO_PIN_ARDUINO_D9_PORT       B
    #define _GPIO_PIN_ARDUINO_D9_PIN        1

    // GPIO_PIN_ARDUINO_D10
    #define _GPIO_PIN_ARDUINO_D10_PORT      B
    #define _GPIO_PIN_ARDUINO_D10_PIN       2

    // GPIO_PIN_ARDUINO_D11
    #define _GPIO_PIN_ARDUINO_D11_PORT      B
    #define _GPIO_PIN_ARDUINO_D11_PIN       3

    // GPIO_PIN_ARDUINO_D12
    #define _GPIO_PIN_ARDUINO_D12_PORT      B
    #define _GPIO_PIN_ARDUINO_D12_PIN       4

    // GPIO_PIN_ARDUINO_D13
    #define _GPIO_PIN_ARDUINO_D13_PORT      B
    #define _GPIO_PIN_ARDUINO_D13_PIN       5

    // GPIO_PIN_ARDUINO_D14
    #define _GPIO_PIN_ARDUINO_D14_PORT      C
    #define _GPIO_PIN_ARDUINO_D14_PIN       0

    // GPIO_PIN_ARDUINO_D15
    #define _GPIO_PIN_ARDUINO_D15_PORT      C
    #define _GPIO_PIN_ARDUINO_D15_PIN       1

    // GPIO_PIN_ARDUINO_D16
    #define _GPIO_PIN_ARDUINO_D16_PORT      C
    #define _GPIO_PIN_ARDUINO_D16_PIN       2

    // GPIO_PIN_ARDUINO_D17
    #define _GPIO_PIN_ARDUINO_D17_PORT      C
    #define _GPIO_PIN_ARDUINO_D17_PIN       3

    // GPIO_PIN_ARDUINO_D18
    #define _GPIO_PIN_ARDUINO_D18_PORT      C
    #define _GPIO_PIN_ARDUINO_D18_PIN       4

    // GPIO_PIN_ARDUINO_D19
    #define _GPIO_PIN_ARDUINO_D19_PORT      C
    #define _GPIO_PIN_ARDUINO_D19_PIN       5

#else

    // Device type not defined
    #error "Unknown or unsupported device type!"

#endif

#endif /* !defined( UTILITY_PINOUT_H ) */
