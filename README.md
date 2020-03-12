
C Fixed Point  [WIP]


C fixed point math library  : 64bit Q48.18 


type        min()                       max()
------------------------------------------------------------------- 
char        -128                        128
uchar       0                           255
short       -32,768                     32,767
ushort      0                           65535
wchar_t     0                           65535
int         -2147483648                 2147483647
uint        0                           4,294,967,295
long        -2,147,483,648              2,147,483,647
ulong       0                           4,294,967,295
longlong    -9,223,372,036,854,775,808  9,223,372,036,854,775,807
ulonglong   0                           18,446,744,073,709,551,615
float       1.17549e-38                 3.40282e+38
double      2.22507e-308                1.79769e+308

    static const fp4816_t fix4816_one   = { 65536 }; // 2^16 = 65536 = 0x10000000000000000    
    static const float fp_rounding      = 0.0005F;

    static const fp4816_t fp_maximum    = { 0x7FFFFFFFFFFFFFFF }; //  9223372036854775807; float ????
    static const fp4816_t fp_minumum    = { 0xFFFFFFFFFFFFFFFF }; //  -9223372036854775807 [note that sprintf(%lld) = -1];  aka float ???
    static const fp4816_t fp_overflow   = { 0x8000000000000000 }; // -9223372036854775808

    static const int64_t maxInteger     = { 140737488355327 };    //  { 0x7FFFFFFFFFFF }  140737488355327 = 140'737'488'355'327
    static const int64_t minInteger     = { -140737488355327 };   // -140737488355327;  FFFFFFFFFFFF0000
    static const fp4816_t fp_maxInteger = { 0x7FFFFFFFFFFF0000 }; //  9223372036854710272 = (longlong) 140737488355327 = 140'737'488'355'327
    static const fp4816_t fp_minInteger = { 0xFFFFFFFFFFFF0000 }; // 9223372036854710272; 


References


+++++ https://github.com/RomanZhu/FixedPoint-Sharp/blob/master/FixedPointSharp/fixnum/fp.cs

https://en.wikipedia.org/wiki/Bitwise_operations_in_C
https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/bitwise-and-shift-operators


+++ https://github.com/RomanZhu/FixedPoint-Sharp
+++ https://github.com/MikeLankamp/fpm

++++ https://www.coranac.com/tonc/text/fixed.htm
https://en.wikichip.org/w/images/d/db/Intrinsity_FixedPoint.pdf
https://hal-lirmm.ccsd.cnrs.fr/lirmm-01277362/file/EJCIM2013.pdf


+++ https://github.com/PetteriAimonen/libfixmath/tree/master/libfixmath 
    https://github.com/PetteriAimonen/libfixmath/blob/master/libfixmath/fix16.h
    https://en.wikipedia.org/wiki/Libfixmath


https://github.com/asik/FixedMath.Net/tree/master/src
https://github.com/nxrighthere/RioSockets/blob/master/Source/riosockets.h
https://www.allaboutcircuits.com/technical-articles/fixed-point-representation-the-q-format-and-addition-examples/

- Math and floating-point support
  https://docs.microsoft.com/en-us/cpp/c-runtime-library/floating-point-support?view=vs-2019


+++ static tutorial - very good!
  https://www.bogotobogo.com/cplusplus/statics.php



 ------------ TODOs ---------------------

 - Consider using  https://en.wikipedia.org/wiki/Rounding#Round_half_to_even


