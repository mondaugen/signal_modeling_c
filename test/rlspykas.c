/* Reads a signal as doubles from stdin and performs RLS predicition on it. The
 * program writes the following to stdout:
 * w0[0], w0[1], ..., w0[p-1], e0, w1[0], ..., w1[p-1], e1, ..., wn[0], ...,
 * wn[p - 1], {en,dn}
 * where n is the length of the input signal.
 * It writes en (the error signal) when doing analysis and dn (the original
 * signal) when doing synthesis.
 */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 
#include "rlspyk.h" 

#define BUFFER_SIZE 8192

#define DELTA 0.001 


int main (int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr,"Arguments are: "
                "%s p lambda mode(0=synthesis,1=analysis)\n",argv[0]);
        return(-1);
    }
    int p, mode, err;
    p = atoi(argv[1]);
    mode = atoi(argv[3]);
    double buf[BUFFER_SIZE+p], *d, lambda;
    lambda = atof(argv[2]);
    memset(buf,0,(BUFFER_SIZE+p)*sizeof(double));
    d = buf + p; /* we need d to be defined for negative indices */
    double wn[p], Pn[p*p], e[BUFFER_SIZE];
    memset(wn,0,sizeof(double)*p);
#define __Pn(j,k) Pn[j*p + k] 
    int j,k;
    for (j = 0; j < p; j++) {
        for (k = 0; k < p; k++) {
            __Pn(j,k) = (j == k) ? DELTA : 0.;
        }
    }
    while(!feof(stdin)) {
        size_t n_items, n;
        switch (mode) {
            case RLSPYK_ANALYSIS:
                n_items = fread(d,sizeof(double),BUFFER_SIZE,stdin);
                break;
            case RLSPYK_SYNTHESIS:
                n_items = fread(e,sizeof(double),BUFFER_SIZE,stdin);
        }
        if (n_items < 0) {
            perror("Reading file");
            return(-1);
        }
        for (n = 0; n < n_items; n++) {
            rlspyk(&d[n],p,wn,wn,Pn,Pn,&e[n],lambda,mode);
            if (fwrite(wn,sizeof(double),p,stdout) < p) {
                perror("Writing file");
                return(-1);
            }
            switch (mode) {
                case RLSPYK_ANALYSIS:
                    err = fwrite(&e[n],sizeof(double),1,stdout);
                    break;
                case RLSPYK_SYNTHESIS:
                    err = fwrite(&d[n],sizeof(double),1,stdout);
            }
            if (err < 1) {
                perror("Writing file");
                return(-1);
            }
        }
        /* Shift last samples to before d */
        memmove(buf,&d[n_items-p],p*sizeof(double));
    }
    return(0);
#undef __Pn 
}
