#ifndef PropStatic_h
#define PropStatic_h

#include <string>

#include "Propagator.h"
#include "Settings.h"

class PropStatic: public Propagator{

    public:

        PropStatic( const Settings* info, const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropStatic           ( const PropStatic& x ) = delete;
        PropStatic& operator=( const PropStatic& x ) = delete;

        ~PropStatic() override;

    private:
        
        // function to run the propagator
        void   Execute() override;

};



#endif