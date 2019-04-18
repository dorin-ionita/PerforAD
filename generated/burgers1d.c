
#ifndef TAPENADE
#include <math.h>
#endif
#define Max(x,y) fmax(x,y)
#define Min(x,y) fmin(x,y)
#define Heaviside(x) ((x>=0)?1.0:0.0)

#define u(x) u[x]
#define u_1(x) u_1[x]
void burgers1d(double* u, double* u_1, double C, double D, int n) {
    int i;
    #pragma omp for private(i)
    for ( i=1; i<=n - 2; i++ ) {
        u(i) += -C*((-u_1(i) + u_1(i + 1))*Min(0, u_1(i)) + (u_1(i) - u_1(i - 1))*Max(0, u_1(i))) + D*(-2.0*u_1(i) + u_1(i - 1) + u_1(i + 1)) + u_1(i);
    }
}