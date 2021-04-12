#!/usr/bin/env python

import rospy
import time
import ledshim
import smbus
import numpy as np
from geometry_msgs.msg import PoseStamped

class LEDSHIM():
    def __init__(self):
        # LED related things
        ledshim.set_clear_on_exit()
        ledshim.display.i2c = smbus.SMBus(5)
        ledshim.set_brightness(0.6)

        self.time_window = rospy.get_param('~time_window')
        self.rate_threshold = rospy.get_param('~rate_threshold')
        self.time_stamp_array = np.random.rand(self.time_window)

        ns = rospy.get_namespace()
        vision_topic = "{}mavros/vision_pose/pose".format(ns)
        rospy.loginfo_once("Topic to subscribe: {}".format(vision_topic))

        rospy.Subscriber(vision_topic, PoseStamped, self.pose_callback)
        rospy.Timer(rospy.Duration(0.01), self.led_update)

    # callback function for time stamps
    def pose_callback(self, pose_data):
        header = pose_data.header
        self.time_stamp_array[1:-1] = self.time_stamp_array[0:-2]
        self.time_stamp_array[0] = rospy.Time(header.stamp.secs, header.stamp.nsecs).to_sec()
        rospy.loginfo("Seconds: {}".format(self.time_stamp_array[0]))

    # callback for LED loop
    def led_update(self, event):
        rate_in = self.compute_rate()
        #rospy.loginfo(rate_in)
        self.show_graph(rate_in)

    # computes a moving average of the frequency between messages published
    def compute_rate(self):
        dt_array = np.ones(self.time_window-1)
        for i in range(self.time_window - 1):
            dt_array[i] = self.time_stamp_array[i] - self.time_stamp_array[i+1]
        dt = (sum(dt_array)/float(self.time_window - 1)) 
        #print(dt)
        return 1.0/dt

    # make LEDs show colors based on information receival rate
    def show_graph(self, rate_in):
        r, g, b = 0, 0, 0
        for x in range(ledshim.NUM_PIXELS):
            if rate_in > self.rate_threshold:
                r, g, b = 0, 255, 0
            else:
                r, g, b = 255, 0, 0            
            ledshim.set_pixel(x, r, g, b)
        ledshim.show()


if __name__ == "__main__":
    # ROS related things
    rospy.init_node("led", anonymous=True)
    rospy.loginfo_once("Starting LED node")

    ledshim_class = LEDSHIM()
    rospy.spin()
