#include "RobotMotion.h"
#include "RobotConfig.h"
#include "RobotSensors.h"
#include <Zumo32U4.h>

// ===== HARDWARE OBJECTS =====
Zumo32U4Motors  motors;
Zumo32U4Encoders encoders;

// ===== BASIC MOVEMENT =====

void driveDistance(float centimeters) {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    int targetCounts = abs(centimeters) * COUNTS_PER_CM;
    int speed = (centimeters > 0) ? DRIVE_SPEED : -DRIVE_SPEED;
    motors.setSpeeds(speed, speed);
    while (abs(encoders.getCountsLeft()) < targetCounts) delay(10);
    motors.setSpeeds(0, 0);
}

void turnDegrees(float degrees) {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    int targetCounts = abs(degrees) * COUNTS_PER_DEGREE;
    int leftSpeed  = (degrees > 0) ? TURN_SPEED : -TURN_SPEED;
    int rightSpeed = -leftSpeed;
    motors.setSpeeds(leftSpeed, rightSpeed);
    while (abs(encoders.getCountsLeft()) < targetCounts) delay(10);
    motors.setSpeeds(0, 0);
}

void turnLeft() {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    while (abs(encoders.getCountsLeft()) < COUNTS_PER_DEGREE * 85) delay(1);
    motors.setSpeeds(0, 0);
    delay(100);
    int attempts = 0;
    while (attempts < 50) {
        lineSensors.read(rawSensorValues);
        if (rawSensorValues[2] > 600) { motors.setSpeeds(0, 0); return; }
        motors.setSpeeds(-80, 80);
        delay(20);
        attempts++;
    }
    motors.setSpeeds(0, 0);
}

void turnRight() {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    while (abs(encoders.getCountsLeft()) < COUNTS_PER_DEGREE * 85) delay(1);
    motors.setSpeeds(0, 0);
    delay(100);
    int attempts = 0;
    while (attempts < 50) {
        lineSensors.read(rawSensorValues);
        if (rawSensorValues[2] > 600) { motors.setSpeeds(0, 0); return; }
        motors.setSpeeds(80, -80);
        delay(20);
        attempts++;
    }
    motors.setSpeeds(0, 0);
}

void turnAround() {
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    while (abs(encoders.getCountsLeft()) < COUNTS_PER_DEGREE * 175) delay(1);
    motors.setSpeeds(0, 0);
    delay(100);
    int attempts = 0;
    while (attempts < 100) {
        lineSensors.read(rawSensorValues);
        if (rawSensorValues[2] > 600) { motors.setSpeeds(0, 0); return; }
        motors.setSpeeds(120, -120);
        delay(10);
        attempts++;
    }
    motors.setSpeeds(0, 0);
}

// ===== OBSTACLE AVOIDANCE =====

void avoidObstacle() {
    // Step 1 — stop
    motors.setSpeeds(0, 0);
    delay(200);

    // Step 2 — turn right ~90°
    motors.setSpeeds(AVOID_SPEED, -AVOID_SPEED);
    delay(AVOID_TURN_MS);
    motors.setSpeeds(0, 0);
    delay(100);

    // Step 3 — go forward a little (clear the side of obstacle)
    motors.setSpeeds(AVOID_SPEED, AVOID_SPEED);
    delay(AVOID_FORWARD_MS);
    motors.setSpeeds(0, 0);
    delay(100);

    // Step 4 — turn left ~90° (now parallel to line again)
    motors.setSpeeds(-AVOID_SPEED, AVOID_SPEED);
    delay(AVOID_TURN_MS);
    motors.setSpeeds(0, 0);
    delay(100);

    // Step 5 — go forward past the obstacle
    motors.setSpeeds(AVOID_SPEED, AVOID_SPEED);
    delay(AVOID_FORWARD_MS);
    motors.setSpeeds(0, 0);
    delay(100);

    // Step 6 — turn right ~90° back toward line
    motors.setSpeeds(-AVOID_SPEED, AVOID_SPEED);
    delay(AVOID_TURN_MS);
    motors.setSpeeds(0, 0);
    delay(100);

    motors.setSpeeds(AVOID_SPEED, -AVOID_SPEED);
    delay(AVOID_TURN_MS);
    motors.setSpeeds(0, 0);
    delay(100);
    // Step 7 — go forward searching for line (3s timeout)
    motors.setSpeeds(AVOID_SPEED, AVOID_SPEED);
    unsigned long searchStart = millis();
    while (millis() - searchStart < 3000) {
        lineSensors.read(rawSensorValues);
        if (rawSensorValues[2] > 600) {
            motors.setSpeeds(0, 0);
            return;
        }
    }

    // Step 8 — sweep right slowly if still not found
    motors.setSpeeds(80, -80);
    searchStart = millis();
    while (millis() - searchStart < 1500) {
        lineSensors.read(rawSensorValues);
        if (rawSensorValues[2] > 600) {
            motors.setSpeeds(0, 0);
            return;
        }
    }
    motors.setSpeeds(0, 0);
}