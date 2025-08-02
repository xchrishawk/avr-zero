# `powerbar-switcher`

This is a simple application which is intended to provide a front end for a relay-controlled powerbar. The specific
model that this is intended to work with is available from Amazon here:

https://www.amazon.com/dp/B00WV7GMA2

## Interconnect

- USB port should be connected to the controlling computer.
- The D14 (i.e., A0) output on the Arduino is connected to the positive input of the relay.
- The negative input is connected to one of the ground pins on the Arduino.

## Interface

When connected to the PC, the Arduino will appear as a virtual COM port. The expected connection parameters are:

- 9600 baud
- 1 stop bit
- No parity

All commands are a single byte and are responded to immediately. The currently implemented commands are:

- `n` - Turns the power o**n**
- `f` - Turns the power o**f**f

The Arduino will report the power status over the serial interface after each command is received.

## LED

The state of the Arduino's built-in LED shows the state that the Arduino "thinks" it is commanding. If the LED is on,
the powerbar should be switched on, and if the LED is off, the powerbar should be switched off.
