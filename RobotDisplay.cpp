/*
=====================================================
ROBOTDISPLAY.CPP - Display Function Implementations
=====================================================
*/

#include "RobotDisplay.h"
#include <Zumo32U4.h>

Zumo32U4OLED display;

void initDisplay() {
    display.setLayout21x8();
}

void showMessage(const char* line1, const char* line2) {
    display.clear();
    display.print(line1);
    display.gotoXY(0, 1);
    display.print(line2);
}