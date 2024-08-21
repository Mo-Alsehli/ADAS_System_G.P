from PyQt5.QtCore import QObject, pyqtSignal
from PyQt5.QtCore import * 
from PyQt5.QtGui import * 
from PyQt5.QtWidgets import *
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QImage
import cv2, imutils
from analog import AnalogGaugeWidget
from cam_thread import CameraThread
from car_thread import Car_Thread
import time
# import infer_cam1 
import sys
import serial
import pynmea2
from twilio.rest import Client
import icons1
class Ui_MainWindow(object):
    state = "OFF"
    state_sleep = 0
    state_phone = 0
    state_coffee = 0
    def setupUi(self, MainWindow):
        if MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1738, 916)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.centralwidget.setStyleSheet(u"background-color: rgb(0, 0, 0);")
        self.horizontalLayout = QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.frame = QFrame(self.centralwidget)
        self.frame.setObjectName(u"frame")
        self.frame.setFrameShape(QFrame.NoFrame)
        self.frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_7 = QVBoxLayout(self.frame)
        self.verticalLayout_7.setSpacing(0)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.verticalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.widget = AnalogGaugeWidget(self.frame)
        self.widget.setObjectName(u"widget")
        self.widget.setEnabled(True)

        self.verticalLayout_7.addWidget(self.widget)

        self.frame_11 = QFrame(self.frame)
        self.frame_11.setObjectName(u"frame_11")
        self.frame_11.setFrameShape(QFrame.NoFrame)
        self.frame_11.setFrameShadow(QFrame.Raised)
        self.verticalLayout_3 = QVBoxLayout(self.frame_11)
        self.verticalLayout_3.setSpacing(0)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.frame_28 = QFrame(self.frame_11)
        self.frame_28.setObjectName(u"frame_28")
        self.frame_28.setFrameShape(QFrame.NoFrame)
        self.frame_28.setFrameShadow(QFrame.Raised)
        self.cruise_activate = QPushButton(self.frame_28)
        self.cruise_activate.setObjectName(u"cruise_activate")
        self.cruise_activate.setGeometry(QRect(170, 30, 240, 61))
        self.cruise_activate.setStyleSheet(u"\n"
"\n"
"QPushButton {\n"
"border:7px solid;\n"
"font: 90 30pt \"Verdana\";\n"
"color: rgb(0, 255, 255);\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;\n"
"\n"
"}\n"
"QPushButton::checked {\n"
"	border:10px solid;\n"
"    border-color: rgb(0, 255, 255);\n"
"  }\n"
"\n"
"\n"
"")
        self.cruise_activate.setCheckable(True)
        self.cruise_activate.setFlat(True)
        self.frame_22 = QFrame(self.frame_28)
        self.frame_22.setObjectName(u"frame_22")
        self.frame_22.setEnabled(True)
        self.frame_22.setGeometry(QRect(-10, 110, 540, 311))
        self.frame_22.setFrameShape(QFrame.NoFrame)
        self.frame_22.setFrameShadow(QFrame.Raised)
        self.horizontalSlider = QSlider(self.frame_22)
        self.horizontalSlider.setObjectName(u"horizontalSlider")
        self.horizontalSlider.setGeometry(QRect(30, 130, 501, 71))
        self.horizontalSlider.setStyleSheet(u"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00ffff, stop:1 #004343);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -20px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}")
        self.horizontalSlider.setMinimum(10)
        self.horizontalSlider.setMaximum(20)
        self.horizontalSlider.setOrientation(Qt.Horizontal)
        self.lcdNumber = QLCDNumber(self.frame_22)
        self.lcdNumber.setObjectName(u"lcdNumber")
        self.lcdNumber.setGeometry(QRect(70, 220, 211, 61))
        self.lcdNumber.setStyleSheet(u"color: rgb(0, 255, 255);")
        self.lcdNumber.setFrameShape(QFrame.NoFrame)
        self.lcdNumber.setSmallDecimalPoint(False)
        self.lcdNumber.setSegmentStyle(QLCDNumber.Filled)
        self.lcdNumber.setProperty("intValue", 0)
        self.Normal_cruise = QRadioButton(self.frame_22)
        self.Normal_cruise.setObjectName(u"Normal_cruise")
        self.Normal_cruise.setGeometry(QRect(200, 30, 220, 61))
        self.Normal_cruise.setStyleSheet(u"QRadioButton {\n"
"   border:7px solid;\n"
"	font: 90 30pt \"Verdana\";\n"
"	color: rgb(255, 255, 255);\n"
"	border-color: rgb(0, 116, 116);\n"
"	border-radius:20px;\n"
"\n"
"}\n"
"QRadioButton::checked {\n"
"	 border:10px solid;\n"
"	 border-color:rgb(0, 255, 255);\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width:                  10px;\n"
"    height:                 10px;\n"
"    border-radius:          7px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color:       rgb(0, 255, 255);\n"
"    border:                 2px solid white;\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked {\n"
"    background-color:       white;\n"
"    border:                 2px solid white;\n"
"}\n"
"")
        # self.adaptive_cruise = QRadioButton(self.frame_22)
        # self.adaptive_cruise.setObjectName(u"adaptive_cruise")
        # self.adaptive_cruise.setGeometry(QRect(315, 30, 211, 61))
        # self.adaptive_cruise.setStyleSheet(u"QRadioButton {\n"
