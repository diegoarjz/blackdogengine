#ifndef DATATYPES_H_
#define DATATYPES_H_

/*
 * Provides a layer of abstraction for data types.
 * Also helps to ensure that the programmer knows the
 * size of each type.
 */
namespace bde {

    /// Boolean
    typedef bool BOOLEAN;

    /// Byte
    typedef unsigned char Byte;

    /// Signed 8 bit integer (char)
    typedef char I8;
    /// Unsigned 8 bit integer (uchar)
    typedef unsigned char U8;

    /// Signed 16 bit integer
    typedef short int I16;
    /// Unsigned 16 bit integer.
    typedef unsigned short int U16;
    /// Signed 32 bit integer
    typedef int I32;
    /// Unsigned 32 bit integer.
    typedef unsigned int U32;
    /// Signed 64 bit integer.
    typedef long int I64;
    /// Unsigned 64 bit integer.
    typedef unsigned long int U64;

    /// Signed 32 bit float
    typedef float F32;
    /// Signed 64 bit float
    typedef double F64;

    typedef F64 TIME_T;
}
#endif
