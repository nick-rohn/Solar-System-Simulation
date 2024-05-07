#include "Array.h"

#include <iostream>
#include <cmath>

using namespace std;

extern int debug;
static const int debug_deep = 11;


//CONSTRUCTORS

// create empty array
template <class T>
Array<T>::Array():
    length( 0 ), data( nullptr ){

    if( debug >= debug_deep ) cout << "Void array created\t\t" << this << endl;

}


// initialize array[s] at 0
template <class T>
template <typename U>
Array<T>::Array( U input ):
    length( input ), data( new T[length]{} ){

        if( debug >= debug_deep ) cout << "Empty array created\t\t" << this << endl;

}


// initialize array with given parameters
template <class T>
template <typename ... U>
Array<T>::Array( U ... input ):
    length( sizeof ... (U) ), data( new T[length] ){

        u_int i = 0;
        (void(data[i++] = input) , ...);
        if( debug >= debug_deep ) cout << "Array created\t\t" << this << endl;
        
}


template <class T>
Array<T>::Array( const Array<T>& a ):
    data( nullptr ){
    Copy( a );
}


template <class T>
Array<T>::Array( Array<T>&& a ) noexcept:
    length( 0 ), data( nullptr ){
    Move( a );
}


template <class T>
Array<T>::~Array(){
    delete[] data;
}


template <class T>
Array<T>& Array<T>::operator=( const Array<T>& a ){
    Copy( a );
    return *this;
}


template <class T>
Array<T>& Array<T>::operator=( Array<T>&& a ) noexcept {
    Move( a );
    return *this;
}





// PUBLIC

// array functions
template <class T>
u_int Array<T>::size() const {
    return length;
}

template <class T>
const
T& Array<T>::operator[]( u_int i ) const {
    CheckRange( i );
    return data[i];
}

template <class T>
T& Array<T>::operator[]( u_int i ){
    CheckRange( i );
    return data[i];
}

template <class T>
void Array<T>::CheckRange( u_int i ) const {
    if( i >= length ) throw out_of_range( "Out of range" );
    return;
}



// vector module
template <class T>
double Array<T>::module() const {

    double sum = 0;
    for( u_int i = 0; i < length; i++ ) sum += pow( data[i], 2.0 );
    return sqrt( sum );

}





// OPERATORS

// addition
template <class T>
Array<T>& Array<T>::operator+=( const Array<T>& add ){

    // if array is still void, copy array
    if( length == 0 ) return *this = add;
    else if( length != add.length) throw out_of_range( "Arrays of different sizes" );

    for( u_int i = 0; i < length; i++ ) data[i] += add.data[i];
    return *this;

}

template <class U>
Array<U> operator+( Array<U> lhs, const Array<U>& rhs ){
    lhs += rhs;
    return lhs;
}




// subtraction
template <class T>
Array<T>& Array<T>::operator-=( const Array<T>& add ){

    // if array is still void, make same size as other
    if( length == 0 ) data = new T[ length = add.length ]{};
    else if( length != add.length) throw out_of_range( "Arrays of different sizes" );

    for( u_int i = 0; i < length; i++ ) data[i] -= add.data[i];
    return *this;

}

template <class U>
Array<U> operator-( Array<U> lhs, const Array<U>& rhs ){
    lhs -= rhs;
    return lhs;
}




// multiplication
template <class T>
template <typename U>
Array<T>& Array<T>::operator*=( const U& fact ){

    for( u_int i = 0; i < length; i++ ) data[i] *= fact;
    return *this;

}


template <class U, typename V>
Array<U> operator*( Array<U> arr, const V& fact ){
    arr *= fact;
    return arr;
}


template <class U, typename V>
Array<U> operator*( const V& fact, Array<U> arr ){
    return operator*( arr, fact );
}




// division
template <class T>
template <typename U>
Array<T>& Array<T>::operator/=( const U& fact ){

    for( u_int i = 0; i < length; i++ ) data[i] /= fact;
    return *this;

}


template <class U, typename V>
Array<U> operator/( Array<U> arr, const V& fact ){
    arr /= fact;
    return arr;
}




// print content in a line
template <typename U>
ostream& operator<<( ostream& os, const Array<U>& arr ){

    for( u_int i = 0; i < arr.length; i++ ) os << arr.data[i] << '\t';
    return os << endl;

}





// PRIVATE

template <class T>
void Array<T>::Copy( const Array<T>& a ){

    if( data == a.data ) return;

    delete[] data;
    data = new T[length = a.length];

    T* pr = a.data + length;
    T* pl =   data + length;
    while ( pl > data ) *--pl = *--pr;
    if( debug >= debug_deep ) cout << "Array copied \t\t" << &a << endl;

    return;

}



template <class T>
void Array<T>::Move( Array<T>& a ){

    if( data == a.data ) return;

    delete[] data;
    length = a.length;
    data = a.data;

    a.length = 0;
    a.data = nullptr;
    if( debug >= debug_deep ) cout << "Array moved  \t\t" << &a << endl;

    return;

}