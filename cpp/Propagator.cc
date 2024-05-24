#include "Propagator.h"

#include <string>
#include <fstream>

#include "StarSystem.h"
#include "Converter.h"
#include "Settings.h"

using namespace std;

extern int debug;
static const int debug_level = 11;

Propagator::Propagator( const string& name ):
    type( name ){
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
    if ( type != "static" ){
        *file << "duration     = " << cf.p_duration << endl;
        *file << "iterations   = " << cf.iterations << endl;
        *file << "timestep     = " << cf.timestep   << endl;
        *file << "frame length = " << cf.frame_l    << endl;
    }
    ss->Print( file );

    if( debug >= debug_level ) cout << "File created" << endl;

    return;

}



// function to be called at execution end
void Propagator::Terminate(){
    delete file;
}




// function to run the propagator
void Propagator::run( const StarSystem* ssi ){
    
    if( type == "static" ) filename = type + ".txt";
    else filename = type + '_' + cf.p_timestep + '_' + cf.p_duration + ".txt";
    
    ss = ssi;

    StartUp();
    Execute();
    Terminate();
    return;

}




// get current type of propagator
string Propagator::GetType() const {
    return type;
}





// save and calculate config data
void Propagator::Config::Update( string ts, string dur, string fr ){

    p_timestep = ts;
    p_duration = dur;
    // if frame keyword not present, set same as timestep
    if( fr == "" ) fr = ts;
    p_frame_l  = fr;

    timestep   = Converter::TimeToSec( p_timestep );
    iterations = lround( Converter::TimeToSec( p_duration ) / timestep );
    frame_l    = lround( Converter::TimeToSec( p_frame_l  ) / timestep );

}


// setup propagation config
void Propagator::Configuration( const Settings* info){

    string ts  = info->value( "timestep" );
    string dur = info->value( "duration" );
    string fr  = info->value(  "frames"  );

    cf.Update( ts, dur, fr );
    
}


Propagator::Config Propagator::cf;