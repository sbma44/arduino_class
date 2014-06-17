# This is an example of nonblocking serial reading. 
#
# It is a very simple technique to understand, but for many
# applications it suffers from serious shortcomings.

import time
import serial

def do_something_else():
	print "[LAPTOP]  I'm doing something down here, too // %s" % time.time()

# initialize the serial port
ser = serial.Serial('/dev/tty.usbmodem1411', 9600)

# do the following forever
while True:

	# read from the serial port up to the first "\n" (newline) character
	# the program will wait here until it sees the newline come in
	incoming_message = ser.readline()

	# display the message we received
	print "[ARDUINO] %s" % incoming_message

	# do you want your script to do something besides wait? too bad!
	do_something_else()
