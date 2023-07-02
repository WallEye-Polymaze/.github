# Wall-Eye: 🤖

A Maze Solver Robot based on IRs array to follow the line using PID control with decision optimization while detecting and displaying specific colors we made it for POLYMAZE Competition held in Algiers organised by SPARK-VIC ENP🚀

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/picture.jpg" alt="WALL-EYE" width="800" >

Components:
============
- ESP32-DevKitC V4 Microcontroller 🕹️
- QTR-8RC IR array 📡
- TCRT5000 IR Sensor 🔵⚫
- L298N Motor Driver 🚦
- LM2595 voltage regulator 🔌
- N20 Motors 🎚️
- OLED Display 🖥️
- TCS34725 Color Sensor 🌈
- 12V Battery 🔋
- RGB Led 💡
- Buzzer 🔊
- Pushbutton 🔘
  
Design:
============
The 3D design done inside of SolidWorks then 3D printed and assembled.

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/design1.png" alt="design1" width="400" > <img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/design2.png" alt="design2" width="400" height="300">

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/SW.png" alt="SW1" width="805">

Shematic:
============
<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/schematic1.png" alt="schematic1" width="800">

Assembly:
============

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly2.png" alt="assembly2" height="255" ><img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly1.png" alt="assembly1" width="200" ><img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/assembly3.png" alt="assembly3" width="200" >

More Details:
============
- ESP32 microcontroller: Serves as the central processing unit, coordinating the actions of the system and enabling wireless communication capabilities. 🎛️
- IR array: Comprised of 8 infrared sensors, with 4 sensors (D3, D4, D5, D6) used in the PID controller for precise centering of the robot within the black - path. The remaining sensors, along with the 3 separate infrared sensors, are employed for detecting directions. 📡
- The L298N motor driver: It offers a dual H-bridge configuration, allowing it to control the speed and direction of two DC motors independently. 🚦
- The LM2595 voltage regulator: It provides efficient and reliable DC voltage conversion. 🔌
- The purpose of OLED is to display the precise decision being made. 🖥️
  
Functioning:
============
The autonomous maze-solving robotic system is based on an enhanced line-follower approach, incorporating PID control and intelligent decision-making algorithms. The ESP32 microcontroller acts as the brain of the system, processing data from the sensors and executing the required actions. 🧠

The LSRB algorithm used as the navigation strategy for traversing the maze. The robot prioritizes turning left when possible. If turning left is not an option, it proceeds forward. If neither left nor forward is viable, it attempts a right turn. Lastly, if none of these options are available, the robot moves backward. ⬅️⬆️➡️⬇️

The integration of a PID controller assists in maintaining the robot's alignment within the black path, enhancing its stability and accuracy during maze traversal along with detecting and displaying the exact colored stickers when the robot cross them, when Wall-Eye reaches the End-point in stops then moved to the start-point after path optimization it simply now passes through the shotest path. ⚙️🤖🕹️📚

<img src="https://github.com/WallEye-Polymaze/walleye/blob/dev/maze.png" alt="maze" width="820">


Codes:
============
- Main Code of Line Follower + Optimization 
- Component Test codes
- Calibration of IRs 

 
