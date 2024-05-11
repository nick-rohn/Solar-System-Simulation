#ifndef PropSingle_h
#define PropSingle_h

#include <string>

#include "Propagator.h"
#include "Array.h"

class PropSingle: public Propagator{

    public:

        PropSingle( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropSingle           ( const PropSingle& x ) = delete;
        PropSingle& operator=( const PropSingle& x ) = delete;

        ~PropSingle() override;

    private:

        // single step propagation
        virtual DoubleMatrix StepS( DoubleMatrix y0 ) const = 0;
        
        // function to run the propagator
        virtual void Execute() override;

};



#endif