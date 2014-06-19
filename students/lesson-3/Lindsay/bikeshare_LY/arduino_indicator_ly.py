import time
import datetime
import serial
import bikeshare

from datetime import timedelta

BIKESHARE_URL = "http://www.capitalbikeshare.com/data/stations/bikeStations.xml"
BIKESHARE_STATION_ID = 31221

ser = serial.Serial('/dev/tty.usbmodemfd131', 9600, timeout=0)

incoming_message = ser.readline()

def check_button_wait(incoming_message):
	now = datetime.datetime.now()
	while datetime.datetime.now() < (now + timedelta(minutes=1)):
		new_message = ser.readline()
		if new_message == "even":
			incoming_message = "even"
			print incoming_message
		if new_message == "odd":
			incoming_message = "odd"
			print incoming_message
	return incoming_message

while True:
	if incoming_message == "even":
		BIKESHARE_STATION_ID = 31221
		print "bikeshere 31221"
	elif incoming_message == "odd":
		BIKESHARE_STATION_ID = 31222
		print "bikeshare 31222"

	bs = bikeshare.BikeShareInterface(BIKESHARE_URL, BIKESHARE_STATION_ID)

	bs.refresh()
	data = bs.bike_availability
	docs = data[BIKESHARE_STATION_ID ]["docks"]
	bikes = data[BIKESHARE_STATION_ID ]["bikes"]

	if bikes == 0:
		ser.write("R")
		print "no bikes"
	elif bikes < docs:
		ser.write("Y")
		print "bikes < docs"
	else:
		ser.write("G")
		print "docs > bikes"

	print bikes

	incoming_message = check_button_wait(incoming_message) # be kind to the bikeshare servers!


