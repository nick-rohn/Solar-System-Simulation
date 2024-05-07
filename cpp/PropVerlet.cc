#include "PropVerlet.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "Settings.h"


using namespace std;

// define builder and registration
class PropVerletFactory: public PropagatorFactory::AbsFactory{
    public:
        PropVerletFactory(): PropagatorFactory::AbsFactory( "verlet" ){}
        Propagator* create( const Settings* info, const string& name ) override{
            return new PropVerlet( info, name );
        }
};
// create global Factory, so it's registered before main execution
static PropVerletFactory ver;

PropVerlet::PropVerlet( const Settings* info, const string& name ):
    Propagator( info, name ){
}

PropVerlet::~PropVerlet(){
}

// function to run the propagator
void PropVerlet::Execute(){
    return;
}