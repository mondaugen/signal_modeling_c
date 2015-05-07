#ifndef RLSPYK_H
#define RLSPYK_H 

typedef enum {
    RLSPYK_SYNTHESIS = 0,
    RLSPYK_ANALYSIS
} rlspyk_mode_t;

void rlspyk(
        double *d,
        int p,
        double *wn_1,
        double *wn,
        double *Pn_1,
        double *Pn,
        double *e,
        double lambda,
        rlspyk_mode_t mode);

#endif /* RLSPYK_H */
