import serial
import serial.tools.list_ports
import os
import time
import numpy as np 
import math

from ikpy import chain

ports = ""

# Command code for Arduino
CMD_RUN_ROBOT = '1\r\n'
CMD_SAVE_POS = '2\r\n'
CMD_RESET_ROBOT = '3\r\n'
CMD_MOVE_ROBOT_JOY = '4\r\n'
CMD_CLEAR_POS = '5\r\n'
CMD_MOVE_ROBOT_SERIAL = '6\r\n'
CMD_MOVE_ROBOT_6LINK = '7\r\n'

# servo name 
SERVO_IDX = 'z'
SERVO_0 = 'a'
SERVO_1 = 'b'
SERVO_2 = 'c'
SERVO_3 = 'd'
SERVO_4 = 'e'
SERVO_5 = 'f'
SERVO_END = 'g'


# Initialize serial port 
def initialize_serial(tty_serial):
    ser = serial.Serial(port = tty_serial, baudrate = 115200, timeout=1)
    return ser

# 
def list_serial_port():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        print(p)

# reset robot position 
def reset_robot_position(serial_port):
    try:
        msg = CMD_RESET_ROBOT
        serial_port.write(msg)
        #time.sleep(2)
        #print(msg)
    except (OSError, serial.SerialException):   
        pass         


# Move robot to xyz
def move_robot_xyz(serial_port, x, y, z, gripper):
    a = chain.Chain.from_urdf_file("testbot.urdf", base_elements=["base"])   
    #print(a) 
    target = [x, y, z]
    frame_target = np.eye(4)
    frame_target[:3, 3] = target
    joints = [0] * len(a.links)
    #print(joints)
    ik = a.inverse_kinematics(frame_target, initial_position=joints)
    #print("The angles of each joints are : ", a.inverse_kinematics(frame_target))
    arr =  a.inverse_kinematics(frame_target)
    base = int(math.degrees(arr[1]))*-1
    print("Base: ",base)
    shoulder = int(math.degrees(arr[2]))*-1
    print("Shoulder: ",shoulder)
    elbo = int(math.degrees(arr[3]))*-1
    print("Elbow: ",elbo)
    wrist_ud = int(math.degrees(arr[4]))*-1
    print("Wrist up/down: ",wrist_ud)
    move_robot_6_link(serial_port, base, shoulder, elbo, wrist_ud, 0, gripper)


# Move robot link
def move_robot_1_link(serial_port, servo, angle):
    if servo =='a' or servo == 'b' or servo =='c' or servo == 'd' or servo =='e'or servo == 'f':
        if angle < -90 or angle > 90:
            return 
        try:
            msg = CMD_MOVE_ROBOT_SERIAL+servo+str(angle)+'\n'
            serial_port.write(msg)
            time.sleep(1)
            #print(msg)
        except (OSError, serial.SerialException):   
            pass   
        
# Move robot 6 link
def move_robot_6_link(serial_port, base, shoulder, elbo, wrist_ud, wrist_turn, gripper):
    if base < -90 or base > 90:
        return  
    if shoulder < -90 or shoulder > 90:
        return
    if elbo < -90 or elbo > 90:
        return  
    if wrist_ud < -90 or wrist_ud > 90:
        return
    if wrist_turn < -90 or wrist_turn > 90:
        return
    if gripper < -90 or gripper > 90:
        return   
    try:
        msg = CMD_MOVE_ROBOT_6LINK+SERVO_0+str(base)+SERVO_1+str(shoulder)+SERVO_2+str(elbo)+SERVO_3+str(wrist_ud)+SERVO_4+str(wrist_turn)+SERVO_5+str(gripper)+SERVO_END+'\n'
        serial_port.write(msg)
        time.sleep(1)
        #print(msg)
    except (OSError, serial.SerialException):   
        pass   
          


# Run robot through saved positin
#def run_robot():

# Save current robot position 
#def save_robot():

if __name__ == __main__:
    



        