#include "ReadFromFile.h"

#include <fstream>
#include <string>
#include <sstream>

#include "StarSystem.h"

using namespace std;

extern int debug;
static const int debug_level = 3;

// read data from file "name"
ReadFromFile::ReadFromFile( const string& name ) {
    if( debug >= debug_level ) cout << "Opening file \"" << name <<"\"..." << endl;
    file = new ifstream( name );
}


ReadFromFile::~ReadFromFile() {
    if( debug >= debug_level ) cout << "Closing file..." << endl <<endl;
    delete file;
}


// get a StarSystem
const StarSystem* ReadFromFile::get() {
    return ReadFile();
}


// create a StarSystem
const StarSystem* ReadFromFile::ReadFile() {

    // StarSystem pointer and identifier
    StarSystem* ss = new StarSystem;
    string name;
    double mass, px, py, pz, vx, vy, vz;

    // try to read input file
    // on failure close program
    if( !( getline( *file, name ) ) ){
        cout << "Error opening the file" << endl;
        exit(1);
    }

    do{

        //read and store planets
        *file >> mass >> px >> py >> pz >> vx >> vy >> vz;
        ss->Add( name, mass, px, py, pz, vx, vy, vz );
        if( debug >= debug_level ) cout << "Added " << name << endl;
    }
    while( ( getline(*file, name), getline( *file, name ) ) );

    return ss;

}

