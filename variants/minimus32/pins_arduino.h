/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_ANALOG_INPUTS 0
#define NUM_DIGITAL_PINS 24

// We only have a small USB buffer
#define USB_EP_SIZE 16

extern uint8_t usb_rxtx_leds;
static inline void
usb_rxtx_update_leds(uint8_t state, uint8_t mask)
{
  if (usb_rxtx_leds & 0x80)
    return;
  usb_rxtx_leds = (usb_rxtx_leds & ~mask) | (state & mask);
  if (usb_rxtx_leds)
    PORTD &= ~(1<<6);
  else
    PORTD |= 1<<6;
}

#define USB_RXTX_LED_PIN 7

// Use LED A (D7 - PD6) for USB activity
#define TX_RX_LED_INIT DDRD |= (1<<6), PORTD |= (1<<6)
#define TXLED0 usb_rxtx_update_leds(0, 1)
#define TXLED1 usb_rxtx_update_leds(1, 1)
#define RXLED0 usb_rxtx_update_leds(0, 2)
#define RXLED1 usb_rxtx_update_leds(2, 2)

static const uint8_t SS   = 9;
static const uint8_t MOSI = 12;
static const uint8_t MISO = 13;
static const uint8_t SCK  = 10;

extern const uint8_t PROGMEM pin_to_pcint_PGM[24];
#define digitalPinToPCICR(p)	((pgm_read_byte(pin_to_pcint_PGM + (p)) < 12) ? &PCICR : (uint8_t *)0)
#define digitalPinToPCICRbit(p) (pgm_read_byte(pin_to_pcint_PGM + (p)) >> 3)
#define digitalPinToPCMSK(p)    ((pgm_read_byte(pin_to_pcint_PGM + (p)) < 8) ? &PCMSK0 : &PCMSK1)
#define digitalPinToPCMSKbit(p) (pgm_read_byte(pin_to_pcint_PGM + (p)) & 7)

#define analogPinToChannel(P)  ( -1 )

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA32U2 / Minimus 32
//
// Pins numbered counter-clockwise starting from USB connector
//
// D0				PC2				PCINT11
// D1#				PD0				OC0B
// D2				PD1
// D3				PD2				RX
// D4				PD3				TX
// D5				PD4
// D6				PD5				LEB B (Blue)
// D7				PD6				LED A (Red/USB)
// D8				PD7				HWB
// D9				PB0				SS/PCINT0
// D10				PB1				SCK/PCINT1
// [D11]							GND
//
// D12				PB2				MOSI/PCINT2
// D13				PB3				MISO/PCINT3
// D14				PB4				PCINT4
// D15				PB5				PCINT5
// D16				PB6				PCINT6
// D17#				PB7				PCINT7/OC0A/OC1C
// D18				PC7
// D19#				PC6				PCINT8/OC1A
// [D20]							!RESET
// D21#				PC5				PCINT9/OC1B
// D22				PC4				PCINT10
// [D23]							VCC

const uint8_t PROGMEM pin_to_pcint_PGM[24] = {
	11, // D0 - PC2
	0xff, // D1 - PD0
	0xff, // D2 - PD1
	0xff, // D3 - PD2
	0xff, // D4 - PD3
	0xff, // D5 - PD4
	0xff, // D6 - PD5
	0xff, // D7 - PD6
	0xff, // D8 - PD7
	0, // D9 - PB0
	1, // D10 - PB1
	0xff, // GND
	2, // D12 - PB2
	3, // D13 - PB3
	4, // D14 - PB4
	5, // D15 - PB5
	6, // D16 - PB6
	7, // D17 - PB7
	0xff, // D18 - PC7
	8, // D19 - PC6
	0xff, // !RESET
	9, // D21 - PC5
	10,	// D22 - PC4
	0xff // VCC
};

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[24] = {
	PC, // D0 - PC2
	PD,	// D1 - PD0
	PD, // D2 - PD1
	PD, // D3 - PD2
	PD,	// D4 - PD3
	PD,	// D5 - PD4
	PD, // D6 - PD5
	PD,	// D7 - PD6
	PD,	// D8 - PD7
	PB, // D9 - PB0
	PB, // D10 - PB1
	NOT_A_PIN, // GND
	PB, // D12 - PB2
	PB,	// D13 - PB3
	PB, // D14 - PB4
	PB,	// D15 - PB5
	PB,	// D16 - PB6
	PB, // D17 - PB7
	PC, // D18 - PC7
	PC, // D19 - PC6
	NOT_A_PIN, // !RESET
	PC, // D21 - PC5
	PC,	// D22 - PC4
	NOT_A_PIN // VCC
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[24] = {
	_BV(2), // D0 - PC2
	_BV(0),	// D1 - PD0
	_BV(1), // D2 - PD1
	_BV(2), // D3 - PD2
	_BV(3),	// D4 - PD3
	_BV(4),	// D5 - PD4
	_BV(5),	// D6 - PD5
	_BV(6),	// D7 - PD6
	_BV(7),	// D8 - PD7
	_BV(0), // D9 - PB0
	_BV(1), // D10 - PB1
	0,		// GND
	_BV(2), // D12 - PB2
	_BV(3),	// D13 - PB3
	_BV(4), // D14 - PB4
	_BV(5),	// D15 - PB5
	_BV(6),	// D16 - PB6
	_BV(7), // D17 - PB7
	_BV(7), // D18 - PC7
	_BV(6), // D19 - PC6
	0,		// !RESET
	_BV(5), // D21 - PC5
	_BV(4),	// D22 - PC4
	0,		// VCC
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[24] = {
	NOT_ON_TIMER,
	TIMER0B,		/* 1 */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,

	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER0A,	/* 17 */
	NOT_ON_TIMER,
	TIMER1A,	/* 19 */
	NOT_ON_TIMER,
	TIMER1B,	/* 21 */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

uint8_t usb_rxtx_leds;

#endif /* ARDUINO_MAIN */

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR        Serial
#define SERIAL_PORT_USBVIRTUAL     Serial
#define SERIAL_PORT_HARDWARE       Serial1
#define SERIAL_PORT_HARDWARE_OPEN  Serial1

#endif /* Pins_Arduino_h */
