#include "CFixedPoint.h"
#include <stdio.h>

//using namespace cfp;

int main()
{
 //   fp4816_t fp;

    /*
    
     32768              0.5   1000000000000000
                        1    10000000000000000
     65536 * 3   = 196608   110000000000000000
           * 3.5 = 229376   111000000000000000

     65536 * 5.336 = 349700.096  55604   1010101011000000100
 
 */


 //   printf("%i\n", fp.toString());
 //   printf("%i\n", cfp->min);
 //   printf("LongMin= %i\n", fp.min.value);
 //   printf("LongMax=  %i\n", fp.max.value);

    printf("One: x: %llx d: %lld\n", fix4816_one.x, fix4816_one.x);

    fp4816_t fp = fp_from_int(5);
    printf(" 5 * 1 = %llx  %lld\n", fp.x, fp.x);    // 50000  327680

    int out = fp_to_int(fp);
    printf(" int: %d\n", out);  // 5

    fp = fp_from_int(-5);
    printf(" -5 * 1 = %llx  %lld\n", fp.x, fp.x); // FFFFFFFFFFFB0000  -327680

    out = fp_to_int(fp);
    printf(" int: %d\n", out);  // -5

    fp = fp_from_float(5.336f);
    printf("float 5.336: %llx  %lld\n", fp.x, fp.x);    // 38000  229376   0x111000000000000000

    out = fp_to_int(fp);
    printf("float 5.336 to int: %d\n", out);  // 5

    fp = fp_from_float(5.536f);
    out = fp_to_int(fp);
    printf("float: 5.536 = %d\n", out);  // 6

    fp = fp_from_long(2147483647); // max value
    out = fp_to_long(fp);
    printf("long 2147483647 = %d\n", out);

    fp = fp_from_long(-2147483648); // min value
    out = fp_to_long(fp);
    printf("long -2147483648 = %d\n", out);

    _int64 ll = 0;
    fp = fp_from_longlong(-140737488355327);
    ll = fp_to_longlong(fp);
    printf("long -140737488355327 = %lld\n", ll);

    fp = fp_from_longlong(140737488355327);
    ll = fp_to_longlong(fp);
    printf("long 140737488355327 = %lld\n", ll);

    fp = fp_from_longlong(fp_overflow.x);
    if (fp.x == fp_overflow.x)
        printf("  overflow!\n");

    // Will assert if NO_OVERFLOW_HANDLING not defined
    // ll = fp_to_longlong(fp);
    // printf("long overflow = %lld\n", ll);

    fp4816_t b; 
    b.x = fix4816_one.x * -140737488355327;  // b.x = -9223372036854710272 = 7FFFFFFFFFFF0000

    printf("...\n");
    double c = -140737488355327;
    fp = fp_from_double(c);
    printf("float -140737488355327: %llx  %lld\n", fp.x, fp.x);
    c = fp_to_double(fp);
    printf(" double %f \n", c);

    c = 150000000000000;
    fp = fp_from_double(c); // return overflow
    printf("float 150000000000000 will overflow: %llx  %lld\n", fp.x, fp.x);
    // Will assert
    // c = fp_to_double(fp);
    // printf(" double %f \n", c);

    fp = fp_from_float(-14073748835532.65432);
    printf("\nfloat -140737488355327: %llx  %lld\n", fp.x, fp.x);
    fp.x = 9223372036854775806;
    c = fp_to_float(fp);
    printf(" float %f \n", c);


//    fp = fp_from_double(-140737488355326.5432);
    fp = fp_from_double(-14073748835532.65432);
    printf("\ndouble -140737488355327: %llx  %lld\n", fp.x, fp.x);
    fp.x = 9223372036854775806;
    c = fp_to_double(fp);
    printf(" double %f \n", c);

    fp = fp_from_double(123.54);
    printf("\ndouble 123.54: %llx  %lld\n", fp.x, fp.x);
    c = fp_to_double(fp);
    printf(" double %f \n", c);

    char str[10] = "456";

    long long val = ParseFractions(str);
    printf(" val 456 = %lld\n", val);
    c = val * 0.0000152588;
    printf(" .456 %f \n", c);


    char str2[10] = "-2323";
 // todo   fp = Parse(str2);
    c = fp_to_double(fp);
 //   printf("\n double %f \n", c);


    int i = getchar();
    return 0;
}