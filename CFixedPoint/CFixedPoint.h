/*
 *  C Q48.16 Fixed Point library
 *  Copyright (c) 2020 Steven 'lazalong' GAY - lazalong@gmail.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef CFIXEDPOINT_H
#define CFIXEDPOINT_H

#define CFIXEDPOINT_VERSION_MAJOR 1
#define CFIXEDPOINT_VERSION_MINOR 0
#define CFIXEDPOINT_VERSION_PATCH 0

#define CFIXEDPOINT_CALLBACK __cdecl

#ifdef CFIXEDPOINT_DLL
    #ifdef CFIXEDPOINT_IMPLEMENTATION
        #define CFIXEDPOINT_API __declspec(dllexport)
    #else
        #define CFIXEDPOINT_API __declspec(dllimport)
    #endif
#endif

// --------------  API  --------------------------
#ifdef _MSC_VER 
    #pragma warning(push)
    #pragma warning(disable: 4244) /* 64-bit to 32-bit integer conversion */
    #pragma warning(disable: 4838) /* double to in64_t conversion requires a narrowing conversion */
#endif

#ifdef __cplusplus
extern "C" {
#endif

// TODO move all .h if possible into .c
#include <stdint.h>
#include <cassert>
#include <string.h>
#include <stdio.h>  // printf
#include <stdlib.h> // atoll and atol
//#include <inttypes.h>

    // C 64bit fixed point Q48.16 (1st bit = sign, 47 bit for , 16 bit for 5 decimals precision)
    typedef struct _fp4816_t {
        int64_t x;
    } fp4816_t;

    typedef struct _fp1616_t {
        int32_t x;
    } fp1616_t;

    // [-1; +1] with 30 bit for 9 decimal precision
    typedef struct _fp0230_t {
        int32_t x;
    } fp0230_t;

    typedef struct _fp88_t {
        int16_t x;
    } fp88_t;

    // <x,y>
    typedef struct _fp4816_2_t {
        int64_t x;
        int64_t y;
    } fp4816_2_t;

    // <x,y,z>
    typedef struct _fp4816_3_t {
        int64_t x;
        int64_t y;
        int64_t z;
    } fp4816_3_t;

    // Quaternion <x,y,z,w>
    typedef struct _fp4816_4_t {
        int64_t x;
        int64_t y;
        int64_t z;
        int64_t w;
    } fp4816_4_t;



    static const fp4816_t fix4816_zero  = { 0 }; 
    static const fp4816_t fix4816_one   = { 65536 }; // 2^16 = 65536 = 0x10000000000000000    
    static const float fp_rounding      = 0.0005F;

    static const fp4816_t fp_maximum    = { 0x7FFFFFFFFFFFFFFF }; //  9223372036854775807; float ????
    static const fp4816_t fp_minumum    = { 0xFFFFFFFFFFFFFFFF }; //  -9223372036854775807 [note that sprintf(%lld) = -1];  aka float ???
    static const fp4816_t fp_overflow   = { 0x8000000000000000 }; // -9223372036854775808

    static const int64_t maxInteger     = { 140737488355327 };    //  { 0x7FFFFFFFFFFF }  140737488355327 = 140'737'488'355'327
    static const int64_t minInteger     = { -140737488355327 };   // -140737488355327;  FFFFFFFFFFFF0000
    static const fp4816_t fp_maxInteger = { 0x7FFFFFFFFFFF0000 }; //  9223372036854710272 = (longlong) 140737488355327 = 140'737'488'355'327
    static const fp4816_t fp_minInteger = { 0xFFFFFFFFFFFF0000 }; // 9223372036854710272;              -140737488355327

    // ------------- Macros    -----------------------------

    #ifndef NO_OVERFLOW_HANDLING
    #define RETURN_IF_OVERFLOW(value) {  if (a > maxInteger || a < minInteger) return fp_overflow;}
    #define ASSERT_ON_OVERFLOW(value) { assert(a.x != fp_overflow.x); }
    #else
    #define RETURN_IF_OVERFLOW(value) { }
    #define ASSERT_ON_OVERFLOW(value) { }
    #endif

    // ------------- Functions -----------------------------

    // int16 [−32'767, +32'767]
    static inline fp4816_t fp_from_short(short a)   { fp4816_t b; b.x = fix4816_one.x * a; return b; }

    // int16 [−32'767, +32'767] 
    static inline fp4816_t fp_from_int(int a)       { fp4816_t b; b.x = fix4816_one.x * a; return b; }

    // int32 [-2'147'483'648, 2'147'483'647]
    static inline fp4816_t fp_from_long(long a)     { fp4816_t b; b.x = fix4816_one.x * a; return b; }

    // int64 may overflow  [−140'737'488'355'327, +140'737'488'355'327]
    static inline fp4816_t fp_from_longlong(int64_t a)
    {
        RETURN_IF_OVERFLOW(a)
        fp4816_t b; b.x = fix4816_one.x * a; return b;
    }

    // Conversion from float to in64 may have loss of data
    static inline fp4816_t fp_from_float(float a)
    {
        RETURN_IF_OVERFLOW(a)

        double t = (double)a * fix4816_one.x;
    #ifndef FIXMATH_NO_ROUNDING
        t += (t >= 0) ? 0.5f : -0.5f;
    #endif
        fp4816_t b = { t };
        return b;
    }
   
    // Conversion from double to in64 may have loss of data
    static inline fp4816_t fp_from_double(double a)
    {
        RETURN_IF_OVERFLOW(a)

        double t = (double)a * fix4816_one.x;
    #ifndef FIXMATH_NO_ROUNDING // at lowest decimal
        t += (t >= 0) ? 0.5f : -0.5f;
    #endif
        fp4816_t b = { t };
        return b;
    }

    static inline int fp_to_int(fp4816_t a)
    {
    #ifndef FIXMATH_NO_ROUNDING_INT  // at unit level - not decimal ! i.e. 3.6 => 4!
        if (a.x >= 0)
            return (a.x + (fix4816_one.x >> 1)) / fix4816_one.x;
        return (a.x - (fix4816_one.x >> 1)) / fix4816_one.x;
    #else
        return a.x >> 16;
    #endif
    }

    static inline long fp_to_long(fp4816_t a)
    {
    #ifndef FIXMATH_NO_ROUNDING_INT  // at unit level - not decimal ! i.e. 3.6 => 4!
        if (a.x >= 0)
            return (a.x + (fix4816_one.x >> 1)) / fix4816_one.x;
        return (a.x - (fix4816_one.x >> 1)) / fix4816_one.x;
    #else
        return a.x >> 16;
    #endif
    }

    static inline int64_t fp_to_longlong(fp4816_t a)
    {
        ASSERT_ON_OVERFLOW(a)
        return a.x >> 16;
    }


    static inline float fp_to_float(fp4816_t a)
    {
        ASSERT_ON_OVERFLOW(a)
        return (float)a.x / (double) fix4816_one.x;
    }


    static inline double fp_to_double(fp4816_t a)
    {
        ASSERT_ON_OVERFLOW(a);
        return (double)a.x / (double) fix4816_one.x;
    }

    const long VISUALIZATION_FACTOR = 152584; // 152601;  aka around smallest positive decimal which should be 0.0000152587890625
    const long VISUALIZATION_FRACTIONS = 100000;

    static long long ParseFractions(char* format)
    {
        int length, i = strlen(format);

        for (i; i<5; i++)
        //if (length < 5) // fixlut.FRACTIONS_COUNT)
        {
            //format = format.PadRight(fixlut.FRACTIONS_COUNT, '0');
            strcat(format, "0");
        }

        //printf("%s\n", format);

        long long integer = 0;

        //long fractions = long.Parse(format);
        long long fractions = atoll(format);

        fractions = fractions * VISUALIZATION_FRACTIONS / VISUALIZATION_FACTOR;

        while (fractions >= 65536) // fixlut.ONE)
        {
            integer += 65536; // fixlut.ONE;
            fractions -= 65536; // fixlut.ONE;
        }
        
        return integer + fractions;
    }

    static long long ParseInteger(char* format)
    {
        return atoll(format) * 65536; // fixlut.ONE; fix4816_one.x;
    }

    static fp4816_t Parse(char* value)
    {
        if (value == "")
            return fix4816_zero;
        
        //char c = '-'; // value[0];
        //int negative = strcmp(&c,  "-") == 0;
        //printf(" %c\n", value[0]);
        //if (negative == 1)

        int negative = 0;
        if (value[0] == 45) // char value of '-'
        {
            printf("negative");
            negative = 1;
        }
        
        // TODO etc 
        return fix4816_zero;
    }

#ifdef __cplusplus
}
#endif


