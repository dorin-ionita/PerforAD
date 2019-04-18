/*        Generated by TAPENADE     (INRIA, Ecuador team)
    Tapenade 3.14 (r7079) -  5 Oct 2018 09:55
*/
#include <adBuffer.h>

/*
  Differentiation of burgers1d in reverse (adjoint) mode:
   gradient     of useful results: *u *u_1
   with respect to varying inputs: *u *u_1
   RW status of diff variables: *u:in-out *u_1:incr
   Plus diff mem management of: u:in u_1:in
*/
void burgers1d_b(double *u, double *ub, double *u_1, double *u_1b, double C, 
        double D, int n) {
    int i;
    float result1;
    float result1b;
    float result2;
    float result2b;
    double tempb;
    double tempb0;
    //#pragma omp for private(i)
    for (i = 1; i < n-1; ++i) {
        pushReal4(result1);
        result1 = fmin(0, u_1[i]);
        pushReal4(result2);
        result2 = fmax(0, u_1[i]);
    }
    for (i = n-2; i > 0; --i) {
        tempb = -(C*ub[i]);
        tempb0 = D*ub[i];
        u_1b[i + 1] = u_1b[i + 1] + tempb0 + result1*tempb;
        u_1b[i] = u_1b[i] + ub[i] - 2.0*tempb0 + (result2-result1)*tempb;
        result1b = (u_1[i+1]-u_1[i])*tempb;
        u_1b[i - 1] = u_1b[i - 1] + tempb0 - result2*tempb;
        result2b = (u_1[i]-u_1[i-1])*tempb;
        adStack_startRepeat();
        popReal4(&result2);
        adStack_resetRepeat();
        adStack_endRepeat();
        fmax_b(0, u_1[i], &(u_1b[i]), result2b);
        popReal4(&result2);
        adStack_startRepeat();
        popReal4(&result1);
        adStack_resetRepeat();
        adStack_endRepeat();
        fmin_b(0, u_1[i], &(u_1b[i]), result1b);
        popReal4(&result1);
    }
}
