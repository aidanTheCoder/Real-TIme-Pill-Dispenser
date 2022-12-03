#ifndef _PILL_DISPENSER_H
#define _PILL_DISPENSER_H

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void menu();
void* loadingPhase(void* void_pointer);
void* transPhase(void* void_pointer);
void* dispensePhase(void* void_pointer);
int off(int time);
int on(int time);
void print_scheduler(pid_t pid);

#endif