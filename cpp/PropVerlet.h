#ifndef PropVerlet_h
#define PropVerlet_h

#include <string>

#include "PropDouble.h"
#include "Array.h"

class PropVerlet: public PropDouble{

    public:

        PropVerlet( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropVerlet           ( const PropVerlet& x ) = delete;
        PropVerlet& operator=( const PropVerlet& x ) = delete;

        ~PropVerlet() override;

    private:
    
        // single step propagation
        DoubleMatrix Step( DoubleMatrix y0, const DoubleMatrix& y1 ) const override;
        

};



#endif