# "   border:7px solid;\n"
# "	font: 90 30pt \"Verdana\";\n"
# "	color: rgb(255, 255, 255);\n"
# "	border-color: rgb(0, 116, 116);\n"
# "	border-radius:20px;\n"
# "\n"
# "}\n"
# "QRadioButton::checked {\n"
# "	 border:10px solid;\n"
# "	 border-color:rgb(0, 255, 255);\n"
# "}\n"
# "\n"
# "QRadioButton::indicator {\n"
# "    width:                  10px;\n"
# "    height:                 10px;\n"
# "    border-radius:          7px;\n"
# "}\n"
# "\n"
# "QRadioButton::indicator:checked {\n"
# "    background-color:       rgb(0, 255, 255);\n"
# "    border:                 2px solid white;\n"
# "}\n"
# "\n"
# "QRadioButton::indicator:unchecked {\n"
# "    background-color:       white;\n"
# "    border:                 2px solid white;\n"
# "}\n"
# "")
        self.label = QLabel(self.frame_22)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(280, 220, 151, 51))
        self.label.setStyleSheet(u"font: 20pt \"MS Shell Dlg 2\";\n"
"color: rgb(0, 255, 255)")

        self.verticalLayout_3.addWidget(self.frame_28)


        self.verticalLayout_7.addWidget(self.frame_11)

        self.verticalLayout_7.setStretch(0, 1)
        self.verticalLayout_7.setStretch(1, 1)

        self.horizontalLayout.addWidget(self.frame)

        self.frame_3 = QFrame(self.centralwidget)
        self.frame_3.setObjectName(u"frame_3")
        self.frame_3.setFrameShape(QFrame.NoFrame)
        self.frame_3.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_7 = QHBoxLayout(self.frame_3)
        self.horizontalLayout_7.setSpacing(0)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.frame_12 = QFrame(self.frame_3)
        self.frame_12.setObjectName(u"frame_12")
        self.frame_12.setStyleSheet(u"")
        self.frame_12.setFrameShape(QFrame.NoFrame)
        self.frame_12.setFrameShadow(QFrame.Raised)
        self.verticalLayout_13 = QVBoxLayout(self.frame_12)
        self.verticalLayout_13.setSpacing(0)
        self.verticalLayout_13.setObjectName(u"verticalLayout_13")
        self.verticalLayout_13.setContentsMargins(0, 0, 0, 0)
        self.frame_20 = QFrame(self.frame_12)
        self.frame_20.setObjectName(u"frame_20")
        self.frame_20.setStyleSheet(u"background-image: url(icons/PENUP_20240502_180121.png);\n"
"background-repeat: no-repeat;\n"
"border-image:none;\n"
"background-position:centre;\n"
"")
        self.frame_20.setFrameShape(QFrame.NoFrame)
        self.frame_20.setFrameShadow(QFrame.Raised)
        self.main_car = QPushButton(self.frame_20)
        self.main_car.setObjectName(u"main_car")
        self.main_car.setGeometry(QRect(130, 210, 391, 511))
        self.main_car.setStyleSheet(u"background-image:none;")
        icon = QIcon()
        icon.addFile(u"icons/Clipped_image_20240502_224504.png", QSize(), QIcon.Normal, QIcon.Off)
        self.main_car.setIcon(icon)
        self.main_car.setIconSize(QSize(500, 500))
        self.main_car.setFlat(True)
        self.wifi_down = QPushButton(self.frame_20)
        self.wifi_down.setObjectName(u"wifi_down")
        self.wifi_down.setEnabled(True)
        self.wifi_down.setGeometry(QRect(270, 710, 121, 91))
        icon1 = QIcon()
        icon1.addFile(u"icons/wifi_down.png", QSize(), QIcon.Normal, QIcon.Off)
        self.wifi_down.setIcon(icon1)
        self.wifi_down.setIconSize(QSize(105, 105))
        self.wifi_down.setFlat(True)
        self.wifi_up = QPushButton(self.frame_20)
        self.wifi_up.setObjectName(u"wifi_up")
        self.wifi_up.setEnabled(True)
        self.wifi_up.setGeometry(QRect(260, 130, 121, 88))
        icon2 = QIcon()
        icon2.addFile(u"icons/wifi.png", QSize(), QIcon.Normal, QIcon.Off)
        self.wifi_up.setIcon(icon2)
        self.wifi_up.setIconSize(QSize(105, 105))
        self.wifi_up.setFlat(True)
        self.front_car = QPushButton(self.frame_20)
        self.front_car.setObjectName(u"front_car")
        self.front_car.setGeometry(QRect(190, -120, 271, 261))
        self.front_car.setStyleSheet(u"background-image:none;")
        icon3 = QIcon()
        icon3.addFile(u"icons/backend.png", QSize(), QIcon.Normal, QIcon.Off)
        self.front_car.setIcon(icon3)
        self.front_car.setIconSize(QSize(250, 250))
        self.front_car.setFlat(True)
        self.left_car = QPushButton(self.frame_20)
        self.left_car.setObjectName(u"left_car")
        self.left_car.setGeometry(QRect(80, 580, 131, 301))
        self.left_car.setStyleSheet(u"background-image:none;")
        self.left_car.setIcon(icon)
        self.left_car.setIconSize(QSize(300, 300))
        self.left_car.setFlat(True)
        self.right_car = QPushButton(self.frame_20)
        self.right_car.setObjectName(u"right_car")
        self.right_car.setGeometry(QRect(433, 580, 135, 301))
        self.right_car.setStyleSheet(u"background-image:none;")
        self.right_car.setIcon(icon)
        self.right_car.setIconSize(QSize(300, 300))
        self.right_car.setFlat(True)
        self.rear_car = QPushButton(self.frame_20)
        self.rear_car.setObjectName(u"rear_car")
        self.rear_car.setGeometry(QRect(190, 800, 271, 191))
        self.rear_car.setStyleSheet(u"background-image:none;")
        icon4 = QIcon()
        icon4.addFile(u"icons/frontend.png", QSize(), QIcon.Normal, QIcon.Off)
        self.rear_car.setIcon(icon4)
        self.rear_car.setIconSize(QSize(200, 200))
        self.rear_car.setFlat(True)
        self.wifi_down.raise_()
        self.rear_car.raise_()
        self.wifi_up.raise_()
        self.main_car.raise_()
        self.right_car.raise_()
        self.left_car.raise_()
        self.front_car.raise_()

        self.verticalLayout_13.addWidget(self.frame_20)


        self.horizontalLayout_7.addWidget(self.frame_12)


        self.horizontalLayout.addWidget(self.frame_3)

        self.frame_2 = QFrame(self.centralwidget)
        self.frame_2.setObjectName(u"frame_2")
        self.frame_2.setFrameShape(QFrame.NoFrame)
        self.frame_2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.frame_2)
        self.horizontalLayout_9.setSpacing(0)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(0, 0, 0, 0)
        self.frame_5 = QFrame(self.frame_2)
        self.frame_5.setObjectName(u"frame_5")
        self.frame_5.setFrameShape(QFrame.NoFrame)
        self.frame_5.setFrameShadow(QFrame.Raised)
        self.verticalLayout_2 = QVBoxLayout(self.frame_5)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.alert_label = QLabel(self.frame_5)
        self.alert_label.setObjectName(u"alert_label")
        self.alert_label.setStyleSheet(u"font: 75 20pt \"Berlin Sans FB Demi\";\n"
"selection-background-color: rgb(255, 0, 0);")
        self.alert_label.setTextFormat(Qt.RichText)

        self.verticalLayout_2.addWidget(self.alert_label)

        self.frame_4 = QFrame(self.frame_5)
        self.frame_4.setObjectName(u"frame_4")
        self.frame_4.setFrameShape(QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QFrame.Raised)
        self.sos = QPushButton(self.frame_4)
        self.sos.setObjectName(u"sos")
        self.sos.setGeometry(QRect(190, 10, 241, 104))
        self.sos.setStyleSheet(u"QPushButton {\n"
"border:7px solid;\n"
"border-color:  rgb(0, 116, 116);\n"
"border-radius:20px;\n"
"\n"
"}\n"
"QPushButton::pressed {\n"
"    border-color: rgb(255, 0, 0);\n"
"  }\n"
"")
        icon5 = QIcon()
        icon5.addFile(u"icons/sos.png", QSize(), QIcon.Normal, QIcon.Off)
        self.sos.setIcon(icon5)
        self.sos.setIconSize(QSize(100, 85))
        self.sos.setCheckable(False)
        self.sos.setChecked(False)
        self.sos.setAutoDefault(False)
        self.sos.setFlat(False)

        self.verticalLayout_2.addWidget(self.frame_4)

        self.frame_6 = QFrame(self.frame_5)
        self.frame_6.setObjectName(u"frame_6")
        self.frame_6.setStyleSheet(u"border-color: rgb(15, 255, 235);")
        self.frame_6.setFrameShape(QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.frame_6)
        self.horizontalLayout_2.setSpacing(7)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.frame_9 = QFrame(self.frame_6)
        self.frame_9.setObjectName(u"frame_9")
        self.frame_9.setStyleSheet(u"border:7px solid;\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;\n"
"\n"
"")
        self.frame_9.setFrameShape(QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QFrame.Plain)
        self.frame_9.setLineWidth(2)
        self.frame_9.setMidLineWidth(0)
        self.horizontalLayout_3 = QHBoxLayout(self.frame_9)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.seatbelt = QPushButton(self.frame_9)
        self.seatbelt.setObjectName(u"seatbelt")
        self.seatbelt.setStyleSheet(u"border:none;\n"
"")
        icon6 = QIcon()
        icon6.addFile(u"icons/seatbelt.png", QSize(), QIcon.Normal, QIcon.Off)
        self.seatbelt.setIcon(icon6)
        self.seatbelt.setIconSize(QSize(90, 90))
        self.seatbelt.setFlat(True)

        self.horizontalLayout_3.addWidget(self.seatbelt)


        self.horizontalLayout_2.addWidget(self.frame_9)

        self.frame_7 = QFrame(self.frame_6)
        self.frame_7.setObjectName(u"frame_7")
        self.frame_7.setStyleSheet(u"border:7px solid;\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;")
        self.frame_7.setFrameShape(QFrame.NoFrame)
        self.frame_7.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_4 = QHBoxLayout(self.frame_7)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.coffee = QPushButton(self.frame_7)
        self.coffee.setObjectName(u"coffee")
        self.coffee.setStyleSheet(u"border:none;")
        icon7 = QIcon()
        icon7.addFile(u"icons/cup-of-drink.png", QSize(), QIcon.Normal, QIcon.Off)
        self.coffee.setIcon(icon7)
        self.coffee.setIconSize(QSize(90, 90))
        self.coffee.setFlat(True)

        self.horizontalLayout_4.addWidget(self.coffee)


        self.horizontalLayout_2.addWidget(self.frame_7)

        self.frame_10 = QFrame(self.frame_6)
        self.frame_10.setObjectName(u"frame_10")
        self.frame_10.setStyleSheet(u"border:7px solid;\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;")
        self.frame_10.setFrameShape(QFrame.NoFrame)
        self.frame_10.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_5 = QHBoxLayout(self.frame_10)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.phone = QPushButton(self.frame_10)
        self.phone.setObjectName(u"phone")
        self.phone.setStyleSheet(u"border:none;")
        icon8 = QIcon()
        icon8.addFile(u"icons/no-phone.png", QSize(), QIcon.Normal, QIcon.Off)
        self.phone.setIcon(icon8)
        self.phone.setIconSize(QSize(90, 90))
        self.phone.setFlat(True)

        self.horizontalLayout_5.addWidget(self.phone)


        self.horizontalLayout_2.addWidget(self.frame_10)

        self.frame_8 = QFrame(self.frame_6)
        self.frame_8.setObjectName(u"frame_8")
        self.frame_8.setStyleSheet(u"border:7px solid;\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;")
        self.frame_8.setFrameShape(QFrame.NoFrame)
        self.frame_8.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_6 = QHBoxLayout(self.frame_8)
        self.horizontalLayout_6.setSpacing(0)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.sleepy = QPushButton(self.frame_8)
        self.sleepy.setObjectName(u"sleepy")
        self.sleepy.setStyleSheet(u"border:none;")
        icon9 = QIcon()
        icon9.addFile(u"icons/driving.png", QSize(), QIcon.Normal, QIcon.Off)
        self.sleepy.setIcon(icon9)
        self.sleepy.setIconSize(QSize(90, 90))
        self.sleepy.setFlat(True)

        self.horizontalLayout_6.addWidget(self.sleepy)


        self.horizontalLayout_2.addWidget(self.frame_8)


        self.verticalLayout_2.addWidget(self.frame_6)

        self.cam_label = QLabel(self.frame_5)
        self.cam_label.setObjectName(u"cam_label")
        self.cam_label.setStyleSheet(u"border:7px solid;\n"
"border-color: rgb(0, 116, 116);\n"
"border-radius:20px;\n"
"\n"
"")

        self.verticalLayout_2.addWidget(self.cam_label)

        self.verticalLayout_2.setStretch(0, 2)
        self.verticalLayout_2.setStretch(1, 1)
        self.verticalLayout_2.setStretch(2, 1)
        self.verticalLayout_2.setStretch(3, 4)

        self.horizontalLayout_9.addWidget(self.frame_5)


        self.horizontalLayout.addWidget(self.frame_2)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        self.horizontalSlider.valueChanged.connect(self.lcdNumber.display)
        self.horizontalSlider.valueChanged.connect(self.send_adaptive_data)
        self.Normal_cruise.clicked.connect(self.send_adaptive_data)
        # self.adaptive_cruise.clicked.connect(self.send_adaptive_data)
        self.cruise_activate.clicked.connect(self.activate_deactivate)
        # self.sos.clicked.connect(self.send_message)
        self.sos.setDefault(False)
        self.CarThread = Car_Thread()
        self.CarThread.speed_val.connect(self.update_gauge_val)
        self.CarThread.adaptive_data.connect(self.CarThread.get_adaptive_data)
        self.CarThread.warnings.connect(self.collision_warnings)
        self.CarThread.start()
        self.worker = CameraThread()
        self.worker.frame_ready.connect(self.update_frame)
        self.worker.custom_signal.connect(self.driver_state)
        self.worker.start()

        QMetaObject.connectSlotsByName(MainWindow)
        self.activate = False
        self.started=False
        self.frame_22.setEnabled(False)
        self.lcdNumber.setVisible(False)
        self.label.setVisible(False)
        self.Normal_cruise.setCheckable(False)
        # self.adaptive_cruise.setCheckable(False)	
        self.horizontalSlider.setVisible(False)
        self.rear_car.setText("")
        self.rear_car.setVisible(False)
        self.wifi_down.setText("")
        self.wifi_down.setVisible(False)
        self.wifi_up.setText("")
        self.wifi_up.setVisible(False)
        self.left_car.setText("")
        self.left_car.setVisible(False)
        self.right_car.setText("")
        self.right_car.setVisible(False)
        self.front_car.setText("")
        self.front_car.setVisible(False)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.cruise_activate.setText(QCoreApplication.translate("MainWindow", u"Activate", None))
        self.Normal_cruise.setText(QCoreApplication.translate("MainWindow", u"Normal", None))
        # self.adaptive_cruise.setText(QCoreApplication.translate("MainWindow", u"Adaptive", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p><span style=\" font-size:36pt; color:#00ffff;\">Km/h</span></p></body></html>", None))
        self.main_car.setText("")
        
        # self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600; color:#00ffff;\">please fasten your seatbelt</span></p><p align=\"center\"><br/></p></body></html>", None))
        self.sos.setText("")
        self.seatbelt.setText("")
        self.coffee.setText("")
        self.phone.setText("")
        self.sleepy.setText("")
        self.cam_label.setText("")
    # retranslateUi

    def send_sos(self):
        x = 1
    def send_adaptive_data(self,speed):
        if self.activate:
            state = "ON"
        else:
            state = "OFF"
            self.horizontalSlider.setEnabled(False)
            self.horizontalSlider.setVisible(False)
        if self.Normal_cruise.isChecked():
            mode = "Normal"
            self.horizontalSlider.setEnabled(True)
            self.horizontalSlider.setVisible(True)
            self.lcdNumber.setEnabled(True)
            self.lcdNumber.setVisible(True)
            self.label.setVisible(True)
        elif self.adaptive_cruise.isChecked():
            mode = "Adaptive"
            self.horizontalSlider.setEnabled(True)
            self.horizontalSlider.setVisible(True)
            self.lcdNumber.setEnabled(True)
            self.lcdNumber.setVisible(True)
            self.label.setVisible(True)
        if speed >= 7:
            self.CarThread.adaptive_data.emit(speed ,state , mode)
        if state == "OFF" :
             speed = 0
             mode = "Normal"
             self.CarThread.adaptive_data.emit(speed ,state , mode)
    def activate_deactivate(self):
        if self.activate:
            self.activate=False
            self.cruise_activate.setText('Activate')
            self.frame_22.setEnabled(False)  
            self.lcdNumber.setEnabled(False)
            self.lcdNumber.setVisible(False)
            self.label.setVisible(False)
            self.Normal_cruise.setChecked(False)
            # self.adaptive_cruise.setChecked(False)
            self.Normal_cruise.setCheckable(False)
            self.lcdNumber.setProperty("intValue", 0)
            # self.adaptive_cruise.setCheckable(False)	
        #     self.horizontalSlider.setValue(0)
            self.horizontalSlider.setVisible(False)
            speed = 0
            mode = "Normal"
            state = "OFF"
            self.CarThread.adaptive_data.emit(speed ,state , mode)
        else:
            # self.send_adaptive_data("ON", 0)
            self.activate=True
            self.cruise_activate.setText('Deactivate')
            self.frame_22.setEnabled(True)
            # self.lcdNumber.setEnabled(True)
            # self.lcdNumber.setVisible(True)
            # self.label.setVisible(True)
            self.Normal_cruise.setCheckable(True)
            # self.adaptive_cruise.setCheckable(True)	
            self.Normal_cruise.setChecked(False)
            # self.adaptive_cruise.setChecked(False)	
        #     self.adaptive_cruise.setChecked(False)
        #     self.Normal_cruise.setChecked(False)

    def driver_state(self,icon,state):
        getattr(self, icon).setVisible(state)
        
        # if icon == "seatbelt" and state == True:
        #     self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600; color:#00ffff;\">Please fasten your seatbelt!</span></p><p align=\"center\"><br/></p></body></html>", None))
        
        if icon == "sleepy" and state == True:
            self.state_sleep = True
            self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; top:50px; font-weight:600; color:#00ffff;\">Please pay attention to the road!</span></p><p align=\"center\"><br/></p></body></html>", None))
        elif icon == "sleepy" and state == False:
            self.state_sleep = False
        if icon == "phone" and state == True:
            self.state_phone = True
            self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; top:150px;font-weight:600; color:#00ffff;\">Don't use your phone while driving.</span></p><p align=\"center\"><br/></p></body></html>", None))
        elif icon == "phone" and state == False:
            self.state_phone = False
        # elif icon == "phone" and state == False:
            # self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600; color:#00ffff;\"></span></p><p align=\"center\"><br/></p></body></html>", None))        # else:
        if icon == "coffee" and state == True:
            self.state_coffee = True
            self.alert_label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; top:150px;font-weight:600; color:#00ffff;\">You look tired, please take a rest!</span></p><p align=\"center\"><br/></p></body></html>", None))
        elif icon == "coffee" and state == False:
            self.state_coffee = False
        if (self.state_sleep == False) and (self.state_coffee == False) and (self.state_phone == False):
            self.alert_label.setText("")  
    def collision_warnings(self, icon, state):
        if icon == "close_cruise" and state == True:
            self.activate=False
            self.cruise_activate.setChecked(False)
            self.cruise_activate.setText('Activate')
            self.frame_22.setEnabled(False)  
            self.lcdNumber.setEnabled(False)
            self.lcdNumber.setVisible(False)
            self.label.setVisible(False)
            self.Normal_cruise.setChecked(False)
            # self.adaptive_cruise.setChecked(False)
            self.Normal_cruise.setCheckable(False)
            self.lcdNumber.setProperty("intValue", 0)
            # self.adaptive_cruise.setCheckable(False)	
        #     self.horizontalSlider.setValue(0)
            self.horizontalSlider.setVisible(False)
            speed = 0
            mode = "Normal"
            state = "OFF"
        else :
            getattr(self, icon).setVisible(state)

    def update_gauge_val(self,value):
        self.widget.updateValue(value)
    def update_frame(self,frame):
        image = imutils.resize(frame,width=620,height=1500 )
        frame = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        image = QImage(frame, frame.shape[1],frame.shape[0],frame.strides[0],QImage.Format_RGB888)
        self.cam_label.setPixmap(QtGui.QPixmap.fromImage(image))
    def get_location():

        serial_port = serial.Serial(
        port="/dev/ttyTHS1",
        baudrate=9600,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        )
        # Wait a second to let the port initialize
        time.sleep(1)
            # Send a simple header
        while True:
            if serial_port.inWaiting() > 0:
                data = serial_port.readline()
                if data[0:6] == b"$GPRMC":
                    newmsg=pynmea2.parse(data.decode('utf-8'))
                    lat=newmsg.latitude
                    lng=newmsg.longitude
                    if lng != 0 and lat!= 0:
                        return lat , lng
    def send_message(self):

        account_sid = 'AC1006684c2e66fc21dca5d41a1acb1ed1'
        auth_token = '42aa5a45a3c9b9be10ac92d3584a9eeb'
        client = Client(account_sid, auth_token)
        # lat, lng = get_location()
        text="The Driver at bad health condition here: "
        text+= "https://maps.app.goo.gl/ZMFwmzd9BrAX1iss7"
        # text+="http://maps.google.com/maps?q=loc:{:.5f},{:.5f}".format(lat,lng)
        message = client.messages.create(  from_='+17603096983',
                                           body = text,
                                           to='+201129860337')
