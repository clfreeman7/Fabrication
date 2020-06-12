# MoSoRo
This repository documents the design, fabrication, and control of a modular soft robotic system MoSoRo capable of reconfiguration into a ball. 

## Fabrication

### Mechatronics
The basic mechatronics for the MoSoRo system consist of a microcontroller, DC motors, and motor drivers. The current prototype consists of the following:
- One (1) [Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3)
- Four (4) maxon DC Motors (273687,1105182-05 Rev. E)*
- Four (4) TOSHIBA Full-Bridge DC Motor Driver IC ([TB6643KQ8](https://toshiba.semicon-storage.com/ap-en/semiconductor/product/motor-driver-ics/brushed-dc-motor-driver-ics/detail.TB6643KQ.html))

\*  *These motors were purchased from eBay. However, the corresponding datasheets are propietary to the maxon company and we do not have access to them. We typically run these motors at about 15-20 V.* 

A basic circuit schematic is shown below:
![test](MoSoRo_Schematic.png)

#### Alternative Components
The same mechatronics design and code can be used with other components as well. We have also used the following:
- One (1) [Arduino Nano](https://store.arduino.cc/usa/arduino-nano)
- One (1) [Arduino Nano 33 IOT] (https://store.arduino.cc/usa/nano-33-iot), with built-in Bluetooth connectivity
- Four (4) [Faulhaber Minimotor SA 1219 E 015 G](https://www.faulhaber.com/en/products/series/1219g/)*

#### Motor Considerations
Given our use of "bang-bang control" (where actuators are only either on or off), the motors used do not have to be servomotors or have encoders. Thus, motors should be chosen to satisfy desired size and torque requirements. We found that Faulhaber motors were slower but could provide more torque. 

#### Alternative Configruations
We have parameterized our control code such that different actuator configurations and quanitites do not require significant changes to the code. For a robot with a different number of actuators, simply change the constant parameter in the setup portion of the code. The control code is independent of the morphology or configuration of the robot. Rather, the number of motors determines the number of possible robot states (i.e., the total number of on/off motor combinations) and labels them. The user can then input a desired sequence of on/off combinations to control the robot.

### Code
The basic code presented [here](neweuler.ino) enables open-loop control of a motor-tendon actuated robot by cycling through a predetermined input sequence (i.e. locomotion gait). 
