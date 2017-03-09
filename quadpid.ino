#include "motor_receiver.h"
#include "mpu6050.h"
#include <PID_v1.h>
double setpoint= 0;
double pitch_rate=0;
double error;
double kp=10;
int m1,m3;
PID pitch_pid(&compAngleX, &pitch_rate, &setpoint,kp,0,0, DIRECT);

void setup() {
  // put your setup code here, to run once:
motorinitialize();
rcinitialize();
mpu6050_initialize();     //PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
pitch_pid.SetOutputLimits(-1000,1000);
pitch_pid.SetSampleTime(1);

  //turn the PID on
pitch_pid.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:
 update_angles();
 pitch_pid.Compute();
 rcmap();
 /*motor1.writeMicroseconds(throttle-pitch_rate);
 motor3.writeMicroseconds(throttle+pitch_rate);*/

if(throttle>1020)
  {
  m1= throttle-pitch_rate;
  m3= throttle+pitch_rate;
 if(m1<1000)
 m1=1000;
 else if(m1>2000)
 m1=2000;
 if(m3<1000)
 m3=1000;
 else if(m3>2000)
 m3=2000;
 motor1.writeMicroseconds(m1);
 motor3.writeMicroseconds(m3);
  }
 else
 {
 motor1.writeMicroseconds(1000);
 motor3.writeMicroseconds(1000);
 }
 //Serial.print("Throttle = ");   Serial.print(pitch_rate);
 //Serial.print("  "); Serial.print(m1); Serial.print("  "); Serial.print(m3);
 //Serial.print("         " ); 
// Serial.print("Angle = "); Serial.println(abs(compAngleX)); 
}