if __name__ == '__main__':
    # parser = infer_cam1.argparse.ArgumentParser()
    # parser.add_argument("-e", "--engine", default=None, help="The serialized TensorRT engine")
    # #parser.add_argument("-i", "--input", default=None, help="Path to the image or directory to process")
    # #parser.add_argument("-o", "--output", default=None, help="Directory where to save the visualization results")
    # parser.add_argument("-l", "--labels", default="./labels_coco.txt", 
    #                     help="File to use for reading the class labels from, default: ./labels_coco.txt")
    # parser.add_argument("-d", "--detection_type", default="bbox", choices=["bbox", "segmentation"],
    #                     help="Detection type for COCO, either bbox or if you are using Mask R-CNN's instance segmentation - segmentation")
    # parser.add_argument("-t", "--nms_threshold", type=float, 
    #                     help="Override the score threshold for the NMS operation, if higher than the threshold in the engine.")
    # parser.add_argument("--iou_threshold", default=0.5, type=float, 
    #                     help="Select the IoU threshold for the mask segmentation. Range is 0 to 1. Pixel values more than threshold will become 1, less 0")                                                              
    # parser.add_argument("--preprocessor", default="fixed_shape_resizer", choices=["fixed_shape_resizer", "keep_aspect_ratio_resizer"],
    #                     help="Select the image preprocessor to use based on your pipeline.config, either 'fixed_shape_resizer' or 'keep_aspect_ratio_resizer', default: fixed_shape_resizer")
    # args = parser.parse_args()
    # import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    #ui.print_Data(12)
    # MainWindow.showFullScreen()  # for full screen view
    MainWindow.show()
    sys.exit(app.exec_())