#pragma once
#include "../AVRDuino/core.h"
#include "../AVRDuino/uart.h"
#include "../AVRDuino/A4988.h"
#include "../AVRDuino/pwm.h"

struct pwm1 pwm;

void help();
void checkData(char data[]);
