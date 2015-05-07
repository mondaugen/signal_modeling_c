/* 
 * RLSPYK_ANALYSIS - RLS predictor in analysis configuration as implemented by
 * Yu and Ko in "Lossless Compression of Digital Audio Using Cascaded RLS-LMS
 * Prediction," IEEE Trans. Speech Audio Processing, Vol. 11, No. 6, November
 * 2003.
 *
 * d is the signal on which prediction is to be performed. d[-k] must be defined
 * for k = [0...p]
 *
 * p is the order of the predictor
 *
 * wn_1 is a vector (array) of length p. These were the last predicted
 * coefficients. On the first iteration set these to 0. wn_1[0] is the
 * coefficient of d[-1], wn_1[1] is the coefficient of d[-2], etc.
 *
 * wn is a vector of length p. These will be the new coefficients. This can
 * point to the same memory as wn_1 but wn_1 will be overwritten.
 *
 * Pn_1 is row-major ordered matrix of size pxp. This was the last covariance
 * matrix. On the first iteration of this algorithm, set Pn_1 = delta*I where
 * delta is some small positive constant (e.g., 0.001) and I is the identity
 * matrix.
 *
 * Pn is the same size as Pn_1 and is where the new covariance matrix will go.
 * This can be at the same address as Pn_1 but Pn_1will be overwritten.
 *
 * e is where the current prediction error will be stored.
 *
 * lambda is the adaptivity coefficient
 */
void rlspyk_analysis(
        double *d,
        int p,
        double *wn_1,
        double *wn,
        double *Pn_1,
        double *Pn,
        double *e,
        double lambda)
{
    /* macro for looking up d: x = d[-1 ... -p] */
#define __x(k) d[-k-1] 
#define __Pn_1(j,k) Pn_1[p*j + k] 
#define __Pn(j,k) Pn[p*j + k] 
    /* temporary variables */
    int n, m;
    double z[p], y;
    /* e = d[0] - wn_1*x */
    *e = 0.;
    for (n = 0; n < p; n++) {
        *e -= wn_1[n]*__x(n);
    }
    *e += d[0];
    /* z = P*x */
    for (n = 0; n < p; n++) {
        z[n] = 0.;
        for (m = 0; m < p; m++) {
            z[n] += __Pn_1(n,m)*__x(m);
        }
    }
    /* y = x^T*P*x */
    y = 0.;
    for (n = 0; n < p; n++) {
        y += __x(n)*z[n];
    }
    /* z = Px/(lambda + y) */
    for (n = 0; n < p; n++) {
        z[n] /= (lambda + y);
    }
    /* wn = wn_1 + e*z; */
    for (n = 0; n < p; n++) {
        wn[n] = wn_1[n] + (*e)*z[n];
    }
    /* y = z*x */
    y = 0.;
    for (n = 0; n < p; n++) {
        y += z[n]*__x(n);
    }
    /* Pn = (Pn_1 - yPn_1)/lambda */
    for (n = 0; n < p; n++) {
        for (m = 0; m < p; m++) {
            __Pn(n,m) = (__Pn_1(n,m) - y*__Pn_1(n,m))/lambda;
        }
    }
#undef __x
#undef __Pn_1
#undef __Pn 
} 
    
