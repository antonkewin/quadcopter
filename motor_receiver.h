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

#define throttle_min 1180
#define throttle_max 1850
#define roll_min 1110
#define roll_max 1900
#define pitch_min 1110
#define pitch_max 1780
#define yaw_min 1100
#define yaw_max 1900

#define mid_value 1500

#define motor_max 2000
#define motor_min 700
void motorinitialize();
void rcmap();
void rcinitialize();
void rollinput();
void throttleinput();
void pitchinput();
void yawinput();

Servo motor1, motor2, motor3, motor4;
/*

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
int throttle,yaw,pitch,roll;
 
void motorinitialize()
{
  motor1.attach(motor1_pin);
  motor2.attach(motor2_pin);
  motor3.attach(motor3_pin);
  motor4.attach(motor4_pin);//  attached to pin 9 I just do this with 1 Servo

  //attachInterrupt(digitalPinToInterrupt(pin), ISR, mode); 
}
void rcmap()
{
 // value = map(nThrottleIn, 1200, 1850, 700, 2000);
 throttle=map(rx_throttle,throttle_min,throttle_max,700,2000);
 pitch=map(rx_pitch,mid_value,pitch_max,700,2000);
 roll=map(rx_roll,mid_value,roll_max,700,2000);
 yaw=map(rx_yaw,mid_value,yaw_max,700,2000);
 
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
