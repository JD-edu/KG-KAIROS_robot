import serial 

seq = serial.Serial(
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
seq.port = "COM12"
a = 0
b = 0
c = 0
d = 0

seq.open()

while True: 
    if seq.isOpen() == True:  
        try:
            if seq.inWaiting():
                try:
                    command = seq.readline()
                    cmd_dec = command.decode()
                    if cmd_dec[0] == 'a':
                        a = cmd_dec.index('a')
                        b = cmd_dec.index('b')
                        c = cmd_dec.index('c')
                        d = cmd_dec.index('d')
                        e = cmd_dec.index('e')
                        a = int(cmd_dec[a+1:b])
                        b = int(cmd_dec[b+1:c])
                        c = int(cmd_dec[c+1:d])
                        d = int(cmd_dec[d+1:e])
                        print(a, b, c, d)
                    
                except ValueError:
                    print("value error")

                
        except IOError:
            print("IO error")