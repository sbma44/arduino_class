import xml.etree.ElementTree as ET
import requests

class BikeShareInterface(object):
    """Convenience class for identifying bikeshare availability"""
    def __init__(self, xml_url, station_ids):
        super(BikeShareInterface, self).__init__()
        
        self.xml_url = xml_url
        if not type(station_ids) in (list, tuple):
            station_ids = [station_ids]
        self.station_ids = station_ids

        self.last_updated = None
        self.bike_availability = dict.fromkeys(self.station_ids)
        for station_id in self.bike_availability:
            self.bike_availability[station_id] = {}
        
    def refresh(self):
        """Updates bikeshare availability from XML feed"""
        req = requests.get(self.xml_url)
        root = ET.fromstring(req.content)
        
        self.last_updated = root.get('lastUpdate')
        for station in root.iter('station'):
            station_id = int(station.find('terminalName').text)
            if station_id in self.station_ids:
                self.bike_availability[station_id]['bikes'] = int(station.find('nbBikes').text)
                self.bike_availability[station_id]['docks'] = int(station.find('nbEmptyDocks').text)
