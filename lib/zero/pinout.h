/**
 * @file    pinout.h
 * @brief   Header defining device-specific pin information.
 *
 * @author  Chris Vig (chris@invictus.so)
 * @date    2025-07-21
 */

#if !defined( ZERO_PINOUT_H )
#define ZERO_PINOUT_H

/* -- Includes -- */

#include <avr/io.h>

/* -- Constants -- */

#if defined( __AVR_ATmega328P__ )

    // AVR ATMega328P
    // Assume Arduino Uno R3
    // https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf

    // Peripheral counts
    #define _GPIO_PIN_COUNT                 ( 20 )
    #define _USART_PORT_COUNT               ( 1 )

    // GPIO_PIN_ARDUINO_D0
    #define _GPIO_PIN_ARDUINO_D00_PORT      D
    #define _GPIO_PIN_ARDUINO_D00_PIN       0

    // GPIO_PIN_ARDUINO_D1
    #define _GPIO_PIN_ARDUINO_D01_PORT      D
    #define _GPIO_PIN_ARDUINO_D01_PIN       1

    // GPIO_PIN_ARDUINO_D2
    #define _GPIO_PIN_ARDUINO_D02_PORT      D
    #define _GPIO_PIN_ARDUINO_D02_PIN       2

    // GPIO_PIN_ARDUINO_D3
    #define _GPIO_PIN_ARDUINO_D03_PORT      D
    #define _GPIO_PIN_ARDUINO_D03_PIN       3

    // GPIO_PIN_ARDUINO_D4
    #define _GPIO_PIN_ARDUINO_D04_PORT      D
    #define _GPIO_PIN_ARDUINO_D04_PIN       4

    // GPIO_PIN_ARDUINO_D5
    #define _GPIO_PIN_ARDUINO_D05_PORT      D
    #define _GPIO_PIN_ARDUINO_D05_PIN       5

    // GPIO_PIN_ARDUINO_D6
    #define _GPIO_PIN_ARDUINO_D06_PORT      D
    #define _GPIO_PIN_ARDUINO_D06_PIN       6

    // GPIO_PIN_ARDUINO_D7
    #define _GPIO_PIN_ARDUINO_D07_PORT      D
    #define _GPIO_PIN_ARDUINO_D07_PIN       7

    // GPIO_PIN_ARDUINO_D8
    #define _GPIO_PIN_ARDUINO_D08_PORT      B
    #define _GPIO_PIN_ARDUINO_D08_PIN       0

    // GPIO_PIN_ARDUINO_D9
    #define _GPIO_PIN_ARDUINO_D09_PORT      B
    #define _GPIO_PIN_ARDUINO_D09_PIN       1

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

