#ifndef PropRungeKutta_h
#define PropRungeKutta_h

#include <string>

#include "Propagator.h"
#include "Settings.h"

class PropRungeKutta: public Propagator{

    public:

        PropRungeKutta( const Settings* info, const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropRungeKutta           ( const PropRungeKutta& x ) = delete;
        PropRungeKutta& operator=( const PropRungeKutta& x ) = delete;

        ~PropRungeKutta() override;

    private:
        
        // function to run the propagator
        void   Execute() override;

};



#endif