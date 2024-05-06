#include "Propagator.h"

#include <string>
#include <fstream>

#include "StarSystem.h"
#include "Settings.h"

using namespace std;

extern int debug;
static const int debug_level = 11;

Propagator::Propagator( const Settings* info, const string& name ):
    settings( info ), type( name ){
}


Propagator::~Propagator(){
}

// function to be called at execution start
void Propagator::StartUp(){
    if( debug >= debug_level ) cout << "Creating file..." << endl;
    // open file (TODO: name with settings)
    file = new ofstream( settings->value( type ) );
    *file << "Propagator " << type << endl;

    ss->Print(file);

    *file << endl;

    if( debug >= debug_level ) cout << "File created" << endl;

    return;

}


// function to be called at execution end
void Propagator::Terminate(){
    delete file;
}

// function to run the propagator
void Propagator::run( const StarSystem* ssi ) {

    ss = ssi;

    StartUp();
    Execute();
    Terminate();
    return;

}


string Propagator::GetType() const {
    return type;
};