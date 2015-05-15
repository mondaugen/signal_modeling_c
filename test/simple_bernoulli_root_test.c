#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
    if (argc != 2) {
        return(-1);
    }
    int n = 2;
    double A[] = {-501., 500},
           X[] = {1., 0};
    int I = atoi(argv[1]),
        k, l;
    for (k = 0; k < I; k++) {
        double xk = 0.;
        for (l = n-1; l > 0; l--) {
            xk -= A[l]*X[l];
            X[l] = X[l-1];
        }
        xk -= A[0]*X[0];
        X[0]=xk;
    }
    printf("%g\n",X[0]/X[1]);
}
