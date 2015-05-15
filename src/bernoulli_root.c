#include "bernoulli_root.h" 
#include <string.h> 
/* Find the largest modulo root using Bernoulli's method.
 * The polynomial P(z) is monic, i.e.,
 * P(z) = z^n + a_(n-1)*z^(n-1) + ... + a_0
 * A is an array of length n containing the coefficients of P(z) s.t.
 * A[0] = a_(n-1), ... A[n-1] = a_0
 * n is the n as in the equation above (the order of the polynomial) and it must
 * be greater than 2
 * N is the number of iterations to perform
 * mode can be either BR_SINGLE or BR_PAIR where BR_SINGLE returns the single
 * real root with largest modulus and BR_PAIR returns r^2, the squared modulus
 * of one of the conjugate pair of roots, and 2*r*cos(w), which can be used to
 * find the angle of each root in the pair, into address pointed to by r1 and r2
 * respectively. In the case of BR_SINGLE, r2 is untouched. 
 * returns 0 on success and -1 if an error occurred
 *
 *  *** Not sure if the values for r2 are correct. ***
 */
int bernoulli_root(double *A, int n, int N, double *r1, double *r2, bernoulli_root_mode_t mode)
{
    if (n <= 2) {
        return(-1);
    }
    double X[n+1];
    int k, l;
    memset(X,0,n*sizeof(double));
    X[0] = 1.;
    for (k = 0; k < N; k++) {
        double xk = 0.;
        for (l = n-1; l >= 0; l--) {
            /* Shift over */
            X[l+1] = X[l];
            /* Do calculation */
            xk -= A[l]*X[l];
        }
        X[0]=xk;
    }
    switch (mode) {
        case BR_SINGLE:
            *r1 = X[0]/X[1];
            break;
        case BR_PAIR:
            *r1 = (X[1]*X[1] - X[0]*X[2]) / (X[2]*X[2] - X[1]*X[3]);
            *r2 = (X[0]*X[2] - X[2]*X[1]) / (X[1]*X[3] - X[2]*X[2]);
            break;
    }
    return(0);
}
