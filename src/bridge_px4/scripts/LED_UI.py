#!/usr/bin/env python

import rospy
import time
import ledshim
import smbus
import numpy as np
from geometry_msgs.msg import Pose 

# callback function for time stamps
def pose_callback(pose_data):
    global time_stamp_array
    time_stamp_array[1:-1] = time_stamp_array[0:-2]
    time_stamp_array[0] = int(pose_data.header.stamp)

# computes a moving average of the time between messages published
def compute_dt(time_window, time_stamp_array):
    dt = sum(time_stamp_array)/time_window
    return dt

# make LEDs show colors based on information receival rate
def show_graph(dt, time_threshold):
    for x in range(ledshim.NUM_PIXELS):
        if dt < time_threshold:
            r, g, b = 0, 255, 0
        else:
            r, g, b = 255, 0, 0            
            #r, g, b = [int(min(v, 1.0) * c) for c in [r, g, b]]
        ledshim.set_pixel(x, r, g, b)
    ledshim.show()

def main():
    # LED related things
    ledshim.set_clear_on_exit()
    ledshim.display.i2c = smbus.SMBus(5)
    ledshim.set_brightness(0.6)

    # ROS related things
    time_window = 5 #rospy.get_param('time_window')
    time_threshold = 3 #rospy.get_param('time_threshold')
    time_stamp_array = np.zeros((time_window, 0))
    rospy.init_node("led")
    rospy.Subscriber("/mavros/vision_pose/pose", Pose, pose_callback)

    # Loop for LED
    while True:
        dt = compute_dt(time_window, time_stamp_array)
        show_graph(dt, time_threshold)
        time.sleep(0.01)

if __name__ == "__main__":
    main()
