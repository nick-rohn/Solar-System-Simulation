#include "PropagatorFactory.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "StarSystem.h"
#include "Settings.h"
#include "Propagator.h"

using namespace std;

extern int debug;
static const int debug_level = 1;

PropagatorFactory::PropagatorFactory() {
}


PropagatorFactory::~PropagatorFactory() {
}


// create all requested analysis objects
vector<Propagator*> PropagatorFactory::create( const Settings* info ) {
    
    if( debug >= debug_level ) cout << "Creating propagator list..." << endl;
    vector<Propagator*> prop_list;
    // loop over analysis object factories
    static map<string,AbsFactory*> *fm = FactoryMap();
    for ( const auto& element: *fm ) {
        // create analysis object if its name is listed in the command line
        if ( info->contains( element.first ) )
            prop_list.push_back( element.second->create( info, element.first ) );
    }
    if( debug >= debug_level ) cout << "List created" << endl <<endl;
    return prop_list;
}


// function to add analyzer concrete factories
void PropagatorFactory::RegisterFactory( const string& name, AbsFactory* b ) {
    static map<string,AbsFactory*>& fm = *FactoryMap();
    fm[name] = b;
    return;
}


// map to associate analyzer names with corresponding factories
map<string,PropagatorFactory::AbsFactory*>* PropagatorFactory::FactoryMap() {
    static map<string,AbsFactory*>* fm = new map<string,AbsFactory*>;
    return fm;
}

