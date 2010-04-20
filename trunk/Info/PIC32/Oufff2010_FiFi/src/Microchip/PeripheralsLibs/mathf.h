
/* This file defines the ANSI C floating-point functions.  It is here
   because:
   1)  we need also the single-precision functions, missing from most
       compilers
   2)  some compilers define some ANSI functions wrong
*/
#ifndef __MATHF_H
#define __MATHF_H
 
float acosf(float);	
float asinf(float);
float atanf(float);
float atan2f(float, float);
float ceilf(float);
float cosf(float);
float coshf(float);
float expf(float);
float fabsf(float);
float floorf(float);
float fmodf(float, float);
float frexpf(float, int *);
float ldexpf(float, int);
float logf(float);
float log10f(float);
float modff(float, float *);
float powf(float, float);
float sinf(float);
float sinhf(float);
float sqrtf(float);
float tanf(float);
float tanhf(float);

double acos(double);	
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double cos(double);
double cosh(double);
double exp(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double frexp(double, int *);
double ldexp(double, int);
double log(double);
double log10(double);
double modf(double, double *);
double pow(double, double);
double sin(double);
double sinh(double);
double sqrt(double);
double tan(double);
double tanh(double);

#endif
