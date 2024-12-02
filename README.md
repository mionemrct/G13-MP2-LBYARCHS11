# G13-MP2-LBYARCHS11

Group Members:
1. Hermione Marucot
2. Sophia Sarreal

PROJECT SPECIFICATION (FIRST ATTEMPT):
![image](https://github.com/user-attachments/assets/42115e3f-b892-4dfc-a014-942d1175fa07)

To double check SASM Results realtime:


    double rundaxpy(int n, double A, double *X, double *Y, double *Z, double *cZ, int verify) {
    clock_t start, end;
    
    // Measure SASM DAXPY execution
    start = clock();
    daxpy(X, Y, Z, n, A);
    
    
 SASM RESULT CHECKER FOR TESTING (ADD)

    printf("\nResult SASM:\n");
    int k = n;
		if (n > 10) {
		    k = 10;
		}
	    int i;	
		for (i = 0; i < k; i++) {
		    printf("Z[%d]  %.1lf\n", i, Z[i]);
		}
BEFORE
      
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Verify results - FOR TESTING
    if (verify) {
        cdaxpy(X, Y, cZ, n, A);
		int i;
        for (i = 0; i < n; i++) {
            if (Z[i] != cZ[i]) {
                printf("[Incorrect] index %d: C computed Z[%d] = %.1lf, while SASM computed Z[%d] = %.1lf\n ",
                       i, i, Z[i], i, cZ[i]);
                return duration;
            }
        }
        printf("Results match.\n");
    }

    return duration;
    }
