#pragma once
#include "../AVRDuino/core.h"
#include "../AVRDuino/uart.h"
#include "../AVRDuino/A4988.h"
#include "../AVRDuino/pwm.h"

struct pwm1 pwm;

enum estados {activado, desactivado, homing, referenciado};
volatile extern enum estados estado;

void help();
void checkData(char data[]);