#elif defined( __AVR_ATmega2560__ )

    // AVR ATMega2560
    // Assume Arduino Mega 2560
    // https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf

    // Peripheral counts
    #define _GPIO_PIN_COUNT                 ( 70 )
    #define _USART_PORT_COUNT               ( 4 )

    // GPIO_PIN_ARDUINO_D0
    #define _GPIO_PIN_ARDUINO_D00_PORT      E
    #define _GPIO_PIN_ARDUINO_D00_PIN       0

    // GPIO_PIN_ARDUINO_D1
    #define _GPIO_PIN_ARDUINO_D01_PORT      E
    #define _GPIO_PIN_ARDUINO_D01_PIN       1

    // GPIO_PIN_ARDUINO_D2
    #define _GPIO_PIN_ARDUINO_D02_PORT      E
    #define _GPIO_PIN_ARDUINO_D02_PIN       4

    // GPIO_PIN_ARDUINO_D3
    #define _GPIO_PIN_ARDUINO_D03_PORT      E
    #define _GPIO_PIN_ARDUINO_D03_PIN       5

    // GPIO_PIN_ARDUINO_D4
    #define _GPIO_PIN_ARDUINO_D04_PORT      G
    #define _GPIO_PIN_ARDUINO_D04_PIN       5

    // GPIO_PIN_ARDUINO_D5
    #define _GPIO_PIN_ARDUINO_D05_PORT      E
    #define _GPIO_PIN_ARDUINO_D05_PIN       3

    // GPIO_PIN_ARDUINO_D6
    #define _GPIO_PIN_ARDUINO_D06_PORT      H
    #define _GPIO_PIN_ARDUINO_D06_PIN       3

    // GPIO_PIN_ARDUINO_D7
    #define _GPIO_PIN_ARDUINO_D07_PORT      H
    #define _GPIO_PIN_ARDUINO_D07_PIN       4

    // GPIO_PIN_ARDUINO_D8
    #define _GPIO_PIN_ARDUINO_D08_PORT      H
    #define _GPIO_PIN_ARDUINO_D08_PIN       5

    // GPIO_PIN_ARDUINO_D9
    #define _GPIO_PIN_ARDUINO_D09_PORT      H
    #define _GPIO_PIN_ARDUINO_D09_PIN       6

    // GPIO_PIN_ARDUINO_D10
    #define _GPIO_PIN_ARDUINO_D10_PORT      B
    #define _GPIO_PIN_ARDUINO_D10_PIN       4

    // GPIO_PIN_ARDUINO_D11
    #define _GPIO_PIN_ARDUINO_D11_PORT      B
    #define _GPIO_PIN_ARDUINO_D11_PIN       5

    // GPIO_PIN_ARDUINO_D12
    #define _GPIO_PIN_ARDUINO_D12_PORT      B
    #define _GPIO_PIN_ARDUINO_D12_PIN       6

    // GPIO_PIN_ARDUINO_D13
    #define _GPIO_PIN_ARDUINO_D13_PORT      B
    #define _GPIO_PIN_ARDUINO_D13_PIN       7

    // GPIO_PIN_ARDUINO_D14
    #define _GPIO_PIN_ARDUINO_D14_PORT      J
    #define _GPIO_PIN_ARDUINO_D14_PIN       1

    // GPIO_PIN_ARDUINO_D15
    #define _GPIO_PIN_ARDUINO_D15_PORT      J
    #define _GPIO_PIN_ARDUINO_D15_PIN       0

    // GPIO_PIN_ARDUINO_D16
    #define _GPIO_PIN_ARDUINO_D16_PORT      H
    #define _GPIO_PIN_ARDUINO_D16_PIN       1

    // GPIO_PIN_ARDUINO_D17
    #define _GPIO_PIN_ARDUINO_D17_PORT      H
    #define _GPIO_PIN_ARDUINO_D17_PIN       0

    // GPIO_PIN_ARDUINO_D18
    #define _GPIO_PIN_ARDUINO_D18_PORT      D
    #define _GPIO_PIN_ARDUINO_D18_PIN       3

    // GPIO_PIN_ARDUINO_D19
    #define _GPIO_PIN_ARDUINO_D19_PORT      D
    #define _GPIO_PIN_ARDUINO_D19_PIN       2

    // GPIO_PIN_ARDUINO_D20
    #define _GPIO_PIN_ARDUINO_D20_PORT      D
    #define _GPIO_PIN_ARDUINO_D20_PIN       1

    // GPIO_PIN_ARDUINO_D21
    #define _GPIO_PIN_ARDUINO_D21_PORT      D
    #define _GPIO_PIN_ARDUINO_D21_PIN       0

    // GPIO_PIN_ARDUINO_D22
    #define _GPIO_PIN_ARDUINO_D22_PORT      A
    #define _GPIO_PIN_ARDUINO_D22_PIN       0

    // GPIO_PIN_ARDUINO_D23
    #define _GPIO_PIN_ARDUINO_D23_PORT      A
    #define _GPIO_PIN_ARDUINO_D23_PIN       1

    // GPIO_PIN_ARDUINO_D24
    #define _GPIO_PIN_ARDUINO_D24_PORT      A
    #define _GPIO_PIN_ARDUINO_D24_PIN       2

    // GPIO_PIN_ARDUINO_D25
    #define _GPIO_PIN_ARDUINO_D25_PORT      A
    #define _GPIO_PIN_ARDUINO_D25_PIN       3

    // GPIO_PIN_ARDUINO_D26
    #define _GPIO_PIN_ARDUINO_D26_PORT      A
    #define _GPIO_PIN_ARDUINO_D26_PIN       4

    // GPIO_PIN_ARDUINO_D27
    #define _GPIO_PIN_ARDUINO_D27_PORT      A
    #define _GPIO_PIN_ARDUINO_D27_PIN       5

    // GPIO_PIN_ARDUINO_D28
    #define _GPIO_PIN_ARDUINO_D28_PORT      A
    #define _GPIO_PIN_ARDUINO_D28_PIN       6

    // GPIO_PIN_ARDUINO_D29
    #define _GPIO_PIN_ARDUINO_D29_PORT      A
    #define _GPIO_PIN_ARDUINO_D29_PIN       7

    // GPIO_PIN_ARDUINO_D30
    #define _GPIO_PIN_ARDUINO_D30_PORT      C
    #define _GPIO_PIN_ARDUINO_D30_PIN       7

    // GPIO_PIN_ARDUINO_D31
    #define _GPIO_PIN_ARDUINO_D31_PORT      C
    #define _GPIO_PIN_ARDUINO_D31_PIN       6

    // GPIO_PIN_ARDUINO_D32
    #define _GPIO_PIN_ARDUINO_D32_PORT      C
    #define _GPIO_PIN_ARDUINO_D32_PIN       5

    // GPIO_PIN_ARDUINO_D33
    #define _GPIO_PIN_ARDUINO_D33_PORT      C
    #define _GPIO_PIN_ARDUINO_D33_PIN       4

    // GPIO_PIN_ARDUINO_D34
    #define _GPIO_PIN_ARDUINO_D34_PORT      C
    #define _GPIO_PIN_ARDUINO_D34_PIN       3

    // GPIO_PIN_ARDUINO_D35
    #define _GPIO_PIN_ARDUINO_D35_PORT      C
    #define _GPIO_PIN_ARDUINO_D35_PIN       2

    // GPIO_PIN_ARDUINO_D36
    #define _GPIO_PIN_ARDUINO_D36_PORT      C
    #define _GPIO_PIN_ARDUINO_D36_PIN       1

    // GPIO_PIN_ARDUINO_D37
    #define _GPIO_PIN_ARDUINO_D37_PORT      C
    #define _GPIO_PIN_ARDUINO_D37_PIN       0

    // GPIO_PIN_ARDUINO_D38
    #define _GPIO_PIN_ARDUINO_D38_PORT      D
    #define _GPIO_PIN_ARDUINO_D38_PIN       7

    // GPIO_PIN_ARDUINO_D39
    #define _GPIO_PIN_ARDUINO_D39_PORT      G
    #define _GPIO_PIN_ARDUINO_D39_PIN       2

    // GPIO_PIN_ARDUINO_D40
    #define _GPIO_PIN_ARDUINO_D40_PORT      G
    #define _GPIO_PIN_ARDUINO_D40_PIN       1

    // GPIO_PIN_ARDUINO_D41
    #define _GPIO_PIN_ARDUINO_D41_PORT      G
    #define _GPIO_PIN_ARDUINO_D41_PIN       0

    // GPIO_PIN_ARDUINO_D42
    #define _GPIO_PIN_ARDUINO_D42_PORT      L
    #define _GPIO_PIN_ARDUINO_D42_PIN       7

    // GPIO_PIN_ARDUINO_D43
    #define _GPIO_PIN_ARDUINO_D43_PORT      L
    #define _GPIO_PIN_ARDUINO_D43_PIN       6

    // GPIO_PIN_ARDUINO_D44
    #define _GPIO_PIN_ARDUINO_D44_PORT      L
    #define _GPIO_PIN_ARDUINO_D44_PIN       5

    // GPIO_PIN_ARDUINO_D45
    #define _GPIO_PIN_ARDUINO_D45_PORT      L
    #define _GPIO_PIN_ARDUINO_D45_PIN       4

    // GPIO_PIN_ARDUINO_D46
    #define _GPIO_PIN_ARDUINO_D46_PORT      L
    #define _GPIO_PIN_ARDUINO_D46_PIN       3

    // GPIO_PIN_ARDUINO_D47
    #define _GPIO_PIN_ARDUINO_D47_PORT      L
    #define _GPIO_PIN_ARDUINO_D47_PIN       2

    // GPIO_PIN_ARDUINO_D48
    #define _GPIO_PIN_ARDUINO_D48_PORT      L
    #define _GPIO_PIN_ARDUINO_D48_PIN       1

    // GPIO_PIN_ARDUINO_D49
    #define _GPIO_PIN_ARDUINO_D49_PORT      L
    #define _GPIO_PIN_ARDUINO_D49_PIN       0

    // GPIO_PIN_ARDUINO_D50
    #define _GPIO_PIN_ARDUINO_D50_PORT      B
    #define _GPIO_PIN_ARDUINO_D50_PIN       3

    // GPIO_PIN_ARDUINO_D51
    #define _GPIO_PIN_ARDUINO_D51_PORT      B
    #define _GPIO_PIN_ARDUINO_D51_PIN       2

    // GPIO_PIN_ARDUINO_D52
    #define _GPIO_PIN_ARDUINO_D52_PORT      B
    #define _GPIO_PIN_ARDUINO_D52_PIN       1

    // GPIO_PIN_ARDUINO_D53
    #define _GPIO_PIN_ARDUINO_D53_PORT      B
    #define _GPIO_PIN_ARDUINO_D53_PIN       0

    // GPIO_PIN_ARDUINO_D54
    #define _GPIO_PIN_ARDUINO_D54_PORT      F
    #define _GPIO_PIN_ARDUINO_D54_PIN       0

    // GPIO_PIN_ARDUINO_D55
    #define _GPIO_PIN_ARDUINO_D55_PORT      F
    #define _GPIO_PIN_ARDUINO_D55_PIN       1

    // GPIO_PIN_ARDUINO_D56
    #define _GPIO_PIN_ARDUINO_D56_PORT      F
    #define _GPIO_PIN_ARDUINO_D56_PIN       2

    // GPIO_PIN_ARDUINO_D57
    #define _GPIO_PIN_ARDUINO_D57_PORT      F
    #define _GPIO_PIN_ARDUINO_D57_PIN       3

    // GPIO_PIN_ARDUINO_D58
    #define _GPIO_PIN_ARDUINO_D58_PORT      F
    #define _GPIO_PIN_ARDUINO_D58_PIN       4

    // GPIO_PIN_ARDUINO_D59
    #define _GPIO_PIN_ARDUINO_D59_PORT      F
    #define _GPIO_PIN_ARDUINO_D59_PIN       5

    // GPIO_PIN_ARDUINO_D60
    #define _GPIO_PIN_ARDUINO_D60_PORT      F
    #define _GPIO_PIN_ARDUINO_D60_PIN       6

    // GPIO_PIN_ARDUINO_D61
    #define _GPIO_PIN_ARDUINO_D61_PORT      F
    #define _GPIO_PIN_ARDUINO_D61_PIN       7

    // GPIO_PIN_ARDUINO_D62
    #define _GPIO_PIN_ARDUINO_D62_PORT      K
    #define _GPIO_PIN_ARDUINO_D62_PIN       0

    // GPIO_PIN_ARDUINO_D63
    #define _GPIO_PIN_ARDUINO_D63_PORT      K
    #define _GPIO_PIN_ARDUINO_D63_PIN       1

    // GPIO_PIN_ARDUINO_D64
    #define _GPIO_PIN_ARDUINO_D64_PORT      K
    #define _GPIO_PIN_ARDUINO_D64_PIN       2

    // GPIO_PIN_ARDUINO_D65
    #define _GPIO_PIN_ARDUINO_D65_PORT      K
    #define _GPIO_PIN_ARDUINO_D65_PIN       3

    // GPIO_PIN_ARDUINO_D66
    #define _GPIO_PIN_ARDUINO_D66_PORT      K
    #define _GPIO_PIN_ARDUINO_D66_PIN       4

    // GPIO_PIN_ARDUINO_D67
    #define _GPIO_PIN_ARDUINO_D67_PORT      K
    #define _GPIO_PIN_ARDUINO_D67_PIN       5

    // GPIO_PIN_ARDUINO_D68
    #define _GPIO_PIN_ARDUINO_D68_PORT      K
    #define _GPIO_PIN_ARDUINO_D68_PIN       6

    // GPIO_PIN_ARDUINO_D69
    #define _GPIO_PIN_ARDUINO_D69_PORT      K
    #define _GPIO_PIN_ARDUINO_D69_PIN       7

#else

    // Device type not defined
    #error "Unknown or unsupported device type!"

#endif

#endif /* !defined( ZERO_PINOUT_H ) */
