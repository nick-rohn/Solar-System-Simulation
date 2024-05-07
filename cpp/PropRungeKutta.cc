#include "PropRungeKutta.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "Settings.h"


using namespace std;

// define builder and registration
class PropRungeKuttaFactory: public PropagatorFactory::AbsFactory{
    public:
        PropRungeKuttaFactory(): PropagatorFactory::AbsFactory( "runge-kutta" ){}
        Propagator* create( const Settings* info, const string& name ) override{
            return new PropRungeKutta( info, name );
        }
};
// create global Factory, so it's registered before main execution
static PropRungeKuttaFactory ver;

PropRungeKutta::PropRungeKutta( const Settings* info, const string& name ):
    Propagator( info, name ){
}

PropRungeKutta::~PropRungeKutta(){
}

// function to run the propagator
void PropRungeKutta::Execute(){
    return;
}