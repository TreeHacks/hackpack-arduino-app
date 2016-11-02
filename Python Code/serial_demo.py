"""
Simple python app to read from USB serial port. 

TreeHacks 2017
"""

import serial 

try: 
	ser = serial.Serial('/dev/tty.usbserial', 9600)
	while True:
		print ser.readline()
except: 
	print 'port not found'