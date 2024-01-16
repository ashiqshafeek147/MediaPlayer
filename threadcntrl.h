#ifndef _THREAD_H
#define _THREAD_H
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"

extern int userChoice;
extern int sec;
extern int hr;
extern int min;
extern int timer;


void* displaySong(void* args);
void* userInput(void* args);
void display(char* songName);
#endif