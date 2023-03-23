# depends:
# numpy
# opencv-python

import numpy as np
from numpy.linalg import norm
import cv2
import time
import datetime
import csv
import os

FETCH_INTERVAL = 1
CAM_PORT = 0
FILE_NAME = "brightness_data.csv"
FIELD_NAMES = ["time", "brightness"]

def brightness(img):
    if len(img.shape) == 3:
        # Colored RGB or BGR (*Do Not* use HSV images with this function)
        # create brightness with euclidean norm
        return np.average(norm(img, axis=2)) / np.sqrt(3)
    else:
        # Grayscale
        return np.average(img)


cam = cv2.VideoCapture(CAM_PORT)
cam.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 360)

while True:
    time.sleep(FETCH_INTERVAL)
    result, image = cam.read()

    data = {"time": datetime.datetime.now(), "brightness": brightness(image)}

    file_exists = os.path.isfile(FILE_NAME)
    with open(FILE_NAME, 'a') as file:
        writer = csv.DictWriter(file, FIELD_NAMES, quoting=csv.QUOTE_ALL)

        if not file_exists:
            writer.writeheader()  # file doesn't exist yet, write a header

        writer.writerow(data)
        file.close()
