/*
=====================================================
OBSTACLE AVOIDANCE - LINE FOLLOWING
=====================================================
*/

#include <Zumo32U4.h>
#include "RobotConfig.h"
#include "RobotMotion.h"
#include "RobotSensors.h"
#include "RobotDisplay.h"

// ===== EXTERN - Objects defined elsewhere =====
extern Zumo32U4Motors motors;
extern Zumo32U4ButtonA buttonA;
extern Zumo32U4OLED display;

// ===== LOCAL OBJECTS =====
Zumo32U4ButtonB buttonB;

// ===== GLOBAL STATE =====
RobotState currentState = STOPPED;

void setup() {
    Serial.begin(9600);

    display.clear();
    display.print("Obstacle Bot");
    display.gotoXY(0, 1);
    display.print("Press B");

    initLineSensors();
    buttonB.waitForButton();

    display.clear();
    display.print("Calibrating...");
    delay(500);

    calibrateLineSensors();

    display.clear();
    display.print("Ready!");
    display.gotoXY(0, 1);
    display.print("Press B");
    delay(500);
}

void loop() {
    switch (currentState) {

        case STOPPED: {
            motors.setSpeeds(0, 0);

            display.clear();
            display.print("STOPPED");
            display.gotoXY(0, 1);
            display.print("Press B");

            if (buttonB.getSingleDebouncedPress()) {
                currentState = FOLLOWING_LINE;
            }
            break;
        }

    case FOLLOWING_LINE: {
        // Print proximity counts for tuning
        proxSensors.read();
        Serial.print("Prox L:");
        Serial.print(proxSensors.countsFrontWithLeftLeds());
        Serial.print(" R:");
        Serial.println(proxSensors.countsFrontWithRightLeds());

    if (obstacleDetected()) {
        motors.setSpeeds(0, 0);
        display.clear();
        display.print("OBSTACLE!");
        Serial.println("Obstacle detected - avoiding");
        currentState = AVOIDING_OBSTACLE;
        break;
    }
    // ... rest of line following unchanged

            // — PID line following —
            int position = readLinePosition();
            int error = position - LINE_CENTER;
            static int lastError = 0;
            int correction = KP * error + KD * (error - lastError);
            lastError = error;

            int leftSpeed  = constrain(BASE_SPEED + correction, 0, MAX_SPEED);
            int rightSpeed = constrain(BASE_SPEED - correction, 0, MAX_SPEED);
            motors.setSpeeds(leftSpeed, rightSpeed);

            if (buttonB.getSingleDebouncedPress()) {
                currentState = STOPPED;
            }
            break;
        }

        case AVOIDING_OBSTACLE: {
            avoidObstacle();

            display.clear();
            display.print("Line found!");
            Serial.println("Avoidance done - resuming");
            delay(200);

            currentState = FOLLOWING_LINE;
            break;
        }
    }
}