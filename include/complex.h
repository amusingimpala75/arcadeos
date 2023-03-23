#pragma once

/*
Macros and functions that support complex arithematic
 */

#define complex _Complex
#define _Complex_I float _Complex

#define imaginary _Imaginary
#define _Imaginary_I float _Imaginary

#ifdef _Imaginary_I
#define I _Imaginary_I
#else
#define I _Complex_I
#endif

/*
Values are in radians. errno will be set
 */

/* CX_LIMITED_RANGE pragma */

/*
complex arccos of z with branch cuts outside [-1, +1] on the real axis
returns a value unbounded along the imaginary axis, [0, pi] along real axis
 */
double complex cacos(double complex z);
float complex cacosf(float complex z);
long double complex cacosl(long double complex z);

/*
complex arcsin of z with branch cuts outside [-1, +1] on the real axis
returns a value unbounded along the imaginary axis, [-pi/2, +pi/2] along the
real axis
 */
double complex casin(double complex z);
float complex casinf(float complex z);
long double complex casinl(long double complex z);

/*
complex arctan of z with branch cuts outside [-i, +i] along the imaginary axis
returns a value unbounded along the imaginary axis, [=pi/2, +pi/2] along the
real axis
 */
double complex catan(double complex z);
float complex catanf(float complex z);
long double complex catanl(long double complex z);

/* complex cos of z */
double complex ccos(double complex z);
float complex ccosf(float complex z);
long double complex ccosl(long double complex z);

/* complex sin of z */
double complex csin(double complex z);
float complex csinf(float complex z);
long double complex csinl(long double complex z);

/* complex tan of z */
double complex ctan(double complex z);
float complex ctanf(float complex z);
long double complex ctanl(long double complex z);

/*
complex arc hyperbolic cos of z with branch cut < 1 along real axis
returns a value half-strip nonnegative along real axis, [-ipi, +ipi] along
imaginary axis
 */
double complex cacosh(double complex z);
float complex cacoshf(float complex z);
long double complex cacoshl(long double complex z);

/*
complex arc hyperbolic sin of z with branch cuts outside [-i, +i] along
imaginary axis
returns a value unbounded along real axis, [-ipi/2, +ipi/2] along
imaginary axis
 */
double complex casinh(double complex z);
float complex casinhf(float complex z);
long double complex casinhl(long double complex z);

/*
complex arc hyperbolic tan of z with branch cuts outside [-1, +1] along real
axis
returns value unbounded along real axis, [i-pi/2, +ipi/2] along imaginary axis
 */
double complex catanh(double complex z);
float complex catanhf(float complex z);
long double complex catanhl(long double complex z);

/* complex hyperbolic cos of z */
double complex ccosh(double complex z);
float complex ccoshf(float complex z);
long double complex ccoshl(long double complex z);

/* complex hyperbolic sin of z */
double complex csinh(double complex z);
float complex csinhf(float complex z);
long double complex csinhl(long double complex z);

/* complex hyperbolic tan of z */
double complex ctanh(double complex z);
float complex ctanhf(float complex z);
long double complex ctanhl(long double complex z);

/* complex base-e exponential of z */
double complex cexp(double complex z);
float complex cexpf(float complex z);
long double complex cexpl(long double complex z);

/*
complex natural log of z with branch cut along negative real axis
returns a value unbounded along real axis, [-ipi, +ipi] along imaginary axis
 */
double complex clog(double complex z);
float complex clogf(float complex z);
long double complex clogl(long double complex z);

/* complex abs of z */
double cabs(double complex z);
float cabsf(float complex z);
long double cabsl(long double complex z);

/* complex pow x^y with branch cut (x) along negative real axis */
double complex cpow(double complex x, double complex y);
float complex cpowf(float complex x, float complex y);
long double complex cpowl(long double complex x, long double complex y);

/*
complex sqrt z with branch cut along negative real axis
returns value along right-half plane, including imaginary axis
 */
double complex csqrt(double complex z);
float complex csqrtf(float complex z);
long double complex csqrtl(long double complex z);

/*
argument/phase of z with branch cut along negative real axis
returns a value [-pi, +pi]
 */
double carg(double complex z);
float cargf(float complex z);
long double cargl(long double complex z);

/* imgainary part of z */
double cimg(double complex z);
float cimgf(float complex z);
long double cimgl(long double complex z);

/* converts x, y into imaginary number with real of x, imaginary of y */
#define CMPLX(x, y) ((double complex)((double)(x) + _Imaginary_I * (double)(y)))
#define CMPLXF(x, y) ((float complex)((float)(x) + _Imaginary_I * (float)(y)))
#define CMPLXL(x, y)                                                           \
  ((long double complex)((long double)(x) + _Imaginary_I * (long double)(y)))

/* complex conjugate of z, negating sign of imaginary part */
double complex conj(double complex z);
float complex conjf(float complex z);
long double complex conjl(long double complex z);

/* projection onto Reimann sphere */
double complex cproj(double complex z);
float complex cprojf(float complex z);
long double complex cprojl(long double complex z);

/* real part of z */
double creal(double complex z);
float crealf(float complex z);
long double creall(long double complex z);
