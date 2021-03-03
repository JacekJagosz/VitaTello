Any advice is extremely appreciated!

VitaTello
=================
![Logo](https://user-images.githubusercontent.com/28653965/109829663-08a85c00-7c3e-11eb-8789-47c1145680da.png)
 
 What does this do?
===================
 
  This is meant to become a remote control app for PS Vita.
  It currently can fly Tello using analog sticks, takeoff(X), land(O) and turn off the engines in case of emergency (△).
  You can also change speed to 5m/s (SELECT) and 10m/s (START - default).
  UDP communication is based on psxdev's [debugnet](https://github.com/psxdev/debugnet).
  
## TO DO:
### High priority:
  - [ ] add debugScreen to help further development
  - [ ] receive telemetry from Tello, most importantly battery and WiFi signal
     - [ ] strip down current library and understand it better
     - [ ] create another app to experiment with UDP - [Vita UDP Playground](https://github.com/JacekJagosz/VitaUDPPlayground)
     - [ ] create (or hopefully find a suitable library) a UDP server on Vita - ~~transfer to [ENet](https://github.com/cgutman/enet/tree/master)~~ - turns out Enet uses custom protocol
  - [ ] figure out a way to display video stream (FFMPEG and SDL?)
  - [ ] add sport (high speed) mode - transfer to [Low-Level protocol](https://tellopilots.com/wiki/protocol/)
  - [ ] replace arbitrary delays when sending commands with something better
  - [ ] save photos and videos
### Low prioroty:
  - [x] ~~add pictures for LiveArea~~
  - [ ] add a config file or settings so you can change e.g. deadzone without recompiling
  - [ ] add Mode 1 controll scheme
  
  More to come! (hopefully)
