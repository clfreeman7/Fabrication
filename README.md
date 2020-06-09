# MoSoRo
This repository documents the design, fabrication, and control of a modular soft robotic system MoSoRo capable of reconfiguration into a ball. 

## Fabrication

### Mechatronics
The basic mechatronics for the MoSoRo system consist of a microcontroller, DC motors, and motor drivers. The current prototype consists of the following:
- One (1) [Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3)
- Four (4) maxon DC Motors (273687,1105182-05 Rev. E)*
- Four (4) TOSHIBA Full-Bridge DC Motor Driver IC ([TB6643KQ8](https://toshiba.semicon-storage.com/ap-en/semiconductor/product/motor-driver-ics/brushed-dc-motor-driver-ics/detail.TB6643KQ.html))

\*  *These motors were purchased from eBay. However, the corresponding datasheets are propietary to the maxon company and we do not have access to them. We typically run these motors at about 15-20 V.* 

