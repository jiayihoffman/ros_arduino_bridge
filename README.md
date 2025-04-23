# Arduino Motor Controller

This code turns an Arduino into a motor controller!
It provides a simple serial interface to communicate with a high-level computer (e.g. running ROS), and generates the appropriate PWM signals for a motor driver, to drive two motors.

This is a fork of the [original code](https://github.com/joshnewans/ros_arduino_bridge), with the addition of the OSEPP_TB6612 motor shield and the adjustment of the encoder driver to use analog pins A2-A5 for encoder readings. For instructions on how to leverage the OSEPP_TB6612 motor shield in a robot car, please see my blog [Simplify Robot Cars using TB6612 Motor Shield](https://www.modularmachines.ai/security_robot/2025/04/21/SecurityRobot-MotorShield.html). 

Feedback/improvements are welcome. I currently only use the OSEPP_TB6612 motor shield, L298N driver, and the Arduino encoder mode.


## Functionality

The main functionality provided is to receive motor speed requests over a serial connection, and provide encoder feedback.
The original code has provisions for other features - e.g. read/write of digital/analog pins, servo control, but I've never used them.

The main commands to know are

- `e` - Motor responds with current encoder counts for each motor
- `r` - Reset encoder values
- `o <PWM1> <PWM2>` - Set the raw PWM speed of each motor (-255 to 255)
- `m <Spd1> <Spd2>` - Set the closed-loop speed of each motor in *counts per loop* (Default loop rate is 30, so `(counts per sec)/30`
- `p <Kp> <Kd> <Ki> <Ko>` - Update the PID parameters


## Gotchas

Some quick things to note

- There is an auto timeout (default 2s) so you need to keep sending commands for it to keep moving
- PID parameter order is PDI (?)
- Motor speed is in counts per loop
- Default baud rate 57600
- Needs carriage return (CR)
- Make sure serial is enabled (user in dialout group)
- Check out the original readme for more


## How to sync updates from the original repository
1. Fetch the latest changes 
```
git fetch <upstream>
```
2. Merge the Updates into my for
```
git checkout main
git merge <upstream>/main
```
3. push the updates to my fork
```
git push origin main
```
