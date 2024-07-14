#include <Wire.h>
#include "MPU6050.h" // Make sure this library is installed
MPU6050 mpu6050; // Declare MPU6050 object

// Global variables for motor speed control and target angle
const int pinSDA = 13;
const int pinSDC = 14;


void setup() {
  Serial.begin(9600);
  Wire.begin(pinSDA, pinSDC); // Initialize communication with MPU6050 using pins 47 (SDA) and 48 (SCL)
  mpu6050.initialize(); // Initialize the MPU6050
  if (!mpu6050.testConnection()) {
    Serial.println("MPU6050 connection failed. Please check your connection.");
    while (1); // Halt if connection failed
  }

  Serial.println("Setup complete. Beginning loop...");
}
void loop() {
  // Read raw accelerometer and gyroscope values
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // Convert accelerometer values to angles
  // Note: This is a simplified calculation and might need adjustments
  float angleX = atan2(ay, sqrt(ax*ax + az*az)) * 180 / PI;
  float angleY = atan2(ax, sqrt(ay*ay + az*az)) * 180 / PI;
  float angleZ = atan2(az, sqrt(ax*ax + ay*ay)) * 180 / PI;
  
  //float angleX = atan2(ay, az ) * 180 / PI;
  //float angleY = atan2(ax, az) * 180 / PI;
  //float angleZ = atan2(ay, ax) * 180 / PI;
  
  

  // Log data for debugging
  Serial.printf("X: %f, Y: %f, Z: %f \n",angleX, angleY, angleZ);
  delay(100); // Delay for readability of serial output
}

