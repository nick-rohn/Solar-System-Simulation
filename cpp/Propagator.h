#ifndef Propagator_h
#define Propagator_h

#include <string>
#include <fstream>

using namespace std;

class StarSystem;
class Settings;

class Propagator{

    public:

        Propagator( const string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        Propagator           ( const Propagator& x ) = delete;
        Propagator& operator=( const Propagator& x ) = delete;

        virtual ~Propagator();

        // function to run the propagator
        void run( const StarSystem* ssi );
        // get current type of propagator
        string GetType() const;
        // setup propagation config
        static void Configuration( const Settings* info );

    protected:

        // type of propagator
        const string type;
        // writing file
        string filename;
        ofstream* file;
        // pointer to star system
        const StarSystem *ss;

        // propagation config
        struct Config{
            string p_timestep;
            string p_duration;
            string p_frame_l;
            double timestep;
            u_int64_t iterations;
            u_int64_t frame_l;
            void Update( string ts, string dur, string fr );
        };
        static Config cf;

    private:

        // function to be called at execution start
        void   StartUp();
        // function to run the propagator
        virtual void   Execute() = 0;
        // function to be called at execution end
        void Terminate();

};

#endif

