#include "comms.h"
#include "pins.h"
#include <Servo.h>

bool activated = false;
Servo ch1,ch2,ch3,ch4;

void setup()
{
  
  Serial.begin(9600);
  pinMode(ACTIVATE_LED, OUTPUT);
  initServo();
  connect_wifi("PHENIX","03323359065");
  digitalWrite(ACTIVATE_LED, HIGH);
}
void loop()
{
    //waitUntilNewReq();  //Waits until a new request from python come
    if(CheckNewReq() == 1)
    {
        //Serial.println("new request arrived");
        if (getPath()=="/test")
            client.print(DEVICE_ID);
        else if(getPath() == "/activate")
        {
            digitalWrite(ACTIVATE_LED, LOW);
            client.print("activated");
            activated = true;
        }
        else if(getPath() == "/deactivate")
        {
            digitalWrite(ACTIVATE_LED, HIGH);
            client.print("deactivated");
            activated = false;
        }
        else if(getPath()=="/favicon.ico")   //this happens for browsers only.
            client.print("garbage");
        else
        {
            path = getPath();
            //Serial.println(path);   //String
            extract_data(path);
            display_data();
            if(activated)
                updateServos();
        } 
    } 
}
void initServo()
{
    ch1.attach(CH1_PIN);
    ch2.attach(CH2_PIN);
    ch3.attach(CH3_PIN);
    ch4.attach(CH4_PIN);
}
void updateServos()
{
    ch1.write(data[0]);
    ch2.write(data[1]);
    ch3.write(data[2]);
    ch4.write(data[3]);
}
