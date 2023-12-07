import robot_control_mk1 as rc 
import time
import math 



# servo name 
SERVO_IDX = 'z'
SERVO_0 = 'a'
SERVO_1 = 'b'
SERVO_2 = 'c'
SERVO_3 = 'd'
SERVO_4 = 'e'
SERVO_5 = 'f'
SERVO_END = 'g'
#import serial
#import serial.tools.list_ports

#ports = list(serial.tools.list_ports.comports())
#for p in ports:
#    print p
 
#ser = serial.Serial('/dev/ttyACM0', 9600, timeout=None)
ser = rc.initialize_serial("/dev/ttyACM0")
print(ser.name)

rc.list_serial_port()

while True:
    #time.sleep(0.05)
    #if ser.isOpen() == True:
    #    if ser.inWaiting():
    #        text = ser.readline()
    #        print(text)
    #key = raw_input("enter:")
    #if key == 'a':
    #    rc.reset_robot_position(ser)
  
   
    #rc.move_robot_1_link(ser, SERVO_0, -30)
    #rc.move_robot_1_link(ser, SERVO_1, 30)
    #rc.move_robot_1_link(ser, SERVO_2, -30)
    #rc.move_robot_1_link(ser, SERVO_3, -20)
    #rc.move_robot_1_link(ser, SERVO_4, -30)
    #rc.move_robot_1_link(ser, SERVO_5, -90)
    #rc.reset_robot_position(ser)

    #rc.move_robot_6_link(ser, 0, -20, -90, -60, 0, 0)
    #rc.move_robot_6_link(ser, 10, 0, -80, -50, 0, 90)
  
    rc.move_robot_xyz(ser, 0.1, 0.1, 0.0, 90)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.1, 0.1, 0.0, 0)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.1, 0.1, 0.1, 0)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.14, 0.0, 0.1, 0)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.14, 0.0, 0.0, 90)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.14, 0.0, 0.1, 90)
    #time.sleep(1)
    rc.move_robot_xyz(ser, 0.1, 0.1, 0.1, 90)
    #time.sleep(1)
