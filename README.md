# ClubMaster: Golf Club Swing Tracker
This project is an Arduino-based golf club swing tracker named "ClubMaster." It uses an Arduino Nano with an LSM6DSOX inertial measurement unit (IMU) to measure and track the swing speed, angle, and acceleration of a golf club. The data is then sent to the Arduino IoT Cloud for real-time monitoring and analysis.

## Features
Measure Swing Speed: Calculates the speed of the golf club head at the point of impact.
Track Swing Angle: Measures the angle of the swing to analyze swing path.
Acceleration Monitoring: Tracks the acceleration during the swing to identify key metrics.
Stroke Count: Counts the number of strokes/hits during practice.
Maximum Speed: Records the maximum swing speed achieved.
IoT Cloud Integration: Sends data to the Arduino IoT Cloud for real-time monitoring.
## Components
Arduino Nano with LSM6DSOX IMU
Lithium Battery (provides 4 hours of battery life)
Step-up Converter (to power the Arduino)
3D-printed Mount (design available in the repository)
# Getting Started
## Hardware Setup
Reccomended board: Arduino Nano RP2040 (Has the built-in IMU)
Assemble Components: Connect the Arduino Nano, battery, and step-up converter according to the circuit diagram.
Install in Golf Club: Place the assembled components inside the 3D-printed mount and secure it in the golf club.
## Software Setup
Arduino IDE: Install the Arduino IDE.
Libraries: Install the following libraries through the Arduino Library Manager:
Arduino_LSM6DSOX
Arduino IoT Cloud
Upload Code: Upload the provided Arduino code to the Arduino Nano.
Arduino Code
