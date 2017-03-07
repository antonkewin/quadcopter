#include "motor_receiver.h"
int value;
void setup() {
  // put your setup code here, to run once:
  motorinitialize();
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
   if(Serial.available()) 
    value = Serial.parseInt();
 if(value!=0)
 {
 Serial.println(value);

motor1.writeMicroseconds(value);
motor2.writeMicroseconds(value);
motor3.writeMicroseconds(value);
motor4.writeMicroseconds(value);}
}
