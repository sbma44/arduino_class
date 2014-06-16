# This is an example of nonblocking serial reading. 
#
# Because it's not always possible to anticipate when anticipate
# message can arrive, it's very useful to only perform actions
# when a complete message has been received (instead of waiting
# for it indefinitely).
# 
# Another approach to this problem is to use threading or forked
# processes. This requires a lot more Python knowledge, though.

import time
import serial

def do_something_else():
	print "[LAPTOP]  I'm doing something down here, too // %s" % time.time()

# initialize the serial port with timeout=0 to disable blocking
ser = serial.Serial('/dev/tty.usbmodem1421', 9600, timeout=0)

# we will use this string as a scratch-pad for half-collected messages
incoming_message = ""

while True:

	# add whatever is on the serial port to our scratchpad
	incoming_message = incoming_message + ser.read()
	
	# we are using the newline character to be a signal that
	# the message is complete and ready to be acted upon.
	# it's like saying "OVER!" into a walkie talkie.
	if "\n" in incoming_message:
		print "[ARDUINO] %s" % incoming_message
				
		# pause briefly so we can read the message
		time.sleep(0.9)

		# reset the string (otherwise it would just keep growing)
		incoming_message = ""

	# we can do other things in this loop because the read is 
	# non-blocking
	do_something_else()