import time
import os

import KActivities

print("General Service, reporting for duty")

for activity in KActivities.ActivityManager.ListActivities():
    print(activity)

print("Registering the resource event - testapp - file:///home/ivan")

windowId = int(os.environ['WINDOWID'])

print("Shell window id is ${windowId}")

resource = KActivities.ResourceInstance(windowId, "testapp", "file:///home/ivan")

time.sleep(15)
