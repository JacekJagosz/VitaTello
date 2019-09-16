Any advice is extremely appreciated!

VitaTello
=================
 
 What does this do?
===================
 
  This is meant to become a remote control app for PS Vita.
  It currently can fly Tello using analog sticks, takeoff(X), land(O) and turn off the engines in case of emergency (△).
  You can also change speed to 5m/s (SELECT - default) and 10m/s (START).
  UDP communication is based on psxdev's [debugnet](https://github.com/psxdev/debugnet).
  
## TO DO:
### High priority:
  - add sport (high speed) mode
  - replace arbitrary delays when sending commands with something better
  - create (or hopefully find a suitable library) a UDP server on Vita
  - receive telemetry from Tello, most importantly battery and WiFi signal
  - figure out a way to display video stream (FFMPEG and SDL?)
  - save photos and videos
### Low prioroty:
  - strip down current library and understand it better
  - add pictures for LiveArea
  - add a config file or settings so you can change e.g. deadzone without recompiling
  - add Mode 1 controll scheme
  
  More to come! (hopefully)
