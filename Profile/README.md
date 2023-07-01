# Wall-Eye: 🤖

A Maze Solver Robot based on IRs array to follow the line using PID control with decision optimization while detecting and displaying specific colors we made it for POLYMAZE Competition held in Algiers organised by SPARK-VIC ENP🚀

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/picture.jpg" alt="WALL-EYE" width="800" >

Components:
============
- ESP32 microcontroller 🕹️
- IR array (QTR-8RC) 📡
- L298N Motor Driver 🚦
- M2595 voltage regulator 🔌
- N20 Motors 🎚️
- OLED Display 🖥️
- COLOR SENSOR: TCS34725 🌈
- Batteries: 11.4-12V 🔋
- RGB Led 💡
  
Design:
============
The 3D design done inside of SolidoWorks then 3D printed and assembled.

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/design1.png" alt="design1" width="400" > <img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/design2.png" alt="design2" width="400" height="300">

Shematic:
============
<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/schematic1.png" alt="schematic1" width="400" height="300">

Assembly:
============

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly2.png" alt="assembly2" height="255" ><img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly1.png" alt="assembly1" width="200" ><img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly3.png" alt="assembly3" width="200" >

More Details:
============
- ESP32 microcontroller: Serves as the central processing unit, coordinating the actions of the system and enabling wireless communication capabilities. 🎛️
- IR array: Comprised of 8 infrared sensors, with 4 sensors (D3, D4, D5, D6) used in the PID controller for precise centering of the robot within the black - path. The remaining sensors, along with the 3 separate infrared sensors, are employed for detecting directions. 📡
- The L298N motor driver: It offers a dual H-bridge configuration, allowing it to control the speed and direction of two DC motors independently. 🚦
- The LM2595 voltage regulator: It provides efficient and reliable DC voltage conversion. 🔌
  
Functioning:
============
The autonomous maze-solving robotic system is based on an enhanced line-follower approach, incorporating PID control and intelligent decision-making algorithms. The ESP32 microcontroller acts as the brain of the system, processing data from the sensors and executing the required actions. 🧠

The LSRB algorithm serves as the navigation strategy for traversing the maze. The robot prioritizes turning left when possible. If turning left is not an option, it proceeds forward. If neither left nor forward is viable, it attempts a right turn. Lastly, if none of these options are available, the robot moves backward. ⬅️⬆️➡️⬇️

The integration of a PID controller assists in maintaining the robot's alignment within the black path, enhancing its stability and accuracy during maze traversal. ⚙️

Codes:
============
- Main Code of Line Follower + Optimization 
- Component Test codes
- Calibration of IRs 

 
