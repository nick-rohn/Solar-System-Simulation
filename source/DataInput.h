#ifndef DataInput_h
#define DataInput_h

class StarSystem;

class DataInput {

    public:

        DataInput();
        // deleted copy constructor and assignment to prevent unadvertent copy
        DataInput           ( const DataInput& x ) = delete;
        DataInput& operator=( const DataInput& x ) = delete;

        virtual ~DataInput();

        // create star system and send to propagators
        virtual const StarSystem* read();

    private:

        // get a star system
        virtual const StarSystem* get() = 0;

};

#endif

