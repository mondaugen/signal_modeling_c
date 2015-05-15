#include <stdlib.h> 
#include <stdio.h> 
#include "bernoulli_root.h" 

#define MAX_ORDER 100 

int main (int argc, char **argv)
{
    if ((argc < 4) || ((argc-3) > MAX_ORDER)) {
        fprintf(stderr,
                "Usage:\n%s number-of-iterations mode a(n-1) a(n-2) ... a(0)\n"
                "p can be maximum %d\n", argv[0], MAX_ORDER);
        return(-1);
    }
    int P = 0, N;
    double A[MAX_ORDER], r1, r2;
    bernoulli_root_mode_t mode;
    N = atoi(argv[1]);
    mode = atoi(argv[2]);
    while (argv[P+3]) {
        A[P] = atof(argv[P+3]);
        P++;
    }
    if (bernoulli_root(A, P, N, &r1, &r2, mode)) {
        fprintf(stderr,"Error computing root.\n");
        return(-1);
    }
    switch (mode) {
        case 0:
            printf("%g\n",r1);
            break;
        case 1:
            printf("%g %g\n",r1,r2);
            break;
    }
    return(0);
}

