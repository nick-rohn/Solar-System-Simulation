#include "StarSystem.h"

#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#include "Array.h"

using namespace std;

const double StarSystem::g_const = 6.674e-20; // (kg*km/s^2)*(km^2/kg^2)

StarSystem::Planet::Planet( string n, double m,
                            double px, double py, double pz,
                            double vx, double vy, double vz ):
    name( n ), mass( m ), pos( px, py, pz ), vel( vx, vy, vz ){
}



// CONSTRUCTORS

StarSystem::StarSystem():
    locked( false ){

        // reserve space for planets
        planets.reserve( 10 );

}
/*
StarSystem::StarSystem( const StarSystem& x ){
    Copy( x );
}

StarSystem& StarSystem::operator=( const StarSystem& x ){
    Copy( x );
    return *this;
}

StarSystem::StarSystem( StarSystem&& x ) noexcept {
    Move( x );
}

StarSystem& StarSystem::operator=( StarSystem&& x ) noexcept {
    Move( x );
    return *this;
}
*/
StarSystem::~StarSystem(){
    Clear();
}





// PUBLIC

// add a planet to the star system
void StarSystem::Add( string n, double m,
                  double px, double py, double pz,
                  double vx, double vy, double vz ){
    if( locked ){
        cout << "ERROR: StarSystem locked; couldn't add " << n << " to the planets list" << endl << endl;
        return;
    }
    Planet* p = new Planet( n, m, px, py, pz, vx, vy, vz );
    planets.push_back( p );

    return;
}


// write on file star system info
ofstream* StarSystem::Print( ofstream* file ) const {
    
    // number of planets
    *file << "planets    = " << planets.size() << endl << endl;

    // planets names and masses
    for ( Planet* p : planets ){
        *file << p->name << '\t' << p->mass << endl; 
    }

    *file << endl;
    return file;
}


// retrieve planets information in matrix form
Matrix StarSystem::GetMatrix( const Data& request ) const {

    switch ( request ){
        case Data::pos:
            return position;
        
        case Data::vel:
            return velocity;

        case Data::grav:
            return Acceleration( position );
        
        default:
            return Matrix( planets.size() );
    }

}




// calculate gravitational acceleration in given position
Matrix StarSystem::Acceleration( const Matrix& pos ) const {

    unsigned int n = planets.size();
    Matrix grav( n );

    for( u_int i = 0; i < (n-1); i++ ){
        for( u_int j = (i+1); j < n; j++ ){
            // calculate gravitational force between planets i and j
            Array<double> r = pos[j] - pos[i];
            Array<double> f = ( g_const * masses[i] * masses[j] / pow( r.module(), 3.0) ) * r;
            // add force to both planets
            grav[i] += f;
            grav[j] -= f;
        }
    }

    // divide by mass of each planet
    for( u_int i = 0; i < n; i++ ) grav[i] /= masses[i];

    return grav;
}



// block class from further modifications
void StarSystem::Lock(){

    locked = true;

    unsigned int n = planets.size();

    // save data for easy access
    // masses
    masses.resize( n );
    for( u_int i = 0 ; i < n; i++ ) masses[i] = planets[i]->mass;

    // positions
    position = Matrix( n );
    for( u_int i = 0; i < n; i++) position[i] = planets[i]->pos;

    // velocities
    velocity = Matrix( n );
    for( u_int i = 0; i < n; i++) velocity[i] = planets[i]->vel;

    return;

}




// retrieve planets information in double matrix form
DoubleMatrix StarSystem::GetY() const {

    return DoubleMatrix( position, velocity );

}


// retrieve planets velocity and acceleration
DoubleMatrix StarSystem::GetF( const DoubleMatrix& y ) const {

    return DoubleMatrix( y[1], Acceleration( y[0] ));

}

// PRIVATE

/*
// create copy of the star system
void StarSystem::Copy( const StarSystem& x ){

    if( planets == x.planets ) return;

    Clear();
    planets.reserve( x.planets.size() );
    for( Planet* p : x.planets ){
        Planet* n = new Planet( *p );
        planets.push_back( n );
    }

    return;

}

// move star system
void StarSystem::Move( StarSystem& x ) {

    if ( planets == x.planets ) return;

    Clear();
    planets.reserve( x.planets.size() );
    planets = x.planets;
    x.planets.clear();

    return;

}
*/

// delete dynamic pointers
void StarSystem::Clear(){
    
    // delete all the planet pointers
    for( u_int i = 0; i < planets.size(); ++i ) delete planets[i];

    return;

}
