# G13-MP2-LBYARCHS11

Group Members:
1. Hermione Marucot
2. Sophia Sarreal

PROJECT SPECIFICATION (FIRST ATTEMPT):
![image](https://github.com/user-attachments/assets/42115e3f-b892-4dfc-a014-942d1175fa07)

# i.) Comparative execution time and short analysis of the performance of the kernels

The observation when running the two kernels, **SASM** and **C**, is that the performance when using **2^20** and **2^24** vector sizes are executed within the range of **0.004 to 0.080 seconds**. However, The initial runs show slightly variable execution times, stabilized to **0.006–0.007** **seconds** in later iterations. Meanwhile, when running **2^28** and **2^29**, most runs are executed within a slow range of **40 to 180 seconds**. The vector sizes **2^20** and **2^24** are relatively moderate for the performance test (runs), while the **2^28** and **2^29** vector sizes, execution time arises.

SASM and C kernels produce matching outputs when verified by comparing and matching the Z vector values across all the runs. It also shows that the execution times suggest similar efficiency for the tested workload for SASM and C kernels. Both kernels are accurate and generate similar results for every vector size and scalar multiplication. However, as for the efficiency, both kernels are efficient but are slow when it comes to bigger vector sizes such as **2^28** and **2^29**, revealing a difference in how the kernels scale with increasing data volume.

# ii. and iii.) Take a screenshot of the program output with the correctness check (C and x86-64).
	ii.) Take a screenshot of the program output with the correctness check (C).
	iii.) Take a screenshot of the program output, including the correctness check (x86-64).
![image](https://github.com/user-attachments/assets/d8957238-3203-4fbc-bc36-55f1ca7e0dc0)
![image](https://github.com/user-attachments/assets/06244d96-ab83-4082-b1dd-81e7a7ccf48c)
.
.
.
![image](https://github.com/user-attachments/assets/b2252142-a17d-4138-9a30-2d821b0b3c89)
![image](https://github.com/user-attachments/assets/63cdb031-83ab-4b21-847b-a7bdbe6a41ee)

# To double check SASM and C Results realtime:


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
	
FOR C RESULT CHECKER FOR TESTING (ADD)

	printf("\nResult C:\n");
	int k = n;
		if (n > 10) {
		    k = 10;
		}
	    int h;	
		for (h = 0; h < k; h++) {
		    printf("Z[%d]  %.1lf\n", h, Z[h]);
		}
AND BEFORE

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
