#include "Settings.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

extern int debug;
static const int debug_level = 5;



// value to return for keys not found
string Settings::default_string = "";


// default settings filename
string Settings::settings_file = "_settings.txt";


Settings::Settings( int argc, char* argv[] ){
    
    args.reserve( argc + 20 );

    // read manual arguements
    for( int iarg = 1; iarg < argc; ++iarg ) args.push_back( argv[iarg] );

    // read settings filename, else leave default
    if( contains( "settings" ) ) settings_file = value( "settings" );

    // read settings file and add at the end of arguments    
    ifstream* file = new ifstream( settings_file );
    string in;
    while( *file >> in ) args.push_back( in );
    delete file;

    args.resize( args.size() );
    
    // set debug mode if requested
    if( contains( "debug" ) ) debug = stoi( value( "debug" ) );
    
}


Settings::~Settings() {
}


// get the list of all words
const vector<string>& Settings::ArgList() const {
    return args;
}


// get the word coming after the word 'key'
const string& Settings::value( const string& key ) const {
    if( debug >= debug_level ) cout << key << " = ";
    // loop over words
    int i = 0;
    int n = args.size() - 1;
    while( i < n ){
        // if word is equal to key, return next word
        if( args[i++] == key ){
            if( debug >= debug_level ) cout << args[i] << endl;
            return args[i];
        }
    }
    // if key not found, return a default string
    if( debug >= debug_level ) cout << "#####" << endl;
    return default_string;
}


// check if the word 'key' is present
bool Settings::contains( const string& key ) const {
    if( debug >= debug_level ) cout << key;
    // loop over words
    for( const string& s: args ){
        // if word is equal to key, return true
        if( s == key ){
            if( debug >= debug_level ) cout << " found" << endl;
            return true;
        }
    }
    // if key not found, return false
    if( debug >= debug_level ) cout << " not found" << endl;
    return false;
}

