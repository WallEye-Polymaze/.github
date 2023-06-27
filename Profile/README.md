# WALL-Eye: 🤖
A Maze Solver Robot based on IR array to follow the line then optimaze it to solve the maze while detecing the wanted colors using color sensor.

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/Picture.jpeg" alt="WALL-EYE" width="500" height="500">

 Components:
 ============
- ESP32 microcontroller
- IR array ( QTR-8RC)
- L298N Motor Driver
- LM2595 voltage regulator
- N20 Motors
- OLED Display
- COLOR SENSOR: TCS34725
- Batteries: 11.4-12v
- RGB Led
- Jumpers 

More Deteils:

- ESP32 microcontroller: Serves as the central processing unit, coordinating the actions of the system and enabling wireless communication capabilities.
- IR array: Comprised of 8 infrared sensors, with 4 sensors (D3, D4, D5, D6) used in the PID controller for precise centering of the robot within the black path. The remaining sensors, along with the 3 separate infrared sensors, are employed for detecting directions. 
- The L298N motor driver: it offers a dual H-bridge configuration, allowing it to control the speed and direction of two DC motors independently.
- The LM2595 voltage regulator: it provides efficient and reliable DC voltage conversion

Functioning:
 ============

The autonomous maze-solving robotic system is based on an enhanced line-follower approach, incorporating PID control and intelligent decision-making algorithms. The ESP32 microcontroller acts as the brain of the system, processing data from the sensors and executing the required actions.

The LSRB algorithm serves as the navigation strategy for traversing the maze. The robot prioritizes turning left when possible. If turning left is not an option, it proceeds forward. If neither left nor forward is viable, it attempts a right turn. Lastly, if none of these options are available, the robot moves backward.

The integration of a PID controller assists in maintaining the robot's alignment within the black path, enhancing its stability and accuracy during maze traversal.

