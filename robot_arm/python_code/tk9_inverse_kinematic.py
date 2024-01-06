import ikpy.chain
import ikpy.utils.plot as plot_utils

import numpy as np
import time
import math

import ipywidgets as widgets
import serial
import matplotlib.pyplot as plt

def doIK():
    global ik
    old_position= ik.copy()
    ik = my_chain.inverse_kinematics(target_position, target_orientation, orientation_mode="Z", initial_position=old_position)

def updatePlot():
    ax.clear()
    my_chain.plot(ik, ax, target=target_position)
    plt.xlim(-0.5, 0.5)
    plt.ylim(-0.5, 0.5)
    ax.set_zlim(0, 0.6)
    fig.canvas.draw()
    fig.canvas.flush_events()
    
def move(x,y,z):
    global target_position
    target_position = [x,y,z]
    doIK()
    updatePlot()

    sendCommand(ik[1].item(),ik[2].item(),ik[3].item(),ik[4].item(),ik[5].item(),ik[6].item(),1)

def sendCommand(a,b,c,d,e,f,move_time):
    pass
    
    '''try:
        command = '0{:.2f} 1{:.2f} 2{:.2f} 3{:.2f} 4{:.2f} 5{:.2f} t{:.2f}\n'.format(math.degrees(a),math.degrees(b),math.degrees(c),math.degrees(d),math.degrees(e),math.degrees(f),move_time)
        ser.write(command.encode('ASCII'))
    except:
        pass
    '''
try:
    ser = serial.Serial('COM3',9600, timeout=1)
except:
    pass
my_chain = ikpy.chain.Chain.from_urdf_file("poppy_ergo.URDF")

target_position = [ 0, 0, 1]

target_orientation = [-1, 0, 0]

ik = my_chain.inverse_kinematics(target_position, target_orientation, orientation_mode="Y")
print("The angles of each joints are : ", list(map(lambda r:math.degrees(r),ik.tolist())))

computed_position = my_chain.forward_kinematics(ik)
print("Computed position: %s, original position : %s" % (computed_position[:3, 3], target_position))
print("Computed position (readable) : %s" % [ '%.2f' % elem for elem in computed_position[:3, 3] ])

import matplotlib.pyplot as plt
fig, ax = plot_utils.init_3d_figure()
fig.set_figheight(9)  
fig.set_figwidth(13)  
my_chain.plot(ik, ax, target=target_position)
plt.xlim(-0.5, 0.5)
plt.ylim(-0.5, 0.5)
ax.set_zlim(0, 0.6)
plt.show()

move(1,1,1)
sendCommand(ik[1].item(),ik[2].item(),ik[3].item(),ik[4].item(),ik[5].item(),ik[6].item(),4)
