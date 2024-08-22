# Blindspot Asistance and Rear Collision Avoidance Using Bluepill

## 1. Distance Calculation:
### Ultrasonic Sensor:
![image](https://github.com/user-attachments/assets/aba879ba-43af-485f-906a-3d3aa2c764af)

    - We have used an ultra-sonic sensor to measure the distance.
    - It sends an ultrasonic wave and recieve it then calculate the time between them.
    - By knowing the speed of sound and the time signal took to be recieved we can calc distance.

### Bluepill:
    - Thanks to various timers on bluepill we are able to calc the time effectivly.
    - We have implemented a function that calc the micros between each signal then return the difference.
    - We have also implemented a delay function to insure safe operation for out ultra-sonic sensor.

## 2. BlindSpot Assitance:
    - Generates a warning when the distance between the two cars decreases to a specific limit.
    - Depending on the current situation of the car and the sensor readings we can issue the warning effectivly.

## 3. Rear-Collision Avoidance:
    - We have implemented an algorithm to detect rear collision and issue warning.
    - The algorithm uses the rear ultra-sonic sensor reading and calculates 
      the relative speed to specify the current situation.
