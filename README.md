I have included some test code so you can see if you have setup the Arduino and transceiver correctly.

1)Connect the ESP-01S to the Arduino (pin out can be found online)
2)Go into test.ino and change the placeholder wifi name and password with same network details your laptop or PC is connected to.
2)Flash Arduino with test.ino
3)Run server.py on laptop or PC
4)Startup Arduino and wait to see if you receive message in python program output