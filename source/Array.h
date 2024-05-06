#ifndef Array_h
#define Array_h

#include <iostream>

using namespace std;

template <class T>
class Array {

    public:

        // create empty array
        Array();
        // initialize array[s] at 0
        template <typename U>
        Array( U s );
        // initialize array with given parameters
        template <typename ... U>
        Array( U ... input );

        Array( const Array<T>& a );
        Array( Array<T>&& a ) noexcept;

        ~Array();

        Array<T>& operator=( const Array<T>& a );
        Array<T>& operator=( Array<T>&& a ) noexcept;

        typedef Array<Array<double>> Matrix;
        typedef Array<Matrix> DoubleMatrix;

        // array functions
        u_int size() const;
        T& operator[]( u_int i );
        const T& operator[]( u_int i ) const;

        // vector module
        double module() const;

        // addition
        Array<T>& operator+=( const Array<T>& add );
        template <class U>
        friend Array<U> operator+( Array<U> lhs, const Array<U>& rhs );

        // subtraction
        Array<T>& operator-=( const Array<T>& add );
        template <class U>
        friend Array<U> operator-( Array<U> lhs, const Array<U>& rhs );

        // multiplication
        template <typename U>
        Array<T>& operator*=( const U& fact );
        template <class U, typename V>
        friend Array<U> operator*( Array<U> arr, const V& fact );
        template <class U, typename V>
        friend Array<U> operator*( const V& fact, Array<U> arr );

        // division
        template <typename U>
        Array<T>& operator/=( const U& fact );
        template <class U, typename V>
        friend Array<U> operator/( Array<U> arr, const V& fact );


        // print content in a line
        template <class U>
        friend ostream& operator<<( ostream& os, const Array<U>& arr );

    private:

        u_int length;
        T* data;

        void CheckRange( u_int i ) const;
        void Copy( const Array<T>& a );
        void Move( Array<T>& a );

};

typedef Array<Array<double>> Matrix;
typedef Array<Matrix> DoubleMatrix;

#include "Array.hpp"

#endif