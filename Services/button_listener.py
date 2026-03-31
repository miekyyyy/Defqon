#!/usr/bin/env python3

from gpiozero import Button
from signal import pause
import subprocess

BUTTON_PIN = 27
COMMAND = ["/bin/bash", "/home/stage/defqon_ws/Defqon/MusicStart.sh"]

button = Button(BUTTON_PIN, pull_up=True, bounce_time=0.2)

def on_press():
    subprocess.Popen(COMMAND)

button.when_pressed = on_press

pause()
