import time
import serial
import bikeshare

BIKESHARE_URL = "http://www.capitalbikeshare.com/data/stations/bikeStations.xml"
# BIKESHARE_STATION_ID = 31221
BIKESHARE_STATION_ID = 31212

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0)

# let's give the Arduino...a second or two
print "Waiting 3 seconds for Arduino to boot..."
time.sleep(3)

bs = bikeshare.BikeShareInterface(BIKESHARE_URL, BIKESHARE_STATION_ID)

last_check = 0
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
		# time.sleep(0.9)

		# reset the string (otherwise it would just keep growing)
		incoming_message = ""


	if time.time() > (last_check + 60):
		print "OK, checking Bikeshare again."
		bs.refresh()
		print bs.bike_availability

		bikes = bs.bike_availability[BIKESHARE_STATION_ID]['bikes']
		if bikes > 1:
			answer = 'Y'
		elif bikes == 1:
			answer = 'M'
		else: # < 1
			answer = 'N'

		# now make the Arduino do something!
		ser.write(answer)
		print "Sent to Arduino: %s" % answer

		last_check = time.time()
