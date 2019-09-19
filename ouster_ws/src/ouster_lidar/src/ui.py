# -*- coding: utf-8 -*-
import sys
import os
import cv2
import numpy as np
import signal
from PIL import Image

import rospy
import roslib
import roslaunch
import rosbag
import pyrosbag as prb
import pcl_ros
import subprocess

import sensor_msgs.point_cloud2 as pc2
from sensor_msgs.msg import PointCloud2
from visualization_msgs.msg import Marker, MarkerArray

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QWidget, QInputDialog, QLineEdit, QFileDialog
from PyQt5.QtWidgets import QFrame
from PyQt5.QtGui import QIcon, QImage, QPainter, QPalette, QPixmap
from PyQt5.QtCore import QTimer

class Ui_Dialog(object):

    def setupUi(self, Dialog):
        # Set Dialog
        Dialog.setObjectName("Simulator")
        Dialog.setFixedSize(821, 620)
        Dialog.setWindowTitle("Simulator")

        # Set variables
        self.sub_marker = None
        self.sub_pointcloud = None
        self.selected_topic = None
        self.bag_player = None
        self.bag_playing = 0
        self.real_time_check = 0
        self.real_time_play = 0
        self.real_time_pause = 0

        # Set play pause stop button Layout
        self.horizontalLayoutWidget = QtWidgets.QWidget(Dialog)
        self.horizontalLayoutWidget.setGeometry(QtCore.QRect(510, 550, 311, 80))
        self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setObjectName("horizontalLayout")

        # Set Push Button
        self.play_Button = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.play_Button.setObjectName("play_Button")
        self.play_Button.setText("Play")
        self.horizontalLayout.addWidget(self.play_Button)

        self.pause_Button = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.pause_Button.setObjectName("pause_Button")
        self.pause_Button.setText("Pause")
        self.horizontalLayout.addWidget(self.pause_Button)

        self.stop_Button = QtWidgets.QPushButton(self.horizontalLayoutWidget)
        self.stop_Button.setObjectName("stop_Button")
        self.stop_Button.setText("Stop")
        self.horizontalLayout.addWidget(self.stop_Button)

        self.open_Button = QtWidgets.QPushButton(Dialog)
        self.open_Button.setGeometry(QtCore.QRect(10, 10, 99, 27))
        self.open_Button.setObjectName("open_Button")
        self.open_Button.setText("Open")

        self.open_Button_2 = QtWidgets.QPushButton(Dialog)
        self.open_Button_2.setGeometry(QtCore.QRect(10, 50, 99, 27))
        self.open_Button_2.setObjectName("open_Button")
        self.open_Button_2.setText("Open")

        # Set Label
        self.file_name_Label = QtWidgets.QLabel(Dialog)
        self.file_name_Label.setGeometry(QtCore.QRect(130, 15, 500, 20))
        self.file_name_Label.setObjectName('label')
        self.file_name_Label.setText("Select bag file !")

        self.file_name_Label_2 = QtWidgets.QLabel(Dialog)
        self.file_name_Label_2.setGeometry(QtCore.QRect(130, 55, 500, 20))
        self.file_name_Label_2.setObjectName('label')
        self.file_name_Label_2.setText("Select launch file !")

        # Set Combo Box
        self.select_topic_Box = ComboBox(Dialog)
        self.select_topic_Box.setGeometry(QtCore.QRect(518, 10, 178, 27))
        self.select_topic_Box.setObjectName("comboBox")
        self.select_topic_Box.popupAboutToBeShown.connect(self.combo_box_clicked)
        self.select_topic_Box.activated.connect(self.topic_selected)

        # retranslate Ui
        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

        # Set lidar data Frame
        self.frame = QtWidgets.QLabel(Dialog)
        self.frame.setGeometry(QtCore.QRect(10, 100, 500, 500))
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")

        # Set Color
        self.red = QtGui.qRgb(255, 0, 0)
        self.green = QtGui.qRgb(0, 255, 0)
        self.blue = QtGui.qRgb(0, 0, 255)

        # Set Text Browser
        self.textBrowser = QtWidgets.QTextBrowser(Dialog)
        self.textBrowser.setGeometry(QtCore.QRect(520, 100, 290, 470))
        self.textBrowser.setObjectName("textBrowser")
        self.textBrowser.horizontalScrollBar().setValue(0)

        # Set Check Box
        self.checkBox = QtWidgets.QCheckBox(Dialog)
        self.checkBox.setGeometry(QtCore.QRect(700, 15, 97, 22))
        self.checkBox.setObjectName("checkBox")
        self.checkBox.setText("Real Time")
        self.checkBox.stateChanged.connect(self.check_box_clicked)

        # Set Timer
        self.qTimer = QTimer()
        self.qTimer.setInterval(1) # 1000 ms = 1 s
        self.qTimer.timeout.connect(self.update)
        self.qTimer.start()

        # Set Button Event
        self.button_event()

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
         
    def button_event(self):
        self.play_Button.clicked.connect(self.play_clicked)
        self.pause_Button.clicked.connect(self.pause_clicked)
        self.stop_Button.clicked.connect(self.stop_clicked)
        self.open_Button.clicked.connect(self.open_clicked)
        self.open_Button_2.clicked.connect(self.open_clicked_2)

    def open_clicked(self):
        global bag_path
        open_bag = Open_File()

        if open_bag.filename.split('/')[-1].split('.')[-1] != 'bag':
            self.file_name_Label.setText('Please select bag file !')

        else:
            bag_path = open_bag.filename
            self.file_name_Label.setText(bag_path)

    def open_clicked_2(self):
        global bag_path
        open_launch = Open_File()
        
        if open_launch.filename.split('/')[-1].split('.')[-1] != 'launch':
            self.file_name_Label_2.setText('Please select launch file !')

        else:
            self.file_name_Label_2.setText(open_launch.filename)
            uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
            roslaunch.configure_logging(uuid)
            launch = roslaunch.parent.ROSLaunchParent(uuid, [open_launch.filename])
            launch.start()
            rospy.loginfo("started")
            rospy.init_node('ros_gui_node', anonymous=True)
            # launch.shutdown()

    def play_clicked(self):
        global bag_path
        if self.real_time_check == 0:
            if self.bag_playing == 0 and bag_path != "Select bag file !":
                self.bag_player = prb.BagPlayer(bag_path)
                self.bag_player.play()
                self.bag_playing = 1

        elif self.real_time_check == 1:
            self.real_time_play = 1
            if self.real_time_pause != 0:
                 self.real_time_pause = ~self.real_time_pause
           
    def pause_clicked(self):
        if self.real_time_check == 0:
            if self.bag_player is not None:
                self.bag_player.pause()

        elif self.real_time_check == 1: 
            self.real_time_pause = ~self.real_time_pause

    def stop_clicked(self):
        os.kill(os.getppid(), signal.SIGHUP)
    
    def check_box_clicked(self):
        if self.checkBox.isChecked() == True:
            self.init_frame()
            self.real_time_check = 1

        elif self.checkBox.isChecked() == False:
            self.init_frame()
            self.real_time_check = 0

    def combo_box_clicked(self):
        # update rostopic list
        self.select_topic_Box.clear()
        topic_list = []
        topic_list_dict = dict(rospy.get_published_topics())

        for key in topic_list_dict.keys():
            if topic_list_dict[key] == 'visualization_msgs/MarkerArray':
                topic_list.append(key)

        topic_list.sort()
        self.select_topic_Box.addItems(topic_list)

    def topic_selected(self, i):
        selected_topic = self.select_topic_Box.currentText()

        if selected_topic != '':
            if self.sub_marker is not None:
                self.sub_marker.unregister()
            self.sub_marker = rospy.Subscriber(selected_topic, MarkerArray, marker_msg_callback)
            self.sub_pointcloud = rospy.Subscriber("/segmentation", PointCloud2, pointcloud_msg_callback)

    def draw_box(self):
        
        global message
        global pointcloud
        global map
        global scale
        box_width_x = 0
        box_width_y = 0

        if self.real_time_check == 0:
            for p in pc2.read_points(pointcloud):
                x, y, z, i = p

                if 250 - scale * x > -500 and 250 - scale * x < 500 and 250 - scale * y > -500 and 250 - scale * y < 500:
                    map[int(250 - scale * x)][int(250 - scale * y)][0] = 255
                    map[int(250 - scale * x)][int(250 - scale * y)][1] = 255
                    map[int(250 - scale * x)][int(250 - scale * y)][2] = 255

            for mark in message.markers:
                box_width_x = mark.scale.y * scale
                box_width_y = mark.scale.x * scale

                x = 250 - mark.pose.position.y * scale
                y = 250 - mark.pose.position.x * scale

                if x > -500 and x < 500 and y > -500 and y < 500:
                    cv2.rectangle(map, (int(x - box_width_x / 2), int(y - box_width_y / 2)), (int(x + box_width_x / 2), int(y + box_width_y / 2)), (255, 0, 0), 1)
                
            qimg = QImage(map.data, 500, 500, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qimg)
            self.frame.setPixmap(pixmap)
            self.frame.show()
            self.init_frame()
        else:
            if self.real_time_play == 1:         
                if self.real_time_pause == 0:
                    for p in pc2.read_points(pointcloud):
                        x, y, z, i = p

                        if 250 - scale * x > -500 and 250 - scale * x < 500 and 250 - scale * y > -500 and 250 - scale * y < 500:
                            map[int(250 - scale * x)][int(250 - scale * y)][0] = 255
                            map[int(250 - scale * x)][int(250 - scale * y)][1] = 255
                            map[int(250 - scale * x)][int(250 - scale * y)][2] = 255

                    for mark in message.markers:
                        box_width_x = mark.scale.y * scale
                        box_width_y = mark.scale.x * scale

                        x = 250 - mark.pose.position.y * scale
                        y = 250 - mark.pose.position.x * scale

                        if x > -500 and x < 500 and y > -500 and y < 500:
                            cv2.rectangle(map, (int(x - box_width_x / 2), int(y - box_width_y / 2)), (int(x + box_width_x / 2), int(y + box_width_y / 2)), (255, 0, 0), 1)
                            
                    qimg = QImage(map.data, 500, 500, QImage.Format_RGB888)
                    pixmap = QPixmap.fromImage(qimg)
                    self.frame.setPixmap(pixmap)
                    self.frame.show()
                    self.init_frame()

                else:
                    pass

    def init_frame(self):
        global map
        map = np.zeros((500, 500, 3), dtype=np.uint8)

    def draw_text_browser(self):
        global message

        if self.real_time_check == 0:
            for mark in message.markers:
                self.textBrowser.append('*' * 35)
                self.textBrowser.append('id       : ' + str(mark.id))
                self.textBrowser.append('class    : ' + mark.ns)
                self.textBrowser.append('pose x   : ' + str('{0:.2f}'.format(mark.pose.position.x)))
                self.textBrowser.append('pose y   : ' + str('{0:.2f}'.format(mark.pose.position.y)))
                self.textBrowser.append('distance : ' + str('{0:.2f}'.format(np.sqrt(mark.pose.position.x**2 + mark.pose.position.y**2))))

        else:
            if self.real_time_play == 1:           
                if self.real_time_pause == 0:
                    for mark in message.markers:
                        self.textBrowser.append('*' * 35)
                        self.textBrowser.append('id       : ' + str(mark.id))
                        self.textBrowser.append('class    : ' + mark.ns)
                        self.textBrowser.append('pose x   : ' + str('{0:.2f}'.format(mark.pose.position.x)))
                        self.textBrowser.append('pose y   : ' + str('{0:.2f}'.format(mark.pose.position.y)))
                        self.textBrowser.append('distance : ' + str('{0:.2f}'.format(np.sqrt(mark.pose.position.x**2 + mark.pose.position.y**2))))

                else:
                    pass

    def update(self):
        try:
            # update text browser
            self.draw_text_browser()

            # update draw box
            self.draw_box()
        except:
            pass

