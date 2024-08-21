
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QSemaphore
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtGui import QImage
import cv2, imutils
import time
import numpy as np
#from thread import CameraWorker

import numpy as np
import cv2

import time
from PyQt5.QtCore import QThread, pyqtSignal
import os


import cv2 
import numpy as np
from matplotlib import pyplot as plt

import infer_cam1 
import sys
from infer_cam1 import detections_data

#matplotlib inline
#category_index = label_map_util.create_category_index_from_labelmap(files['LABELMAP'])
semaphore = QSemaphore(1)
class CameraThread(QThread):
    
    frame_ready = pyqtSignal(object)
    custom_signal = pyqtSignal(str, bool)
     
    engine = "engine.trt"
    labels = "labels.txt"
    detection_type = "bbox"
    preprocessor = "fixed_shape_resizer"
    iou_threshold = 0.5
    nms_threshold = 0.5
    trt_infer = infer_cam1.TensorRTInfer(engine, preprocessor, detection_type, iou_threshold)
    # trt_infer = infer_cam1.TensorRTInfer(engine, preprocessor, detection_type,iou_threshold)
    # cap = cv2.VideoCapture("v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480, framerate = 30/1 ! videoconvert ! video/x-raw,format=BGR ! appsink") 
    def run(self):
        value = 0
        flag = 0
        labels = []
        eyes_flag= 0
        yawning_flag = 0
        start_time_eyes = 0
        start_time_yawning = 0
        current_time_eyes = 0
        current_time_yawning = 0
        status = 0
        eyes_closed = 0
        yawning_cnt = 0
        yawning = 0
        phone = 0
        phone_cnt = 0
        seatbelt = 0
        seatbelt_cnt = 0
        phone_reset_counter = 0
        seatbelt_reset_counter = 0
        yawning_time_cnt = 0
        
        cap = infer_cam1.cv2.VideoCapture("v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480, framerate = 30/1 ! videoconvert ! video/x-raw,format=BGR ! appsink")
        end = 0
        font = infer_cam1.cv2.FONT_HERSHEY_COMPLEX
        start = time.time()
        while cap.isOpened():
            # start = time.time()
            semaphore.acquire()
            ret, frame = cap.read()  # 0.033s/self.image
            self.frame_ready.emit(frame)
            frame = infer_cam1.cv2.resize(frame, (320,320))
            batcher = infer_cam1.ImageBatcher(frame, *self.trt_infer.input_spec(), preprocessor=self.preprocessor)
            for batch, images, scales in batcher.get_batch():
                detections = self.trt_infer.infer(batch, scales, self.nms_threshold) # 0.033s/detection
                dect = []
                for d in detections[0]:
                   dect.append(d['class'])
                for i in dect:
                    if i == 0:
                        phone +=1
                    if i == 2:
                        eyes_closed +=1
                    if i == 3:
                        yawning +=1
                    if i == 4:
                        seatbelt +=1
                
            end = time.time()
            if (end - start) >= 1:
                start = end
                phone_reset_counter += 1
                seatbelt_reset_counter += 1
                if yawning >= 10:
                    yawning_cnt +=1
                if yawning_cnt >= 5:
                    self.custom_signal.emit("coffee",True)
                    yawning_time_cnt += 1
                else:
                    self.custom_signal.emit("coffee",False)
                if yawning_time_cnt == 5:
                        self.custom_signal.emit("coffee",False)
                        yawning_time_cnt = 0
                        yawning_cnt = 0
                
                yawning = 0
                if eyes_closed >= 10:
                    self.custom_signal.emit("sleepy",True)
                else :
                    self.custom_signal.emit("sleepy",False)
                eyes_closed = 0
                if phone >=10:
                    phone_cnt +=1
                    
                    self.custom_signal.emit("phone",True)
                    
                    # print("leave phone")
                    phone_cnt = 0
                    phone_reset_counter = 0
                else :
                    self.custom_signal.emit("phone",False)                                                                         
                phone = 0
                if True:
                    if seatbelt <= 5:
                        seatbelt_cnt += 1
                    if seatbelt_reset_counter == 5:
                        if seatbelt_cnt >= 3:
                            # print("no_seatbelt")
                            self.custom_signal.emit("seatbelt",True)
                        else:
                            # print("seatbelt")
                            self.custom_signal.emit("seatbelt",False)
                        seatbelt_cnt = 0
                        seatbelt_reset_counter = 0
                seatbelt = 0
            # end = time.time()
            # if (end - start) >= 1:
            #     print(yawning)
            #     if flag == 0 :
            #         self.custom_signal.emit("pushButton",False)
            #         flag = 1
            #     else:
            #         self.custom_signal.emit("pushButton",True)
            #         flag = 0
            #     start = end    
                #self.valueChanged.emit(image)  # Emit the new value
            semaphore.release()
                 # Adjust sleep time as needed for desired update rate
            #cap.release()
    def inference(self,frame):
        batcher = infer_cam1.ImageBatcher(frame, *self.trt_infer.input_spec(), preprocessor=self.preprocessor)
        for batch, images, scales in batcher.get_batch():
            detections = self.trt_infer.infer(batch, scales, self.nms_threshold) # 0.033s/detection
            dect = []
            for d in detections[0]:
               dect.append(d['class'])