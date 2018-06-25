#include "./lib/AVRDuino/A4988.h"
#include "./lib/AVRDuino/core.h"
#include "./lib/AVRDuino/interrupts.h"
#include "./lib/AVRDuino/pwm.h"
#include "./lib/AVRDuino/timers.h"
#include "./lib/AVRDuino/uart.h"
#include "lib/custom/command_interpreter.h"
#include <util/delay.h>

FILE uart_io = FDEV_SETUP_STREAM(uecho, uread, _FDEV_SETUP_RW);

int main(void) {
  stdout = stdin = &uart_io;
  UART_init(checkData);

  DriveArray STPArray1 = {5, 6, 7, 0, 0, 0, 1.8, 10};
  pololu STP1 = newPololuFA(STPArray1);
  STEPPER PAP1;
  PAP1.motor = &STP1;
  PAP1.enabled = 0;
  PAP1.ID = 0;
  PAParray[0] = &PAP1;

  setPin(9, OUTPUT);
  pwm = newPWM1();
  pwm.regist(&pwm);
  pwm.freq(65000);

  pwm.dutyA(10);

  setPCInt(2);
  setPCInt(3);

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

ISR(PCINT2_vect) {
  _delay_ms(20);
  if (readDPin(3)) {
    raceEnd(0, START);
  } else if (!readDPin(2)) {
    raceEnd(0, END);
  };
};
