#ifndef PropDouble_h
#define PropDouble_h

#include <string>

#include "PropEuler.h"
#include "Array.h"

class PropDouble: public PropEuler{

    public:

        PropDouble( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropDouble           ( const PropDouble& x ) = delete;
        PropDouble& operator=( const PropDouble& x ) = delete;

        ~PropDouble() override;

    private:
    
        // single step propagation
        virtual DoubleMatrix Step( DoubleMatrix y0, const DoubleMatrix& y1 ) const = 0;
        
        // function to run the propagator
        void Execute() override;

};



#endif