#ifndef Converter_h
#define Converter_h

#include <string>
#include <map>

class Converter{

    public:

        Converter();
        ~Converter();

        // convert input string into seconds
        static double TimeToSec( const std::string& in );

    private:

        // conversion rates
        static const std::map<char, double> convert;

};


#endif