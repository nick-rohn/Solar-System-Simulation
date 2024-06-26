#include <vector>
#include <thread>
#include <iostream>

#include "StarSystem.h"
#include "Settings.h"
#include "DataInput.h"
#include "DataFactory.h"
#include "Propagator.h"
#include "PropagatorFactory.h"

using namespace std;

int debug = 0;
static const int debug_level = 7;

int main( int argc, char *argv[] ){

    // store command line parameters
    Settings* settings = new Settings( argc, argv );

    // create data source
    DataInput* dr = DataFactory::create( settings );

    // read data
    const StarSystem* ss = dr->read();
    delete dr;
    
    // create list of propagators
    vector<Propagator*> prop_list = PropagatorFactory::create( settings );

    // configure propagators
    Propagator::Configuration( settings );

    // create threads for parallel execution
    vector<thread*> threads;
    threads.reserve( prop_list.size() );
    if( debug >= debug_level ) cout << endl << "Initializing threads..." << endl << endl;

    // execute each propagator on a different thread
    for( Propagator* p : prop_list ){
        thread* t = new thread( &Propagator::run, p, ss);
        threads.push_back( t );
        if( debug >= debug_level ) cout << "Thread " << p->GetType() << " initialized" << endl;
    }

    // wait for all threads to end
    for( thread* t : threads ){
        t->join();
        delete t;
        if( debug >= debug_level ){
            static int i = 1;
            cout << "Thread " << i++ << " closed" << endl;
        }
    }

    return 0;

}