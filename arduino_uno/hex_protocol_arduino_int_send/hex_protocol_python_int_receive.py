import serial
import threading 
import time 

class JDamr(object):
    def __init__(self, com="COM12"):
        self.ser = serial.Serial(com, 115200)
        if self.ser.isOpen():
            print("JDamr serial port opened!")
        else:
            print("Can't open JDamr serial port!")
        time.sleep(1)
    
    def receive_data(self):     
        self.ser.flushInput()
       
        while True:
            head = bytearray(self.ser.read())[0]
            if head == 0xf5:
                payload = [] 
                length = bytearray(self.ser.read())[0]
                for i in range(length):
                    value = bytearray(self.ser.read())[0]
                    payload.append(value)
                self.parse_cmd(payload)

    def receive_thread(self):
        try:
            task_name = "serial_thread"
            rx_task = threading.Thread(target=self.receive_data, name=task_name)
            rx_task.setDaemon(True)
            rx_task.start()
            print("Start serial receive thread ")
            time.sleep(.05)
        except:
            pass

    def parse_cmd(self, payload):
        print(payload)
        encode1 =int.from_bytes(payload, byteorder="big")
        print(encode1)

if __name__ == '__main__':
    com = 'COM6'
    bot = JDamr(com)
    time.sleep(1)
    bot.receive_thread()
   
    while True:
       pass


