import time
import serial

ser = serial.Serial('/dev/tty.usbmodem1421', 9600)

for character_to_send in ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']:	

	print "About to send the letter %s" % character_to_send

	ser.write(character_to_send)
	ser.flush()

	# sleep for 5 seconds
	time.sleep(5)