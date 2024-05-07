#include "Converter.h"

#include <string>
#include <map>

using namespace std;


Converter::Converter(){
}

Converter::~Converter(){
}


// convert input string into seconds
double Converter::TimeToSec( const string& in ){
    u_int n = in.size();
    char time = in[ n-1 ];
    double value = stod( in.substr(0, n-1) );
    value *= convert.at( time );
    return value;
}


// conversion rates
const std::map<char, double> Converter::convert = {
    { 's',            1 },
    { 'h',        60*60 },
    { 'd',     24*60*60 },
    { 'w',   7*24*60*60 },
    { 'm',  30*24*60*60 },
    { 'y', 365*24*60*60 }
};