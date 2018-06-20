#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/interrupts.h"
#include "./lib/AVRDuino/timers.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

void push(void);
void eje(void);

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdout = stdin = &uart_io;
  UART_init(checkData);
  // i2c_init(checkData); //Strongly suggested implementation

  DriveArray STPArray1 = {8, 9, 10, 0, 0, 0, 1.8, 10};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAP1.ID = 0;
  PAParray[0] = &PAP1;

  setPCInt(2);
  setPCInt(3);
  // This breaks everything, ԅ(≖‿≖ԅ)
  // setINT(2, RISING_FLANK, push);
  // setINT(3, FALLLING_FLANK, eje);

  // PAPsInit(8);
  setTimer0(x8);

  sei();

  setPin(13, OUTPUT);
  _delay_ms(1000);
  printf("Setup Complete\n");

  while (1) {
    togglePin(13);
    _delay_ms(500);
  }
  return 0;
}

void eje(void) {
  _delay_ms(10);
  if (!readDPin(3)) {
    raceEnd(0, START);
  }
}
void push(void) {
  _delay_ms(10);
  if (readDPin(2)) {
    raceEnd(0, END);
  }
}

ISR(PCINT2_vect) {
  _delay_ms(10);
  if (readDPin(3)) {
    raceEnd(0, START);
  } else if (readDPin(2)) {
    raceEnd(0, END);
  };
};