#ifdef _MSC_VER
#pragma warning(pop)
#endif

// --------------  Implementation  ------------------------

#if defined(CFIXEDPOINT_IMPLEMENTATION) && !defined(CFIXEDPOINT_IMPLEMENTATION_DONE)
    #define CFIXEDPOINT_IMPLEMENTATION_DONE 1


    // Macros


    // Functions



/*

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <string>

#include <float.h>

struct fp
{
    
    friend class constructor;

    struct constructor {
        constructor() {
//             fp::min = 232L;
        }
    };

    static constructor cons;

private:
    const long VISUALIZATION_FACTOR    = 152601L;
    const long VISUALIZATION_FRACTIONS = 100000L;

public:

    fp()
    {

    };

    //    fp sin() const { return fp(1000L); }

    int toString();

    //protected:

    fp(long v)
    {
        value = v;
    }

public:
    long value = 0L;

    static const fp min;
    static const fp max;


public:

    fp& operator= (const fp& rhs) { value = rhs.value; return *this; }
    // fp& operator= (fp&& rhs) noexcept {  value = rhs.value; return *this; }
    // fp& operator= (fp rhs) noexcept { value = rhs.value; return *this; }
            

};

*/


#endif // CFIXEDPOINT_IMPLEMENTATION

#endif // CFIXEDPOINT_H
