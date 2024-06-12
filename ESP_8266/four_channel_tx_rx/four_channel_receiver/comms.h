#ifndef COMMS_H
#define COMMS_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#define DEVICE_ID "DEV_ID_0"
#define NCHANNELS 4

WiFiServer server(80);
WiFiClient client;

String request;
bool isReqCame = false;
int data[NCHANNELS] = {0,0,0,0};
String path = "nothing";

void connect_wifi(String ssid, String pass);
bool CheckNewReq();
void waitUntilNewReq();
void extract_data(String str);
void display_data();
String getPath();

//connect to wifi
void connect_wifi(String ssid, String pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(),pass.c_str());
    Serial.println("");
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    if (!MDNS.begin("esp8266")) 
    {
        Serial.println("Error setting up MDNS responder!");
        while (1) 
          delay(1000);
    }
    Serial.println("mDNS responder started");
    server.begin();
    Serial.println("TCP server started");
    MDNS.addService("http", "tcp", 80);
}

//check if new request has been sent
bool CheckNewReq()
{
    client = server.available();
    if (!client)
      return 0;
    /*
    while (client.connected() && !client.available()) {
      delay(1);
    }*/           //to make data transfer fast
    
    String req = client.readStringUntil('\r');
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    
    if (addr_start == -1 || addr_end == -1) 
    {
        Serial.print("Invalid request: ");
        Serial.println(req);
        return 0;
    }
    req = req.substring(addr_start + 1, addr_end);
  
    request = req; 
    isReqCame = true;
    
    client.flush();
    return 1;
}

//wait till a request is received
void waitUntilNewReq()
{
    do 
    {
        CheckNewReq();
    }while(!isReqCame);
    isReqCame = false;
}

//extract data from request
void extract_data(String str)
{
    int dat, st = 1, ptr = 0;
    for(int i = 0 ; i < path.length(); i++)
    {
        if(path.charAt(i) == '_')
        {
            dat = path.substring(st,i).toInt();
            if(ptr < NCHANNELS)
                data[ptr++] = dat;
            st = i+1;
        }
    }
    //Serial.print(ptr);
    if(ptr == NCHANNELS)
        client.print("received");
    else
        client.print("error");
}
void display_data()
{
    int i;
    for(i = 0 ; i < NCHANNELS; i++)
    {
        Serial.print(data[i]);
        Serial.print(" ");
    }
    Serial.println();
}
String getPath()
{
  return request;
}
#endif
