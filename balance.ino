#include "motor_receiver.h"
#include "mpu6050.h"
#include <PID_v1.h>
double setpoint= 0;
double pitch_rate=0,roll_rate=0;
double error,rx_temp;
double kp=5.16,ki=0,kd=0.72;
int m1,m2,m3,m4;
PID pitch_pid(&compAngleY, &pitch_rate, &setpoint,kp,ki,kd, DIRECT);
PID roll_pid(&compAngleX, &roll_rate,&setpoint,kp,ki,kd,DIRECT);

void setup() {
  // put your setup code here, to run once:
motorinitialize();
rcinitialize();
mpu6050_initialize();     //PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
pitch_pid.SetOutputLimits(-1000,1000);
pitch_pid.SetSampleTime(1);
pitch_pid.SetMode(AUTOMATIC);

roll_pid.SetOutputLimits(-1000,1000);
roll_pid.SetSampleTime(1);
roll_pid.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:
 update_angles();
 pitch_pid.Compute();
 roll_pid.Compute();
 rcmap();
 //Serial.println(rx_roll);

///Serial.print(rx_yaw); Serial.print("      ");
 rx_temp=rx_yaw;
 ki=(rx_temp-1000)/100;
 if(ki<0)
 ki=0;

 rx_temp=rx_pitch;
 kd=(rx_temp-1000)/100;
 if(kd<0)
 kd=0;
 //Serial.print(ki); Serial.print("     "); Serial.println(kd);
 pitch_pid.SetTunings(ki,kd,0);
 
 
if(throttle>1020)
  {
m2= throttle+roll_rate;
  m4= throttle-roll_rate;
   m1= throttle+pitch_rate;
  m3= throttle-pitch_rate;
 if(m2<1000)
 m2=1000;
 else if(m2>2000)
 m2=2000;
 if(m4<1000)
 m4=1000;
 else if(m4>2000)
 m4=2000;
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
 motor2.writeMicroseconds(m2);
 motor4.writeMicroseconds(m4);
// Serial.print("Motor2="); Serial.print(m2); Serial.print("     "); Serial.print("Motor4="); Serial.println(m4); 
  }
 else
 {
  motor1.writeMicroseconds(1000);
 motor2.writeMicroseconds(1000);
 motor3.writeMicroseconds(1000);
 motor4.writeMicroseconds(1000);
 }
  
 
 
 
//Serial.print("motor 1="); Serial.print(m1); Serial.print("      ");  Serial.print("motor 3="); Serial.println(m3);
 //Serial.print("Gyro = "); Serial.println(gyroXrate);
 //Serial.print("Throttle = ");   Serial.print(pitch_rate);
 //Serial.print("  "); Serial.print(m1); Serial.print("  "); Serial.print(m3);
 //Serial.print("         " ); 
//Serial.print("Angle = "); Serial.println(compAngleY); 
//counter++;
//if(counter>100)
//{
 // temp1=millis();
//Serial.println(temp-temp1);
//counter=0;
//temp=temp1;
//}
/*if(Serial.available()>1) 
   {
    temp = Serial.parseInt();
    
    if(temp!=0)
    {  
    kp=temp;
    pitch_pid.SetTunings(kp, 0,0);
    //Serial.print(temp); Serial.print(" "); Serial.println(kp);
    }
    }*/
                              
}
