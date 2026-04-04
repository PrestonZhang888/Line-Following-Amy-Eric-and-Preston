#include "RobotSensors.h"
#include <Zumo32U4.h>
#include "RobotConfig.h"

Zumo32U4LineSensors         lineSensors;
Zumo32U4ButtonA             buttonA;
Zumo32U4ProximitySensors    proxSensors;
extern Zumo32U4Motors       motors;

unsigned int sensorValues[5];
unsigned int rawSensorValues[5];
int lastPosition = LINE_CENTER;

void initLineSensors() {
    lineSensors.initFiveSensors();
    proxSensors.initFrontSensor();
}

void calibrateLineSensors() {
    for (int i = 0; i < 100; i++) {
        if (i < 50) motors.setSpeeds(-100,  100);
        else         motors.setSpeeds( 100, -100);
        lineSensors.calibrate();
    }
    motors.setSpeeds(0, 0);
}

int readLinePosition() {
    lastPosition = lineSensors.readLine(sensorValues);
    return lastPosition;
}

bool isLineVisible() {
    lineSensors.read(rawSensorValues);
    unsigned int sum = 0;
    for (int i = 0; i < 5; i++) sum += rawSensorValues[i];
    return sum > LINE_LOST_THRESHOLD;
}

bool obstacleDetected() {
    proxSensors.read();
    int L = proxSensors.countsFrontWithLeftLeds();
    int R = proxSensors.countsFrontWithRightLeds();
    return (L > OBSTACLE_THRESHOLD || R > OBSTACLE_THRESHOLD);
}