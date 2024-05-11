#include "PropSingle.h"

#include <string>

#include "Propagator.h"
#include "Array.h"
#include "StarSystem.h"


using namespace std;



PropSingle::PropSingle( const string& name ):
    Propagator( name ){
}

PropSingle::~PropSingle(){
}


// function to run the propagator
void PropSingle::Execute(){

    // read and print initial state
    DoubleMatrix y0 = ss->GetY();

    *file << y0[0];

    // loop for iterations
    for( int i = 0; i < iterations; i++){
        y0 = StepS( y0 );
        *file << y0[0];
    }

    return;
    
}