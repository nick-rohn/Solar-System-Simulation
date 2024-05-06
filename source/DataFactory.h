#ifndef DataFactory_h
#define DataFactory_h

class Settings;
class DataInput;

class DataFactory {

    public:

        DataFactory();
        // deleted copy constructor and assignment to prevent unadvertent copy
        DataFactory           ( const DataFactory& x ) = delete;
        DataFactory& operator=( const DataFactory& x ) = delete;

        virtual ~DataFactory();

        // create data source
        static DataInput* create( const Settings* info );

};

#endif

