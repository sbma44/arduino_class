import time
import serial
import bikeshare

BIKESHARE_URL = "http://www.capitalbikeshare.com/data/stations/bikeStations.xml"
BIKESHARE_TERMINAL_NAME = 31221 # change as desired!
SERIAL_DEVICE_ID = '/dev/tty.usbmodem1411' # change as necessary!
SERIAL_BAUD_RATE = 9600

bs = bikeshare.BikeShareInterface(BIKESHARE_URL, BIKESHARE_TERMINAL_NAME)
ser = serial.Serial(SERIAL_DEVICE_ID, SERIAL_BAUD_RATE)

while True:

	bs.refresh()
	print bs.bike_availability # this displays the variable with bike info

	# now make the Arduino do something!

	time.sleep(60) # be kind to the bikeshare servers!