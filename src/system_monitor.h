#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H



#include "definitions.h"

#include "modules/sensor_modules/mpu9250_driver.h"
#include "modules/sensor_modules/bme280_driver.h"
#include "sensors/gps.h"

#include "outputs/rgb_led.h"

#include "kraft_kontrol_runner.h"

#include "interval_control.h"



void systemMonitor() {

    static IntervalControl intervalControl(10);

    if (!intervalControl.isTimeToRun()) return; //Only run every 100ms (10Hz)
    

    Vehicle* vehicle = KraftKontrolRunner::kraft;

    KinematicData vehicleKinetics;
    KinematicData vehicleSetpoints;

    if (vehicle != nullptr) vehicleKinetics = vehicle->getNavigationData();
    if (vehicle != nullptr) vehicleSetpoints = vehicle->getGuidanceData();

    static Vector Gyro;
    static uint32_t timestamp = 0;

    //vehicleKinetics.angularRate = vehicleKinetics.attitude.copy().conjugate().rotateVector(vehicleKinetics.angularRate);
    //vehicleKinetics.linearAcceleration = vehicleKinetics.attitude.copy().conjugate().rotateVector(vehicleKinetics.linearAcceleration);
    
    //if (IMU::gyroAvailable()) IMU::getGyro(&Gyro, &timestamp);

    //Serial.println();
    //Serial.println("LoopRate: " + String(IMU.loopRate()) + ", GyroRate: " + String(IMU.gyroRate()) + ", AccelRate: " + String(IMU.accelRate()) + ", MagRate: " + String(IMU.magRate()));
    //Serial.println("vehicle linear accel: x: " + String(vehicleKinetics.linearAcceleration.x) + ", y: " + String(vehicleKinetics.linearAcceleration.y) + ", z: " + String(vehicleKinetics.linearAcceleration.z));
    //Serial.println("vehicle position: x: " + String(vehicleKinetics.position.x) + ", y: " + String(vehicleKinetics.position.y) + ", z: " + String(vehicleKinetics.position.z) + ", IMU: " + IMU.gyroRate());
    Serial.println("vehicle velocity: x: " + String(vehicleKinetics.velocity.x) + ", y: " + String(vehicleKinetics.velocity.y) + ", z: " + String(vehicleKinetics.velocity.z) + ", IMU: Gyro: " + IMU.gyroRate() + ", Accel: " + IMU.accelRate());
    //Serial.println("vehicle attitude: w: " + String(vehicleKinetics.attitude.w) + ", x: " + String(vehicleKinetics.attitude.x) + ", y: " + String(vehicleKinetics.attitude.y) + ", z: " + String(vehicleKinetics.attitude.z));
    //Serial.println("vehicle angularRate: x: " + String(vehicleKinetics.angularRate.x) + ", y: " + String(vehicleKinetics.angularRate.y) + ", z: " + String(vehicleKinetics.angularRate.z));
    //Serial.println("vehicle angularRate setpoint: x: " + String(vehicleSetpoints.angularRate.x) + ", y: " + String(vehicleSetpoints.angularRate.y) + ", z: " + String(vehicleSetpoints.angularRate.z));
    //Serial.println("vehicle attitude setpoint: w: " + String(vehicleSetpoints.attitude.w) + ", x: " + String(vehicleSetpoints.attitude.x) + ", y: " + String(vehicleSetpoints.attitude.y) + ", z: " + String(vehicleSetpoints.attitude.z));
    //Serial.println("IMU Rate: " + String(IMU::getGyroRate()));
    //Serial.println(String("IMU angRate x: ") + Gyro.x + ", y: " + Gyro.y + ", z: " + Gyro.z);
    //Serial.println("vehicle accel: x: " + String(vehicle.getAcceleration().x) + ", y: " + String(vehicle.getAcceleration().y) + ", z: " + String(vehicle.getAcceleration().z));
    //Serial.println("vehicle speed: x: " + String(vehicle.getVelocity().x) + ", y: " + String(vehicle.getVelocity().y) + ", z: " + String(vehicle.getVelocity().z));
    //Serial.println("vehicle pos: x: " + String(vehicle.getPosition().x) + ", y: " + String(vehicle.getPosition().y) + ", z: " + String(vehicle.getPosition().z));
    
    //Serial.println(String("rate: ") + Baro.loopRate());
}



#endif