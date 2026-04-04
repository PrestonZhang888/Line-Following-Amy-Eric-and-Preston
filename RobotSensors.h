#ifndef ROBOT_SENSORS_H
#define ROBOT_SENSORS_H

#include <Zumo32U4.h>
#include "RobotConfig.h"

extern unsigned int sensorValues[5];
extern unsigned int rawSensorValues[5];
extern Zumo32U4LineSensors lineSensors;
extern Zumo32U4ButtonA buttonA;
extern Zumo32U4ProximitySensors proxSensors;

void initLineSensors();
void calibrateLineSensors();
int readLinePosition();
bool isLineVisible();
bool obstacleDetected();

#endif