#include "Arduino.h"
#include "Wifi.h"
#include "SoftwareSerial.h"

SoftwareSerial *ESPSerial;


Wifi::Wifi() {
    ESPSerial = new SoftwareSerial(2,3);
    ESPSerial -> begin(9600);
    delay(2000);
}

//Basic commands

String Wifi::checkStartup() {
    ESPSerial -> flush();
    ESPSerial -> print("AT\r\n");
    ESPSerial -> setTimeout(5000);
    if (ESPSerial -> find("OK") == 1) {
        return "Startup Successful";
    }
    else {
        return "Startup Unsuccessful";
    }
}
    
String Wifi::restart() {
    ESPSerial -> print("AT+RST\r\n");
    ESPSerial -> setTimeout(5000);
    if (ESPSerial -> find("OK") == 1) { 
        return "Successfully Restarted";
    }
    else {
        return "Restart Unsuccessful";
    }
}

String Wifi::checkVersion() {
    ESPSerial -> print("AT+GMR\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if (output.indexOf("OK") > 0) {
        return output.substring(9,output.indexOf("OK"));
    }
    else {
        return "Version check Unsuccessful";
    }
}

//Wifi Commands

String Wifi::checkMode() {
    ESPSerial -> print("AT+CWMODE?\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    int temp = 0;
    if (output.indexOf("OK") > 0) {
        if (output.substring(21,22) == "E") {
            temp = 2;
        }
        else {
            temp = 0;
        }
        switch(output.substring(21+temp, 22+temp).toInt()) {
            case 1:
                return "Currently set to Station Mode";
            case 2:
                return "Currently set to AP Mode";
            case 3:
                return "Currently set to Dual Mode";
        }
    }
    else {
        return "Mode check was Unsuccessful";
    }
    
}

String Wifi::changeMode(int mode) {
    String temp = "AT+CWMODE=";
    temp += mode;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    if(ESPSerial -> find("OK") == 1) {
        return "Mode Change Successful";
    }
    else {
        return "Mode Change Unsuccessful";
    }
}

String Wifi::scanNetworks() {
    ESPSerial -> print("AT+CWLAP\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if (output.indexOf("OK") > 0) {
        String temp = "Enc, SSID, SS, MAC Address, Chn, Freq Off, Freq Cali, Pairwise Cipher\n";
        temp += output.substring(11,output.indexOf("OK"));
        temp.replace("+CWLAP:(0", "Open");
        temp.replace("+CWLAP:(1", "WEP");
        temp.replace("+CWLAP:(2", "WPA_PSK");
        temp.replace("+CWLAP:(3", "WPA2_PSK");
        temp.replace("+CWLAP:(4", "WPA_WPA2_PSK");
        temp.replace("+CWLAP:(5", "WPA2_Enterprise");
        temp.replace("\"", "");
        temp.replace(",", ", ");
        temp.replace("0)", "None");
        temp.replace("1)", "WEP40");
        temp.replace("2)", "WEP104");
        temp.replace("3)", "TKIP");
        temp.replace("4)", "CCMP");
        temp.replace("5)", "TKIP_CCMP");
        temp.replace("6)", "Unknown");
        return temp;
    }
}

String Wifi::connect(String ssid, String pass) {
    ESPSerial -> print("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("WIFI CONNECTED") > 0) {
        return "Connected Successfully";
    }
    else {
        return "Connection Unsuccessful";
    }
    
}

String Wifi::connectedNetwork() {
    ESPSerial -> print("AT+CWJAP?\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if (output.indexOf("OK") > 0) {
        String temp = "SSID, MAC, Chn, SS\n";
        temp += output.substring(19, output.indexOf("OK")-1);
        temp.replace("\"", "");
        return temp;
    }
    else {
        return "Unsuccessful connection query";
    }
}

String Wifi::disconnect() {
    ESPSerial -> print("AT+CWQAP\r\n");
    ESPSerial -> setTimeout(5000);
    if (ESPSerial -> find("WIFI DISCONNECT") == 1) {
        return "Disconnected Successfully";
    }
    else {
        return "Unsuccessful disconnect";
    }
}

String Wifi::setStaticIP(String ip, String gate, String mask) {
    ESPSerial -> print("AT+CIPSTA=\"" + ip + "\"\r\n");
    ESPSerial -> setTimeout(5000);
    if (ESPSerial -> find("OK") == 1) {
        return "IP Successfully Set";
    }
    else {
        return "IP was Unsuccessfuly Set";
    }
}

String Wifi::checkStaticIP() {
    ESPSerial -> print("AT+CIPSTA?\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if (output.indexOf("OK") > 0) {
        String temp = output.substring(12, output.indexOf("OK")-1);
        temp.replace("+CIPSTA:", "");
        temp.replace("\"", " ");
        return temp;
    }
    else {
        return "IP Check was Unsuccessful";
    }
}

String Wifi::checkAPConfig() {
    ESPSerial -> print("AT+CWSAP?\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0) {
        String temp = "SSID, PWD, Chn, Enc, Max Users, SSID status\n";
        temp += output.substring(14, output.indexOf("OK")-1);
        temp.replace("WSAP:", "");
        return temp;
    }
    else {
        return "AP Config Check Unsuccessful";
    }
}

String Wifi::setAPConfig(String ssid, String pass, int channel, int encryption) {
    String temp = "AT+CWSAP=\"";
    temp += ssid;
    temp += "\",\"";
    temp += pass;
    temp += "\",";
    temp += channel;
    temp += ",";
    temp += encryption;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    if(ESPSerial -> find("OK") == 1) {
        return "AP Configuration Successful";
    }
    else {
        return "AP Config Unsuccessful";
    }
}

String Wifi::connectedDevices() {
    ESPSerial -> print("AT+CWLIF\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0) {
        return output.substring(11, output.indexOf("OK"));
    }
    else {
        return "Connected device query Unsuccessful";
    }
}

//TCP/IP Commands

String Wifi::connectionStatus() {
    ESPSerial -> print("AT+CIPSTATUS\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0) {
        String temp = output.substring(15, output.indexOf("OK"));
        temp.replace("STATUS:2", "Connected to AP with IP");
        temp.replace("STATUS:3", "Created TCP or UDP transmission");
        temp.replace("STATUS:4", "Disconnected");
        temp.replace("STATUS:5", "Does not connect");
        return temp;
    }
}

String Wifi::startConnection(String type, String ip, int port) {
    String temp = "AT+CIPSTART=\"";
    temp += type;
    temp += "\",\"";
    temp += ip;
    temp += "\",";
    temp += port;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0 || output.indexOf("ALREADY CONNECTED") > 0) {
        return "Connection Successful";
    }
    else {
        return "Connection Unsuccessful";
    }
}

