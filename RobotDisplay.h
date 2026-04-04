/*
=====================================================
ROBOTDISPLAY.H - Display Function Declarations
=====================================================
*/

#ifndef ROBOT_DISPLAY_H
#define ROBOT_DISPLAY_H

#include <Zumo32U4.h>

extern Zumo32U4OLED display;

void initDisplay();
void showMessage(const char* line1, const char* line2);

#endif