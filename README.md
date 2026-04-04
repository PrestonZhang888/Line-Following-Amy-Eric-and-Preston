# Lesson 9: Intersections & Dead Ends - Starter Code

## What's Included

```
Lesson_09_Starter/
├── platformio.ini          # PlatformIO configuration
├── include/
│   ├── RobotConfig.h       # All tunable constants
│   ├── RobotDisplay.h      # Display declarations
│   ├── RobotMotion.h       # Motion declarations
│   └── RobotSensors.h      # Sensor declarations
├── src/
│   ├── main.cpp            # Main state machine
│   ├── RobotDisplay.cpp    # Display functions
│   ├── RobotMotion.cpp     # Motion functions
│   └── RobotSensors.cpp    # Sensor functions
└── Green_Detection_Test/   # Troubleshooting tool
    ├── platformio.ini
    └── src/main.cpp
```

## Quick Start

1. Copy the folder to your PlatformIO projects directory
2. Open in VS Code with PlatformIO
3. Build and upload
4. Press B to calibrate, then B again to start

## 3 Sensors vs 5 Sensors

This code is configured for **3 SENSORS** (default jumper position).

### When You Move the Jumper to 5 Sensors:

**In RobotConfig.h:**
- Comment out the "3 Sensor" constants section
- Uncomment the "5 Sensor" constants section

**In RobotSensors.cpp:**
- Change `initThreeSensors()` → `initFiveSensors()`
- Change `sensorValues[3]` → `sensorValues[5]`
- Change `sensorValues[2]` → `sensorValues[4]`
- Change `i < 3` → `i < 5`

## Troubleshooting Green Detection

If the robot isn't detecting green markers correctly:

1. Open the `Green_Detection_Test` folder as a separate project
2. Upload it and open Serial Monitor (9600 baud)
3. Place robot on WHITE, GREEN, and BLACK surfaces
4. Note the actual sensor values
5. Adjust `GREEN_LOW_THRESHOLD` and `GREEN_HIGH_THRESHOLD` in RobotConfig.h

### Expected Values:
| Surface | Expected Range |
|---------|----------------|
| White   | 50 - 200       |
| Green   | 300 - 600      |
| Black   | 800 - 2000     |

### Setting Thresholds:
- `GREEN_LOW_THRESHOLD` = (your lowest green reading) - 50
- `GREEN_HIGH_THRESHOLD` = (your highest green reading) + 50

## Common Errors

| Error | Fix |
|-------|-----|
| `motors` not declared | Add `extern Zumo32U4Motors motors;` |
| `display` not declared | Add `extern Zumo32U4OLED display;` |
| Always turns right | Using 3 sensors with 5-sensor code (wrong index) |
| Never detects green | Thresholds wrong - run Green Detection Test |
| `ledYellow` redefinition | Delete custom LED functions, use built-in |

## Challenges

After the base code works, try the challenges in Lesson 9:

1. **LED Turn Indicators** - Light up LEDs when turning
2. **Line-Seeking Turns** - Turn until center sensor finds the line
3. **Encoder-Based Turns** - Use encoders for precise turns
4. **Debounced Detection** - Require 3 consecutive readings
5. **Right-Hand Rule** - Solve mazes without green markers

Good luck!
