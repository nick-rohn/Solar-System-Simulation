#ifndef PropRungeKutta_h
#define PropRungeKutta_h

#include <string>

#include "PropSingle.h"
#include "Settings.h"
#include "Array.h"

class PropRungeKutta: public PropSingle{

    public:

        PropRungeKutta( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropRungeKutta           ( const PropRungeKutta& x ) = delete;
        PropRungeKutta& operator=( const PropRungeKutta& x ) = delete;

        ~PropRungeKutta() override;

    protected:
    
        // single step propagation
        DoubleMatrix StepS( DoubleMatrix y0 ) const override;
        
};



#endif