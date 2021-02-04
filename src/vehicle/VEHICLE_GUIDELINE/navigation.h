#ifndef NAVIGATION_H
#define NAVIGATION_H



/**
 * This is where the vehicle sensor measurements (sensorfusion) is done. This takes
 * the sensor measurements and calculates all inertial parameters of the vehicle.
 * This allows the navigation to be written in a general way for the simulator.
 * Because this class will be augmented by the simulator, this structure also allows for very
 * easy testing of the vehicle code in the simulator in a very "drag and drop" type way.
*/



#include "Arduino.h"

#include "sensors/imu.h"

#include "utils/interval_control.h"
#include "utils/high_pass_filter.h"
#include "utils/low_pass_filter.h"

#include "vehicle/inertial_data.h"


#define LOOP_RATE_LIMIT 2000


class Navigation {
public:

    void resetInertialTEST() {_inertialData.position = Vector(0,0,0); _inertialData.velocity = Vector(0,0,0);}; //To be removed or replaced. This is only for testing Inertial navigation

    Quaternion getAttitude() {return _inertialData.attitude;}
    Vector getAngularRate() {return _inertialData.angularRate;}

    Vector getPosition() {return _inertialData.position;}
    Vector getVelocity() {return _inertialData.velocity;}
    Vector getAcceleration() {return _inertialData.acceleration;}
    Vector getLinearAcceleration() {return _inertialData.linearAcceleration;}

    InertialData getInertialData () {return _inertialData;}


protected:

    void sensorFusionThread();


private:

    //System inertial information
    InertialData _inertialData;

    //Filter data
    //HighPassFilter<Vector> gyroHPF = HighPassFilter<Vector>(0.01);

    uint32_t lastGyroTimestamp = 0;
    uint32_t lastAccelTimestamp = 0;
    uint32_t lastMagTimestamp = 0;

    //System information flagges
    bool _angularRateValid = false;
    bool _attitudeValid = false;
    bool _headingValid = false;

    bool _accelerationValid = false;
    bool _velocityValid = false;
    bool _positionValid = false;

    bool _highPrecisionValid = false;

    bool gyroInitialized = false;
    bool accelInitialized = false;
    bool magInitialized = false;

    //Loop interval control
    IntervalControl interval = IntervalControl(LOOP_RATE_LIMIT);


};




#endif