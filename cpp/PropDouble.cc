#include "PropDouble.h"

#include <string>

#include "Propagator.h"
#include "PropagatorFactory.h"
#include "PropEuler.h"
#include "StarSystem.h"
#include "Array.h"


using namespace std;


PropDouble::PropDouble( const string& name ):
    PropEuler( name ){
}

PropDouble::~PropDouble(){
}


// function to run the propagator
void PropDouble::Execute(){

    // read and print initial state
    DoubleMatrix y0 = ss->GetY();
    *file << y0[0];

    // single step with Explicit Euler method
    DoubleMatrix y1 = StepS( y0 );
    *file << y1[0];

    // loop for iterations
    for( u_int64_t i = 1; i <= cf.iterations; i++){
        DoubleMatrix y2 = Step( y0, y1 );
        if( i % cf.frame_l == 0) *file << y2[0];
        y0 = move( y1 );
        y1 = move( y2 );
    }

    return;

}