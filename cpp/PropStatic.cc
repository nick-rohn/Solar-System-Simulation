#include "PropStatic.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "Settings.h"
#include "StarSystem.h"
#include "Array.h"


using namespace std;

// define builder and registration
class PropStaticFactory: public PropagatorFactory::AbsFactory{
    public:
        PropStaticFactory(): PropagatorFactory::AbsFactory( "static" ){}
        Propagator* create( const Settings* info, const string& name ) override{
            return new PropStatic( info, name );
        }
};
// create global Factory, so it's registered before main execution
static PropStaticFactory stat;

PropStatic::PropStatic( const Settings* info, const string& name ):
    Propagator( info, name ){
}

PropStatic::~PropStatic(){
}

// function to run the propagator
void PropStatic::Execute(){
    Matrix pos = ss->GetMatrix( StarSystem::Data::pos );
    Matrix vel = ss->GetMatrix( StarSystem::Data::vel );
    Matrix grav = ss->GetMatrix( StarSystem::Data::grav );
    *file << pos << vel << grav;
    return;
}