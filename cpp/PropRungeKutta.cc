#include "PropRungeKutta.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "PropSingle.h"
#include "StarSystem.h"
#include "Array.h"


using namespace std;

// define builder and registration
class PropRungeKuttaFactory: public PropagatorFactory::AbsFactory{
    public:
        PropRungeKuttaFactory(): PropagatorFactory::AbsFactory( "runge-kutta" ){}
        Propagator* create( const string& name ) override{
            return new PropRungeKutta( name );
        }
};
// create global Factory, so it's registered before main execution
static PropRungeKuttaFactory rk;



PropRungeKutta::PropRungeKutta( const string& name ):
    PropSingle( name ){
}

PropRungeKutta::~PropRungeKutta(){
}



// single step propagation
DoubleMatrix PropRungeKutta::StepS( DoubleMatrix y1 ) const {

    DoubleMatrix f1 = ss->GetF( y1 );
    // middle points
    DoubleMatrix y2 = y1 + ( f1 * ( cf.timestep / 2 ) );
    DoubleMatrix f2 = ss->GetF( y2 );

    DoubleMatrix y3 = y1 + ( f2 * ( cf.timestep / 2 ) );
    DoubleMatrix f3 = ss->GetF( y3 );

    DoubleMatrix y4 = y1 + ( f3 * ( cf.timestep ) );
    DoubleMatrix f4 = ss->GetF( y4 );

    // step
    y1 += ( cf.timestep / 6 ) * ( f1 + ( 2 * f2 ) + ( 2 * f3 ) + f4 );

    return y1;

}
