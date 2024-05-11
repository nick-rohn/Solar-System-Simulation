#include "PropVerlet.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "PropEuler.h"
#include "Settings.h"
#include "StarSystem.h"
#include "Array.h"


using namespace std;

// define builder and registration
class PropVerletFactory: public PropagatorFactory::AbsFactory{
    public:
        PropVerletFactory(): PropagatorFactory::AbsFactory( "verlet" ){}
        Propagator* create( const string& name ) override{
            return new PropVerlet( name );
        }
};
// create global Factory, so it's registered before main execution
static PropVerletFactory ver;



PropVerlet::PropVerlet( const string& name ):
    PropDouble( name ){
}

PropVerlet::~PropVerlet(){
}




// single step propagation
DoubleMatrix PropVerlet::Step( DoubleMatrix y0, const DoubleMatrix& y1 ) const {

    // force
    DoubleMatrix f = ss->GetF( y1 );

    // step
    y0 += (2 * timestep) * f;

    return y0;

}