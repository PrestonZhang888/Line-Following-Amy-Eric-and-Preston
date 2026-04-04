
#ifndef ROBOT_MOTION_H
#define ROBOT_MOTION_H

#include <Zumo32U4.h>
extern unsigned int rawSensorValues[5];
extern Zumo32U4Motors motors;
extern Zumo32U4Encoders encoders;

// ===== BASIC MOVEMENT =====
void driveDistance(float centimeters);
void turnDegrees(float degrees);

// ===== TIMED TURN FUNCTIONS =====
void turnLeft();
void turnRight();
void turnAround();
void avoidObstacle();

#endif  // ROBOT_MOTION_H