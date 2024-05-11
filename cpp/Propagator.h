#ifndef Propagator_h
#define Propagator_h

#include <string>
#include <fstream>

using namespace std;

class StarSystem;

class Propagator{

    public:

        Propagator( const string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        Propagator           ( const Propagator& x ) = delete;
        Propagator& operator=( const Propagator& x ) = delete;

        virtual ~Propagator();

        // function to run the propagator
        void run( const StarSystem* ssi,
                  const string ts, const string it );
        string GetType() const;

    protected:

        // type of propagator
        const string type;
        // writing file
        string filename;
        ofstream* file;
        // pointer to star system
        const StarSystem *ss;
        // propagation data
        double timestep;
        double iterations;

    private:

        // function to be called at execution start
        void   StartUp();
        // function to run the propagator
        virtual void   Execute() = 0;
        // function to be called at execution end
        void Terminate();

};

#endif

