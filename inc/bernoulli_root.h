#ifndef BERNOULLI_ROOT_H
#define BERNOULLI_ROOT_H 
typedef enum {
    BR_SINGLE = 0,
    BR_PAIR
} bernoulli_root_mode_t;

int bernoulli_root(double *A, int P, int N, double *r1, double *r2, bernoulli_root_mode_t mode);
#endif /* BERNOULLI_ROOT_H */
