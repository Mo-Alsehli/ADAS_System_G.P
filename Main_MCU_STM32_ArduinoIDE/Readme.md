# Speed Calculation, FCW, Blindspot, Cruise Control (PID), Emergency Stop and NRFs Receiver Transmitter
**This Folder Contains The Implementation Of Our Application Layer On the Bluepill board using ArduinoIDE**
## 1. Speed Calculation:
### Hall Effect Sensor:
| Sensor | Working Principle |
| --------------- | --------------- | 
| ![image](https://github.com/user-attachments/assets/94d589af-b910-4a0e-b9c4-a19175e55a5d)| ![image](https://github.com/user-attachments/assets/c5bd6370-a4b6-443e-90c7-0a9cd0b5f7c8)|
        - The Hall effect Sensor generates pulses when exposed to a magnet.
        - The software algorithm detects the pulse via an external interrupt and calculates 
          the RPM Based on the knowledge of wheel diameter.

## 2. Communication:
### NRF Sensor
![image](https://github.com/user-attachments/assets/0978bde5-e3d3-47a2-9262-74250d9d7cd2)

        - NRF is used for short wireless communication.
        - It must be paired with a private address.
        - It operates as a transceiver, allowing both transmission and reception of data.
        - It uses SPI for communication with a microcontroller. 

## 3. Distance Calculation:
### TF-Luna Radar
![image](https://github.com/user-attachments/assets/c8313ab7-1f64-43d9-8332-be975130eb04)

        - The TF-Luna sensor emits a modulated infrared light pulse towards an object.
        - The light pulse travels to the object and reflects back to the sensor.
        - The sensor measures the time it takes for the light to return to the sensor after hitting the object. 
        - This time is directly proportional to the distance between the sensor and the object.
        - It communicates with the board via I2C protocol.

## 4. Motor Control And Signal Processing:
### PWM
![image](https://github.com/user-attachments/assets/37b0bb67-c7e6-4893-8ec3-e8c2a9a51050)

        - The speed of a DC motor is directly proportional to the average voltage applied to it. 
        - By adjusting the duty cycle of the PWM signal, you control the average voltage delivered to the motor, 
          thereby controlling its speed.
        - We make multiple processes on the output signal just as PID control to get a desired output.

## 5. Forward Collision-Avoidance Algorithm:
![image](https://github.com/user-attachments/assets/173eeda3-206a-4289-86ec-4bde8d27fdff)

        - We have implemented an algorithm that calculates the current state of the car and take action.
        - In some cases when the threshold is within a specific range the algorithm issues a warning.
        - In critical cases, the algorithm immediately issues an Emergency braking stop.

## 6. Cruise Control:
## PID 
| Cruise Control | Working Principle |
| --------------- | --------------- | 
| ![image](https://github.com/user-attachments/assets/a9b8fc43-3820-4da5-969d-c9333b85a017)| ![image](https://github.com/user-attachments/assets/f40c952d-5154-4244-aeb7-c3e1e701f968)|


        - We have implemented a cruise control algorithm using PID Controller.
        - By adjusting P, I, and D parameters we could reach the desired speed with a specific time.
        - Considering Rise Time, Settle Time, and Overshoot.
        - The value of Cruise Control is received from the Dashboard Via NRF Reciver.

## BlindSpot and Rear-Collision System:
![image](https://github.com/user-attachments/assets/dd7c6f41-3b74-4793-a1ed-64faa5789d00)

      - Using an ultrasonic sensor and calculation of relative speed we have implemented the algorithm.
      - The software algorithm issues a warning on the dashboard at specific distance limits. 

## Warnings System:
      - The software application issues multiple warnings depending on the algorithm situation.
      - These warnings are transmitted via NRF to the Dashboard.




