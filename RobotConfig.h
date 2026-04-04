
#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// ===== PHYSICAL PROPERTIES =====
// These values define your robot's hardware

// Encoder counts per complete wheel rotation
// (12 counts/motor rotation × 75.81 gear ratio = 909.7)
const float COUNTS_PER_ROTATION = 909.7;

// Wheel diameter in millimeters (measure yours!)
const float WHEEL_DIAMETER_MM = 39.0;

// Wheel circumference = π × diameter
const float WHEEL_CIRCUMFERENCE_MM = 3.14159 * WHEEL_DIAMETER_MM;

// Encoder counts per centimeter of travel
const float COUNTS_PER_CM = COUNTS_PER_ROTATION / (WHEEL_CIRCUMFERENCE_MM / 10.0);

// ===== TURNING PROPERTIES =====
// Distance between wheel centers (for turn calculations)
const float WHEEL_BASE_MM = 85.0;

// Circumference of the turn circle
const float TURN_CIRCUMFERENCE_MM = 3.14159 * WHEEL_BASE_MM;

// Encoder counts per degree of rotation
const float COUNTS_PER_DEGREE = (TURN_CIRCUMFERENCE_MM / 360.0) * 
                                (COUNTS_PER_ROTATION / WHEEL_CIRCUMFERENCE_MM);

// ===== SPEED SETTINGS =====
// Adjust these to change robot behavior
const int DRIVE_SPEED = 150;  // Speed for straight driving (0-400)
const int TURN_SPEED = 140;   // Speed for turning (0-400)

// ===== LINE FOLLOWING CONSTANTS - 3 SENSORS =====
// (Comment this section and uncomment 5-sensor section after moving jumper)
// ===== LINE FOLLOWING CONSTANTS - 3 SENSORS =====
const int LINE_CENTER = 2000;
const int BASE_SPEED = 150;        // ← was 80, too slow
const float KP = 0.12;             // ← slightly increased
const float KD = 1.5;              // ← NEW: dampens oscillation
const int MAX_SPEED = 250;         // ← was 200
const int LINE_LOST_THRESHOLD = 200;
const unsigned long MAX_GAP_TIME = 500;
// ===== OBSTACLE AVOIDANCE =====
const int OBSTACLE_THRESHOLD  = 5;
const int AVOID_SPEED         = 150;
const int AVOID_TURN_MS    = 500;  // ← slightly less than 90°
const int AVOID_FORWARD_MS = 1200;  // ← enough to clear obstacle
const int RETURN_TURN_MS   = 500;  // ← should match AVOID_TURN_MS


// ===== ROBOT STATES (enum) =====
// ===== ROBOT STATES (enum) =====
enum RobotState {
    FOLLOWING_LINE,
    AVOIDING_OBSTACLE,
    STOPPED
};
#endif  // ROBOT_CONFIG_H