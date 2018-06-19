#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/interrupts.h"
#include "./lib/AVRDuino/timers.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdout = stdin = &uart_io;
  UART_init(checkData);

  DriveArray STPArray1 = {2, 3, 4, 0, 0, 0, 1.8, 10};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAParray[0] = &PAP1;

  // setPCInt(8);
  // setPCInt(9);

  // PAPsInit(8);
  setTimer0(x8);

  sei();

  setPin(13, OUTPUT);
  _delay_ms(500);
  printf("Setup Complete\n");

  while (1) {
    /* code */
    togglePin(13);
    _delay_ms(500);
  }
  return 0;
}

ISR(PCINT0_vect) {
  _delay_ms(10);
  if (readDPin(8)) {
    raceEnd(0, START);
  } else if (readDPin(9)) {
    raceEnd(0, END);
  };
};
