#ifndef PropagatorFactory_h
#define PropagatorFactory_h

#include <string>
#include <vector>
#include <map>

class StarSystem;
class Settings;
class Propagator;

class PropagatorFactory {

    public:

        PropagatorFactory();
        // deleted copy constructor and assignment to prevent unadvertent copy
        PropagatorFactory           ( const PropagatorFactory& x ) = delete;
        PropagatorFactory& operator=( const PropagatorFactory& x ) = delete;

        virtual ~PropagatorFactory();

        // create all requested analysis objects
        static std::vector<Propagator*> create( const Settings* info );

        // analysis object abstract factory
        class AbsFactory {
            public:
                // Analyzers are registered with a name so that they are actually 
                // created only if, at runtime, their name is listed in the command line
                AbsFactory( const std::string& name ) { RegisterFactory( name, this ); }
                virtual ~AbsFactory() {}
                virtual Propagator* create( const Settings* info, const std::string& name ) = 0;
        };

    private:

        // function to add analyzer concrete factories
        static void RegisterFactory( const std::string& name, AbsFactory* f );
        // map to associate analyzer names with corresponding factories
        static std::map<std::string,AbsFactory*>* FactoryMap();

};

#endif

