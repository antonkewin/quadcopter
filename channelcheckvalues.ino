#include<Servo.h>

#define motor1_pin 8
#define motor2_pin 9
#define motor3_pin 10
#define motor4_pin 11

//Receiver Pins
#define rx_roll_pin 2
#define rx_pitch_pin 3
#define rx_throttle_pin 18
#define rx_yaw_pin 19

Servo motor1, motor2, motor3, motor4;
int value;
/*
Channel1:Roll:
max:1900
min:1110
Mid Value:1500

Channel2:
max:1780
min:1110
Mid Value:1440

Channel3:
max:1850
min:1180

Channel4:
1900
1100
Mid Value:1490


INPUT:
rx_throttle,rx_pitch,rx_yaw,rx_roll
channel3,channel2,channel4,channel1

channel1=>rx_roll    =>2
channel2=>rx_pitch   =>3
channel3=>rx_throttle=>18
channel4=>rx_yaw     =>19

motor1 =>8
motor2 =>9
motor3 =>10
motor4 =>11

pwm output to motors: from 700us to 2000us
*/
volatile int rx_roll,rx_pitch,rx_throttle,rx_yaw; // volatile, we set this in the Interrupt and read it in loop so it must be declared volatile
volatile unsigned long roll_start,pitch_start,yaw_start,throttle_start; // set in the interrupt
void setup()
{
  rcinitialize();
  Serial.begin(9600);
 
  /*
  motor1.attach(motor1_pin);
  motor2.attach(motor2_pin);
  motor3.attach(motor3_pin);
  motor4.attach(motor4_pin);//  attached to pin 9 I just do this with 1 Servo*/

  //attachInterrupt(digitalPinToInterrupt(pin), ISR, mode); 
 
}
void loop()
{
 // value = map(nThrottleIn, 1200, 1850, 700, 2000);
 Serial.print(rx_roll); Serial.print("        ");
 Serial.print(rx_pitch); Serial.print("        ");
 Serial.print(rx_throttle); Serial.print("        ");
 Serial.println(rx_yaw); Serial.print("        ");
  /*motor1.writeMicroseconds(value);
  motor2.writeMicroseconds(value);
  motor3.writeMicroseconds(value);
  motor4.writeMicroseconds(value);*/
}


void rcinitialize()
{
  attachInterrupt(digitalPinToInterrupt(rx_roll_pin),rollinput,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rx_throttle_pin),throttleinput,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rx_yaw_pin),yawinput,CHANGE);
  attachInterrupt(digitalPinToInterrupt(rx_pitch_pin),pitchinput,CHANGE);
}
void rollinput()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(rx_roll_pin) == HIGH)
    roll_start = micros();
  else
    if(roll_start)
    {
      rx_roll = (int)(micros() - roll_start);
      roll_start = 0;
    }
}
void throttleinput()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(rx_throttle_pin) == HIGH)
    throttle_start = micros();
  else
    if(throttle_start)
    {
      rx_throttle = (int)(micros() - throttle_start);
      throttle_start = 0;
    }
}
void pitchinput()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(rx_pitch_pin) == HIGH)
    pitch_start = micros();
  else
    if(pitch_start)
    {
      rx_pitch = (int)(micros() - pitch_start);
      pitch_start = 0;
    }
}
void yawinput()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(rx_yaw_pin) == HIGH)
    yaw_start = micros();
  else
    if(yaw_start)
    {
      rx_yaw = (int)(micros() - yaw_start);
      yaw_start = 0;
    }
}