# Class that make combobox
class ComboBox(QtWidgets.QComboBox):
    popupAboutToBeShown = QtCore.pyqtSignal()

    def showPopup(self):
        self.popupAboutToBeShown.emit()
        super(ComboBox, self).showPopup()

# Class that select bagfile
class Open_File(QWidget):
 
    def __init__(self):
        super(Open_File, self).__init__()
        self.title = 'PyQt5 file dialogs - pythonspot.com'
        self.left = 10
        self.top = 10
        self.width = 640
        self.height = 480
        self.filename = ''
        self.initUI()
 
    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        self.openFileNameDialog()
        self.show()
 
    def openFileNameDialog(self):    
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        fileName, _ = QFileDialog.getOpenFileName(self,"QFileDialog.getOpenFileName()", "","All Files (*);;Bag Files (*.bag)", options=options)
        if fileName:
            self.filename = fileName


def marker_msg_callback(msg):
    global message
    message = msg

def pointcloud_msg_callback(msg):
    global pointcloud
    pointcloud = msg

if __name__ == "__main__":
    
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)

    message = None
    pointcloud = None
    scale = 10
    map = np.zeros((500, 500, 3), dtype=np.uint8)
    bag_path = "Select bag file !"

    Dialog.show()
    sys.exit(app.exec_())


