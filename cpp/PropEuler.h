#ifndef PropEuler_h
#define PropEuler_h

#include <string>

#include "PropSingle.h"
#include "Array.h"

class PropEuler: public PropSingle{

    public:

        PropEuler( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropEuler           ( const PropEuler& x ) = delete;
        PropEuler& operator=( const PropEuler& x ) = delete;

        ~PropEuler() override;

    protected:

        // single step propagation
        DoubleMatrix StepS( DoubleMatrix y0 ) const override;

};



#endif