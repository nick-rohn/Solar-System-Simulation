#ifndef Settings_h
#define Settings_h

#include <string>
#include <vector>

class Settings {

    public:

        Settings( int argc, char* argv[] );
        // deleted copy constructor and assignment to prevent unadvertent copy
        Settings           ( const Settings& x ) = delete;
        Settings& operator=( const Settings& x ) = delete;

        ~Settings();

    

        // get the list of all words
        const std::vector<std::string>& ArgList() const;
        // get the word coming after the word 'key'
        const std::string& value( const std::string& key ) const;
        // check if the word 'key' is present
        bool contains( const std::string& key ) const;

    private:

        // container for words
        std::vector<std::string> args;
        // value to return for keys not found
        static std::string default_string;

        // settings filename
        static std::string settings_file;

};

#endif

