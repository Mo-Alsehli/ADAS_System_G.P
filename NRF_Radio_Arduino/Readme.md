# Radio Transiever 
**In This folder there is the implementation for the NRF module and data communication**

![image](https://github.com/user-attachments/assets/20df3fa8-42e5-409b-a85c-37dcc8a3afe5)

## 1. Data Package:
      - Data package consists of various variables to be recieved.
      - speed, brake, relative speed, distance and warnings are the data to be received.
      - After recieving data and warnings there is some processing on it to be sent via UART to Dashboard.

## 2. Data Sent
      - The Arduino receives Cruise Control Data Via Uart.
      - After that the Cruise Control Data is sent as a data package using a different pipe to the Car System.
