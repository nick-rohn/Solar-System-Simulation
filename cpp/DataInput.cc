#include "DataInput.h"

#include "StarSystem.h"

extern int debug;
static const int debug_level = 2;

DataInput::DataInput() {
}


DataInput::~DataInput() {
}

// create star system
const StarSystem* DataInput::read() {
    if( debug >= debug_level ) cout << "Reading data..." << endl;
    StarSystem* ss = get();
    if( debug >= debug_level ) cout << "Star system created" << endl;
    ss->Lock();
    return ss;

}