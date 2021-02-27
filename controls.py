from time import sleep
import serial

KEY = b"$\r\n"
MAX = 15000
MIN = 0
POS_DICTIONARY = {
    "soft-center": (0, 0, 0),
    "hard-center": (MAX, MAX, MAX),
    0: (0, MAX, 0),
    30: (MAX, MAX, 0),
    60: (MAX, 0, 0),
    90: (MAX, 0, MAX),
    120: (0, 0, MAX),
    150: (0, MAX, MAX)
}

'''
Connects to arduino
'''
def serial_connect():
	ser = None
	connected = False
	for port in range(8):
	    try:
	        ser = serial.Serial('/dev/ttyACM%d' % port, 9600) # Establish the connection on a specific port
	        connected = True
	        print("Connected to device at /dev/ttyACM%d" % port)
	        break
	    except:
	        continue
	if not connected:
	    print("Failed to connect")

'''
Sends a test serial command
'''
def test_serial():
	ser.write(KEY)
	instr = b""
	while instr != KEY:
	    instr = ser.readline()
	    print(instr)

'''
Moves the dildo to a position
Arguments: a vector tuple argument, optional delay argument
Example input:
moveDildoPos((MAX, 0, 0), 25)
'''
def moveDildoPos(vector, delay=20):
    ch1, ch2, ch3 = vector
    
    channels_string = "C1%05d" % ch1
    channels_string += "C2%05d" % ch2
    channels_string += "C3%05d" % ch3

    delay_string = "D%03d" % delay
    
    code = channels_string + delay_string
    code += "\r\n"
    ser.write(str.encode(code))
    
    instr = b""
    result = ""
       
    while instr != KEY:
        instr = ser.readline()
        result += instr.decode("utf-8")
    
    return result

'''
pos is an angle that's a multiple of 30 degrees.
frequency is the number of taps that you want.
delay is the delay in microseconds 
'''
def moveDildoDegree(degree, delay=20):
    ch1, ch2, ch3 = POS_DICTIONARY[degree]
    
    channels_string = "C1%05d" % ch1
    channels_string += "C2%05d" % ch2
    channels_string += "C3%05d" % ch3

    delay_string = "D%03d" % delay
    
    code = channels_string + delay_string
    code += "\r\n"
    ser.write(str.encode(code))
    
    instr = b""
    result = ""
       
    while instr != KEY:
        instr = ser.readline()
        result += instr.decode("utf-8")
    
    return result

'''
Makes the dildo get hard and then soft n times
'''
def pulseDildo(pulseNumber):
    for i in range(pulseNumber):
        moveDildoPos((0, 0, 0))
        moveDildoPos((MAX, MAX, MAX))
    moveDildoPos((0, 0, 0))

'''
Swings dildo in a circle with increments of 30 degrees
'''
def swingDildo():
    for i in {0, 30, 60, 90, 120, 150, 0}:
        moveDildoDegree(i)
    resetDildo()

'''
resets dildo back to home
'''
def resetDildo():
    moveDildoPos((0, 0, 0), 30)
