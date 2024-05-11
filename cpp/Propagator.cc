#include "Propagator.h"

#include <string>
#include <fstream>

#include "StarSystem.h"
#include "Settings.h"
#include "Converter.h"

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

    // create file
    file = new ofstream( filename );

    // print header file
    *file << "propagator = " << type       << endl;
    *file << "iterations = " << iterations << endl;
    *file << "timestep   = " << timestep   << endl;
    ss->Print( file );

    if( debug >= debug_level ) cout << "File created" << endl;

    return;

}


// function to be called at execution end
void Propagator::Terminate(){
    delete file;
}

// function to run the propagator
void Propagator::run( const StarSystem* ssi,
                      const string ts, const string it ){
    
    filename = type + '_' + ts + ".txt";
    
    timestep = Converter::TimeToSec( ts );
    iterations =  stod( it );

    ss = ssi;

    StartUp();
    Execute();
    Terminate();
    return;

}


string Propagator::GetType() const {
    return type;
};