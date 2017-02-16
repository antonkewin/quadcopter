#include<Servo.h>


int value=0,temp;  

Servo firstesc, secondesc, thirdesc, fourthesc; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  firstesc.attach(3);
  secondesc.attach(5);
  thirdesc.attach(6);
  fourthesc.attach(9);//  attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud

}

void loop() {


//  firstesc.writeMicroseconds(value);
  secondesc.writeMicroseconds(value);
  //thirdesc.writeMicroseconds(value);
  //fourthesc.writeMicroseconds(value);

  if(Serial.available()) 
   {
    temp = Serial.parseInt();
    if(temp!=0)
    value=temp;
     Serial.println(value);                         
   }

}













































