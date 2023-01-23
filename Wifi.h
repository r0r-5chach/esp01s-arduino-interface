#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class Wifi {

public:
    Wifi();
    String checkStartup();
    String restart();
    String checkVersion();
    String checkMode();
    String changeMode(int mode);
    String scanNetworks();
    String connect(String ssid, String pass);
    String connectedNetwork();
    String disconnect();
    String setStaticIP(String ip, String gate, String mask);
    String checkStaticIP();
    String checkAPConfig();
    String setAPConfig(String ssid, String pass, int channel, int encryption);
    String connectedDevices();
    String connectionStatus();
    String startConnection(String type, String ip, int port);
    String startConnection(String type, String ip, int port, int linkid);
    String send(String data);
    String stopConnection();
    String getIP();
    String setAutoConnect(int mode);
    String checkMultiConnect();
    String setMultiConnect(int mode);
    String setServer(int mode);
    String setDHCP(int mode, int setting);

private:
    SoftwareSerial *ESPSerial;
};
#endif