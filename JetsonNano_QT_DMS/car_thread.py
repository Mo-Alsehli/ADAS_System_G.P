from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtCore import pyqtSlot as pyQtSlot
from PyQt5.QtCore import QSemaphore
import time
import serial
semaphore = QSemaphore(1)
class Car_Thread(QThread):
    adaptive_data = pyqtSignal(int, str, str)
    speed_val = pyqtSignal(int)
    warnings = pyqtSignal(str,bool)
    x = 0
    mode = 0
    speed = 0
    def __init__(self):
        super().__init__()
        self.arduino = serial.Serial(
        port = '/dev/ttyUSB0',
        baudrate = 115200,
        bytesize = serial.EIGHTBITS,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        timeout = 5,
        xonxoff = False,
        rtscts = False,
        dsrdtr = False,
        writeTimeout = 2
        )
        time.sleep(3)
        self.arduino.reset_input_buffer()
        # data_to_send = 10
        # self.arduino.write(data_to_send.to_bytes(1, byteorder='big'))
    @pyQtSlot(int,str,str)
    def get_adaptive_data(self, speed, state, mode):
        self.mode = mode
        self.speed = speed
        self.state = state
        # speed = bin(speed)
        adaptive = 0
        if state == "ON":
            adaptive = adaptive | 0b10000000
            if mode == "Adaptive":
                adaptive = adaptive | 0b01000000
            elif mode == "Normal":
                adaptive = adaptive & 0b10111111
            adaptive = adaptive | speed
        elif state == "OFF": 
             adaptive = 0
        # print(adaptive)
        data_to_send = 0
        # adaptive = 138
        self.arduino.write(adaptive.to_bytes(1, byteorder='big'))
        # adaptive = bin(adaptive)


    def run(self):
        # value = 0b01000011
        # inc = 1
        data = 0
        # #self.valueUnchanged.emit(5)
        while True:
            semaphore.acquire()
            try:
                data_to_send = 65  # Integer data to send (one byte)
                    # self.arduino.write(b'9') 
                # self.arduino.write(data_to_send.to_bytes(1, byteorder='big'))
        #         # self.arduino.write(b'9')
        #         # while self.arduino.in_waiting <= 0:
        #         #     time.sleep(0.01)
                data = self.arduino.readline().decode('utf-8').rstrip()# for char purposes
                # value = data.decode('utf-8') # for int purposes 
                value = data # for int purposes 
                if data:
                    # value = ord(value)
                    value = int(value)
                    # print(bin(value))
                    # value = value +1
                    # print(data.decode('utf-8'))
                    if (value & 0b01010000) == 0b01010000:
                            close_adaptive = 0
                            self.arduino.write(close_adaptive.to_bytes(1, byteorder='big'))
                            self.warnings.emit("close_cruise", True)
                            # print("close")

                    if value & 0b10000000 == 0b10000000:
                        speed = value & 0b00111111
                        self.speed_val.emit(speed)
                    elif value & 0b01000000 == 0b01000000:
                        if value & 0b00001000 == 0b00001000: #front collision
                            self.warnings.emit("front_car",True)
                            self.warnings.emit("wifi_up",True)
                        else :
                            self.warnings.emit("front_car",False)
                            self.warnings.emit("wifi_up",False)
                        if value & 0b00000100 == 0b00000100: #rear collision
                            self.warnings.emit("rear_car",True)
                            self.warnings.emit("wifi_down",True)
                        else :
                            self.warnings.emit("rear_car",False)
                            self.warnings.emit("wifi_down",False)
                        if value & 0b00000010 == 0b00000010: #right blindspot 
                            self.warnings.emit("right_car",True)
                        else :
                            self.warnings.emit("right_car",False)
                        if value & 0b00000001 == 0b00000001: #left blindspot 
                            self.warnings.emit("left_car",True)
                        else :
                            self.warnings.emit("left_car",False)
        #             # time.sleep(1)
            except Exception as e:
                print(e)
                self.arduino.close()

               
            semaphore.release()

        # speed = 0b 10 xxxxxx
        # warnings = 0b 01 xxxfbrl
        # from car = 0b sw xxxxx
        #######
        #### from jetson = 0b cmw 11111