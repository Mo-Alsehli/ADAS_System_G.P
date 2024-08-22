# PyQt Design, DMS Model Running Inference.
**This Folder Contains the implementation of Dashboard QT Design aligned with DMS Model Inference**

![dashboard](https://github.com/user-attachments/assets/aaf26f71-673a-462f-a9c2-c7599bdf8787)

# Summary of the Application's Functionality
- *Driver Monitoring*: The application monitors the driver's behavior using AI, detecting states like fatigue, phone usage, etc.
  This is done in a separate thread and integrated into the UI for real-time feedback.
- *Car Monitoring and Control*: The application communicates with the car's systems via UART, receiving data like speed
  and controlling features like cruise control. This data is displayed on the UI.
- *Multithreading*: Critical for maintaining a responsive UI, multithreading allows the application to handle video processing
  and UART communication without blocking the main thread.

## 1. QT Design
![image](https://github.com/user-attachments/assets/d6fc6530-a035-4c9f-869c-580f5687a8dc)

        - A graphical user interface (GUI) design tool that is part of the Qt framework.
        - It consists of two parts Frontend and Backend.
        - The frontend part is the design layout of the Dashboard.
        - Backend is the Functionality of multiple components in the design layout.

QT Multithreading
---
![image](https://github.com/user-attachments/assets/e9d7bbfb-731a-495d-9116-d6f10d21403c)

        - The CameraThread runs in a separate thread from the main application, ensuring that the intensive
          task of processing video frames and running inference does not block the GUI.
        - semaphore: A QSemaphore is used to control access to shared resources, preventing race conditions.
        - Signals (frame_ready and custom_signal) are emitted from this thread to update the main UI or other components.

## 2. Last_UI File Full Overview:
- The last_ui.py file defines the user interface (UI) for a dashboard application using PyQt5.

        - run(self) Method:
        - This is the main method of the thread, which starts when the thread is executed.
        - Initializes several flags and counters related to the monitoring system (e.g., eyes, yawning, phone, seatbelt).
        - Captures video from the specified camera using OpenCV and processes each frame.
        - Detects various states such as whether the driver's eyes are closed, yawning, or using a phone.
        - Emits signals based on detected conditions to update the GUI or trigger other actions.
        - The method runs in a loop, processing frames continuously until the thread is stopped.

## 3. Cam_Thread File Full Overview:
- The cam_thread.py file defines a CameraThread class, which handles camera input and integrates with an AI model for driver monitoring.
- The class is built using PyQt's QThread for multithreading, allowing the camera and AI inference
  to run concurrently with the main GUI, ensuring the UI remains responsive.
- This inference depends on the AI model and for more details about the Inference go to [DMS](https://github.com/Mo-Alsehli/ADAS_System_G.P/tree/master/Driver_Monitoring_System_JetsonNano_SSDMoibileNet).

## 4. Car_Thread File Full Overview:
- The car thread handles the communication Between Jetson Nano and Arduino Via UART.
- It sends the data of Cruise Control to the Arduino to be sent to the car.
- It also receives the data of speed and various warnings to be displayed.

# Multithreading Integration
    I. CameraThread Integration: The CameraThread continuously captures and processes video frames in a separate thread.
    This ensures that the video processing (which could be computationally expensive) does not block the main UI thread,
    allowing the application to remain responsive. The results of the processing (e.g., detecting if the driver is distracted)
    are sent back to the UI through signals, which then update the display accordingly.

    II. Car_Thread Integration: Similarly, the Car_Thread handles real-time data exchange with the car's systems via UART. 
    This thread might be responsible for reading sensor data (e.g., speed) and sending commands (e.g., adjusting cruise control). 
    The UI reflects these interactions, showing the current speed, cruise control status, etc., in real time.

    III. UI Responsiveness: By offloading heavy tasks like video processing and UART communication to separate threads, 
    the UI remains responsive. Users can interact with the dashboard, and the application can update various displays 
    in real-time without any noticeable lag.
