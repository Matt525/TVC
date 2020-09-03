#include "Wire.h"       // allows communication to i2c devices connected to arduino
#include "I2Cdev.h"     // I2Connection library
#include "MPU6050.h"    // IMU library
#include "Servo.h"      // servo control library
 
MPU6050 mpu; //defines the chip as a MPU so I can call it later
 
int16_t ax, ay, az;  // x y z orientation values from accelerometer. Only used during flight. 
int16_t gx, gy, gz;  // x y z orientation values from gyrscope.
/////////////////////////////////////////////////////////////////////////////////////// 
Servo outer; 
Servo inner;
///////////////////////////////////////////////////////////////////////////////////////
//// Defining variables for outer and inner
int valo;     // outer val
int prevValo; // outer prev val
///////////////////////////////////////////////////////////////////////////////////////
int vali;  //inner val
int prevVali; //outer prev val
/////////////////////////////////////////////////////////////////////////////////////// 
//initializes the IMU
void setup() 
{
    Wire.begin(); 
    Serial.begin(38400); 
 
    Serial.println("MPU initialized"); 
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
    outer.attach(9); //servo on pin 9 for  y
    inner.attach(10);//servo on pin 10 for  x
}



/////////////////////////////////////////////////////////////////////////////////////// 
void loop() 
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
 
    valo = map(ax, -17000, 17000, 179, 0);
    if (valo != prevValo)
    {
        outer.write(valo); 
        prevValo = valo; 
    }
    
     vali = map(ay, -17000, 17000, 179, 0);
    if (vali != prevVali)
    {
        inner.write(vali); 
        prevVali = vali; 
    }
}
///////////////////////////////////////////////////////////////////////////////////////

