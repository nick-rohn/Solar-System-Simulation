#ifndef ReadFromFile_h
#define ReadFromFile_h

#include <fstream>
#include <string>

#include "DataInput.h"

class StarSystem;

class ReadFromFile: public DataInput {

    public:

        // read data from file "name"
        ReadFromFile( const std::string& name );
        // deleted copy constructor and assignment to prevent unadvertent copy
        ReadFromFile           ( const ReadFromFile& x ) = delete;
        ReadFromFile& operator=( const ReadFromFile& x ) = delete;

        ~ReadFromFile() override;

    private:

        // get a star system
        const StarSystem* get() override;

        // input file
        std::ifstream* file;

        // read and event
        const StarSystem* ReadFile();

};

#endif

