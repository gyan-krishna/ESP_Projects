/*
 * L298 - interfacing
 * 
 * 
 */

#define FRONT 0
#define BACK  1
#define POINT_R 2
#define POINT_L 3
#define OFF   4

uint8_t mot_pins[] = {D1, D2, D3, D4, D5, D6};
uint16_t i;

void setup() 
{
    Serial.begin(9600);
    int d = 1000;
    config_pins();
    for(d = 0 ; d < 100 ; d+=10)
      move_tank(d, 0, 1000);
   
}
void loop() 
{
}
void config_pins()
{
  analogWrite(mot_pins[0], 180);
  analogWrite(mot_pins[5], 180);
  for(i = 1 ; i < 5 ; i++)
      pinMode(mot_pins[i], OUTPUT);
}
void move_tank(int speed, int dir, int duration)
{
    int l_speed, r_speed;
    l_speed = speed + dir;
    r_speed = speed - dir;

    l_speed = l_speed < 0 ? 0 : l_speed;
    r_speed = r_speed < 0 ? 0 : r_speed;
    l_speed = l_speed > 100 ? 100 : l_speed;
    r_speed = r_speed > 100 ? 100 : r_speed;   

    l_speed = map(l_speed, 0, 100, 130, 255);
    r_speed = map(r_speed, 0, 100, 130, 255);

    Serial.print(l_speed);
    Serial.print(" | ");
    Serial.println(r_speed);
    
    config_dir(FRONT);
    analogWrite(mot_pins[0], l_speed);
    analogWrite(mot_pins[5], r_speed);
    delay(duration);
    config_dir(OFF);
}
void config_dir(int mode)
{
    switch(mode)
    {
        case FRONT:
            digitalWrite(mot_pins[1], HIGH);
            digitalWrite(mot_pins[2], LOW);
            digitalWrite(mot_pins[3], HIGH);
            digitalWrite(mot_pins[4], LOW);
            break;
        case BACK:
            digitalWrite(mot_pins[1], LOW);
            digitalWrite(mot_pins[2], HIGH);
            digitalWrite(mot_pins[3], LOW);
            digitalWrite(mot_pins[4], HIGH);
            break;
        case POINT_L:
            digitalWrite(mot_pins[1], LOW);
            digitalWrite(mot_pins[2], HIGH);
            digitalWrite(mot_pins[3], HIGH);
            digitalWrite(mot_pins[4], LOW);
            break;
        case POINT_R:
            digitalWrite(mot_pins[1], HIGH);
            digitalWrite(mot_pins[2], LOW);
            digitalWrite(mot_pins[3], LOW);
            digitalWrite(mot_pins[4], HIGH);
            break;           
        case OFF:
            digitalWrite(mot_pins[1], LOW);
            digitalWrite(mot_pins[2], LOW);
            digitalWrite(mot_pins[3], LOW);
            digitalWrite(mot_pins[4], LOW);
            break;          
    }
}
