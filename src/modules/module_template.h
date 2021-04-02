#ifndef MODULE_TEMPLATE_H
#define MODULE_TEMPLATE_H



#include "definitions.h"

#include "data_containers/vehicle_mode.h"

/**
 * This is a template that contains all the functions that all 
 * modules must have.
*/



class Module {
public:

    /**
     * This is where all calculations are done.
     *
     * @param values none.
     * @return none.
     */
    virtual void thread() = 0;

    /**
     * Module specific init function that sets the 
     * module up.
     * 
     * A pointer to the vehicles mode must be given in order to
     * allow the module to always know if a failsafe of error has
     * occured.
     *
     * @param values vehicleMode.
     * @return none.
     */
    virtual void init(VEHICLE_MODE* vehicleMode) {
        _vehicleMode = vehicleMode;
        init();
    };

    /**
     * Returns how fast the module should be ran at.
     *
     * @param values none.
     * @return uint32_t.
     */
    virtual uint32_t getLoopRate_Hz() {
        return loopRate_Hz;
    }


protected:

    virtual void init() = 0;

    static VEHICLE_MODE* _vehicleMode;

    uint32_t loopRate_Hz = 1000;


private:




};




#endif