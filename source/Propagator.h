#ifndef Propagator_h
#define Propagator_h

#include <string>
#include <fstream>

class StarSystem;
class Settings;

class Propagator{

    public:

        Propagator( const Settings* info, const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        Propagator           ( const Propagator& x ) = delete;
        Propagator& operator=( const Propagator& x ) = delete;

        virtual ~Propagator();

        // function to run the propagator
        void run( const StarSystem* ssi );
        std::string GetType() const;

    protected:

        const Settings* settings;
        // type of propagator
        const std::string type = "default";
        // writing file
        std::ofstream* file;
        
        const StarSystem *ss;

    private:

        // function to be called at execution start
        void   StartUp();
        // function to run the propagator
        virtual void   Execute() = 0;
        // function to be called at execution end
        void Terminate();

};

#endif

