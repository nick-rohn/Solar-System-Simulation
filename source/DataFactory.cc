#include "DataFactory.h"

#include <iostream>
#include <sstream>

#include "Settings.h"
#include "DataInput.h"
#include "ReadFromFile.h"
// manual input, online source...

using namespace std;

extern int debug;
static const int debug_level = 1;

DataFactory::DataFactory() {
}


DataFactory::~DataFactory() {
}


// create data source
DataInput* DataFactory::create( const Settings* info ) {

    if( debug >= debug_level ) cout << "Selecting datasource...\t\t";

    // input filename = ReadFromFile
    if ( info->contains( "input" ) ){
        return new ReadFromFile( info->value( "input" ) );
    }
    // extra cases, WIP
    // manual input
    // web access
    cout << "No datasource selected" << endl;
    exit(1);
}