String Wifi::startConnection(String type, String ip, int port, int linkid) {
    String temp = "AT+CIPSTART=";
    temp += linkid;
    temp += ",\"";
    temp += type;
    temp += "\",\"";
    temp += ip;
    temp += "\",";
    temp += port;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    return ESPSerial -> readString();
    if(ESPSerial -> find("OK") == 1) {
        return "Connection Successful";
    }
    else {
        return "Connection Unsuccessful";
    }
}

String Wifi::send(String data) {
    String temp = "AT+CIPSEND=";
    temp += String(data.length());
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    if(ESPSerial -> find(">") == 1) {
        ESPSerial -> print(data);
        ESPSerial -> setTimeout(5000);
        if(ESPSerial -> find("SEND OK") == 1) {
            return "Data send succcessful";
        }
    }
    else {
        return "Data send unsuccessful";
    }

}

String Wifi::stopConnection() {
    ESPSerial -> print("AT+CIPCLOSE");
    ESPSerial -> setTimeout(5000);
    return ESPSerial -> readString();
}

String Wifi::getIP() {
    ESPSerial -> print("AT+CIFSR\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0) {
        String temp = output.substring(11, output.indexOf("OK")-1);
        temp.replace("+CIFSR:STA", "");
        return temp;
    }
    else {
        return "IP query Unsuccessful";
    }
}

String Wifi::setAutoConnect(int mode) {
    String temp = "AT+CWAUTOCONN=";
    temp += mode;
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") && mode == 0) {
        return "Auto Connect turned off successfully";
    }
    else if (output.indexOf("OK") && mode == 1) {
        return "Auto Connect turned on successfully";
    }
    else {
        return "Auto Connect change unsuccessful";
    }
    
}

String Wifi::checkMultiConnect() {
    ESPSerial -> print("AT+CIPMUX?\r\n");
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0 && output.indexOf("0") > 0) {
        return "Multiconnect is turned off";
    }
    if(output.indexOf("OK") > 0 && output.indexOf("1") > 0) {
        return "Multiconnect is turned on";
    }
    else {
        return "Multiconnect query unsuccessful";
    }
}

String Wifi::setMultiConnect(int mode) {
    String temp = "AT+CIPMUX=";
    temp += mode;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    if(ESPSerial -> find("OK") == 1) {
        return "Multiconnect mode changed successfully";
    }
    else {
        return "Multiconnect mode changed unsuccessfully";
    }
}

String Wifi::setServer(int mode) {
    String temp = "AT+CIPSERVER=";
    temp += mode;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    String output = ESPSerial -> readString();
    if(output.indexOf("OK") > 0 && mode == 0) {
        return "Server deleted successfully";
    }
    else if(output.indexOf("OK") > 0 && mode == 1) {
        return "Server created successfully";
    }
    else {
        return "Server mode changed unsuccessfully";
    }
}



String Wifi::setDHCP(int mode, int setting) {
    String temp = "AT+CWDHCP=";
    temp += mode;
    temp += ",";
    temp += setting;
    temp += "\r\n";
    ESPSerial -> print(temp);
    ESPSerial -> setTimeout(5000);
    if(ESPSerial -> find("OK") == 1) {
        return "DHCP set successfully";
    }
    else {
        return "DHCP set unsuccessfully";
    }
}

//Modifying this method causes a lot of errors?
void updateSoftware() {
    ESPSerial -> print("AT+CIUPDATE");
}