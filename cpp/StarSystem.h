#ifndef StarSystem_h
#define StarSystem_h

#include <vector>
#include <string>
#include <fstream>

#include "Array.h"

using namespace std;

class StarSystem{
    public:

        enum Data { pos, vel, grav };
        static const double g_const;

        StarSystem();

        StarSystem           ( const StarSystem& x ) = delete;
        StarSystem& operator=( const StarSystem& x ) = delete;
/*
        StarSystem           ( StarSystem&& x ) noexcept;
        StarSystem& operator=( StarSystem&& x ) noexcept;
*/
        ~StarSystem();

        struct Planet{
            Planet( string n, double m,
                    double px, double py, double pz,
                    double vx, double vy, double vz );
            string name;
            double mass;
            Array<double> pos;
            Array<double> vel;
        };

        
        // add a planet to the star system
        void Add( string n, double m,
                  double px, double py, double pz,
                  double vx, double vy, double vz );

        // write on file star system info
        ofstream* Print( ofstream* file ) const;

        // retrieve planets information in matrix form
        Matrix GetMatrix( const Data& request ) const;

        // calculate gravitational force
        Matrix Gravity( const Matrix& pos ) const;

        // block class from further modifications
        void Lock();
        
    private:

        vector<Planet*> planets;
        bool locked;
        // data stored for easy access
        vector<double> masses;
        Matrix position, velocity;

/*
        // create copy of the star system
        void Copy( const StarSystem& x );
        // move star system
        void Move( StarSystem& x );
*/

        // delete dynamic pointers
        void Clear();

};



#endif