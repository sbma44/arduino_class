import time
import serial
import bikeshare

BIKESHARE_URL = "http://www.capitalbikeshare.com/data/stations/bikeStations.xml"
BIKESHARE_STATION_ID = 31221

bs = bikeshare.BikeShareInterface(BIKESHARE_URL, BIKESHARE_STATION_ID)

while True:

	bs.refresh()
	print bs.bike_availability

	# now make the Arduino do something!

	time.sleep(60) # be kind to the bikeshare servers!