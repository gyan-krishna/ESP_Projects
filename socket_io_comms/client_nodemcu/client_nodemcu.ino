#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>

SocketIOclient socketIO;

void setup() 
{
  WiFi.begin("PHENIX", "03323389065");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // server address, port and URL
  socketIO.begin("192.168.0.101", 3005, "/socket.io/?transport=websocket");
  // event handler for the event message
  socketIO.on("reply",messageEventHandler);
}

uint64_t messageTimestamp;
void loop() 
{
    socketIO.loop();  
    uint64_t now = millis();
    if(now - messageTimestamp > 6000) 
    {
        messageTimestamp = now;
        socketIO.emit("message", "\"this is a message from the client\"");   
    }
}

void messageEventHandler(const char * payload, size_t length) 
{
    Serial.printf("got message: %s\n", payload);
}
