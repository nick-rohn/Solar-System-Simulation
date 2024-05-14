#include "PropEuler.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "Array.h"
#include "StarSystem.h"


using namespace std;

// define builder and registration
class PropEulerFactory: public PropagatorFactory::AbsFactory{
    public:
        PropEulerFactory(): PropagatorFactory::AbsFactory( "euler" ){}
        Propagator* create( const string& name ) override{
            return new PropEuler( name );
        }
};
// create global Factory, so it's registered before main execution
static PropEulerFactory eu;



PropEuler::PropEuler( const string& name ):
    PropSingle( name ){
}

PropEuler::~PropEuler(){
}



// single step propagation
DoubleMatrix PropEuler::StepS( DoubleMatrix y0 ) const {

    // force
    DoubleMatrix f = ss->GetF( y0 );

    // step
    y0 += f * cf.timestep;

    return y0;

}