# sudo chroot a+rw /dev/ttyUSB0

# depends:
# pyserial

import serial, time
import datetime
import csv
from csv import DictWriter
import json
import os

FETCH_INTERVAL = 1

ser = serial.Serial('/dev/ttyUSB0', 9600)

print(ser.name)

FIELD_NAMES = ['time', 'voltage', 'current', 'power', 'energy', 'frequency', 'pf']

FILE_NAME = "serial_data.csv"

while True:
    time.sleep(FETCH_INTERVAL)

    while ser.in_waiting > 0:
        i = ser.readline()
        json_data = i.decode('utf-8')

        print(json_data)

        data = json.loads(json_data)
        data['time'] = datetime.datetime.now()

        file_exists = os.path.isfile(FILE_NAME)

        with open(FILE_NAME, 'a') as file:
            writer = DictWriter(file, FIELD_NAMES, quoting=csv.QUOTE_ALL)

            if not file_exists:
                writer.writeheader()  # file doesn't exist yet, write a header

            writer.writerow(data)
            file.close()
