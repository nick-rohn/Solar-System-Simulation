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
    for( u_int64_t i = 1; i <= cf.iterations; i++){
        y0 = StepS( y0 );
        if( i % cf.frame_l == 0) *file << y0[0];
    }

    return;
    
}