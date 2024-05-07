#ifndef PropVerlet_h
#define PropVerlet_h

#include <string>

#include "Propagator.h"
#include "Settings.h"

class PropVerlet: public Propagator{

    public:

        PropVerlet( const Settings* info, const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropVerlet           ( const PropVerlet& x ) = delete;
        PropVerlet& operator=( const PropVerlet& x ) = delete;

        ~PropVerlet() override;

    private:
        
        // function to run the propagator
        void   Execute() override;

};



#endif