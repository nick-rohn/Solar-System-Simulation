#ifndef Converter_h
#define Converter_h

#include <string>
#include <map>

class Converter{

    public:

        Converter();
        ~Converter();
        static double TimeToSec( const std::string& in );

    private:

        static const std::map<char, double> convert;

};


#endif