#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void daxpy(double *X, double *Y, double *Z, int n, double A);

void cdaxpy(double *X, double *Y, double *Z, int n, double A) {
	int i;
    for (i = 0; i < n; i++) {
        Z[i] = A * X[i] + Y[i];
    }
}

// Allocate and initialize vectors
// Modifies the pointers to allocate memory dynamically, hence the use of **
int initialize_vectors(double **X, double **Y, double **Z, double **cZ, int n) {
    *X = (double *)malloc(n * sizeof(double));
    *Y = (double *)malloc(n * sizeof(double));
    *Z = (double *)malloc(n * sizeof(double));
    *cZ = (double *)malloc(n * sizeof(double));

    if (!(*X) || !(*Y) || !(*Z) || !(*cZ)) {
	    fprintf(stderr, "ERROR.\n");
	
	    if (*X) free(*X);
	    if (*Y) free(*Y);
	    if (*Z) free(*Z);
	    if (*cZ) free(*cZ);
	
	    return -1;
	}

	int i;
    for (i = 0; i < n; i++) {
        (*X)[i] = (double)i;
        (*Y)[i] = (double)(i+10);
    }

    return 0;
}

// Perform a single run of the DAXPY operation
// Receives pointers to the input vectors (X, Y), output vectors (Z, cZ), the scalar A, and vector size n.
double rundaxpy(int n, double A, double *X, double *Y, double *Z, double *cZ, int verify) {
    clock_t start, end;

    // Measure SASM DAXPY execution
    start = clock();
    daxpy(X, Y, Z, n, A);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Verify results - FOR TESTING
    if (verify) {
        cdaxpy(X, Y, cZ, n, A);
		int i;
        for (i = 0; i < n; i++) {
            if (Z[i] != cZ[i]) {
                printf("[Incorrect] index %d: C computed Z[%d]  %.1lf, while SASM computed Z[%d]  %.1lf\n ",
                       i, i, Z[i], i, cZ[i]);
                return duration;
            }
        }
        printf("Results match.\n");
    }

    return duration;
}

int main() {
    int n, verify = 1;
    double *X, *Y, *Z, *cZ;
    double A, pt = 0.0;
    int runs = 30;

    // Vector sizes (2^20, 2^24, 2^28, 2^29) -> "If 230 is impossible, you may
	// reduce it to the point your machine can support (i.e.,  228 or 229)"
    int sizes[] = {1 << 20, 1 << 24, 1 << 28, 1 << 29};

    printf("Select a vector size:\n");
    printf("1) 2^20\n2) 2^24\n3) 2^28\n4) 2^29\nChoose Option(1-4): ");
    int ch;
    if (scanf("%d", &ch) != 1 || ch < 1 || ch > 4) {
        printf("Try Again.\n");
        return -1;
    }
    n = sizes[ch - 1];

    if (initialize_vectors(&X, &Y, &Z, &cZ, n) < 0) {
        return -1;
    }

    // Perform DAXPY operation for 30 runs
    int i;
    for (i = 0; i < runs; i++) {
        printf("Enter the scalar value for run #%d: ", i + 1);
        if (scanf("%lf", &A) != 1) {
            printf("Invalid input for scalar value.\n");
            free(X);
            free(Y);
            free(Z);
            free(cZ);
            return -1;
        }

        // C daxpy comparison and implementation
        double duration = rundaxpy(n, A, X, Y, Z, cZ, verify);
        pt += duration;

        printf("\nFirst 10 results (Z):\n");
        int k = n;
		if (n > 10) {
		    k = 10;
		}
	    int m;	
		for (m = 0; m < k; m++) {
		    printf("Z[%d]  %.1lf\n", m, Z[m]);
		}
		
        printf("Run %d execution time: %.8f seconds\n", i + 1, duration);
        

        // Update vectors for the next run
        int j;
        for (j = 0; j < n; j++) {
            X[j] += 1.0;
            Y[j] += 1.0;
        }
    }

    // Calculate average execution time
    double aet = pt / runs;
    printf("[Average execution time] Vector Size %d     %.8f seconds\n", n, aet);

    free(X); // Allocated memory
    free(Y);
    free(Z);
    free(cZ);

    return 0;
}

