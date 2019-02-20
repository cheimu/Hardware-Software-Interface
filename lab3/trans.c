/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */


void transpose_32_32(int M, int N, int A[M][N], int B[N][M]) {
   int temp0 = 0;
   int temp1 = 0;
   int temp2 = 0;
   int temp3 = 0;
   int temp4 = 0;
   int temp5 = 0;
   int temp6 = 0;
   int temp7 = 0;
   for (int i = 0; i < M; i+=8) {
      for (int j = 0; j < N; j+=8) {
         for (int k = i; k < i+8; k++) {
            temp0 = A[k][j+0];
            temp1 = A[k][j+1];
            temp2 = A[k][j+2];
            temp3 = A[k][j+3];
            temp4 = A[k][j+4];
            temp5 = A[k][j+5];
            temp6 = A[k][j+6];
            temp7 = A[k][j+7]; 
            B[j+0][k] = temp0;
            B[j+1][k] = temp1;
            B[j+2][k] = temp2;
            B[j+3][k] = temp3;
            B[j+4][k] = temp4;
            B[j+5][k] = temp5;
            B[j+6][k] = temp6;
            B[j+7][k] = temp7;
         }
      }
   }
}

void transpose_64_64(int M, int N, int A[M][N], int B[N][M]) {
   int temp0 = 0;
   int temp1 = 0;
   int temp2 = 0;
   int temp3 = 0;
   for (int i = 0; i < 64; i+=4) {
      for (int j = 0; j < 64; j+=4) {
         for (int k = i; k < i+4; k++) {
            temp0 = A[k][j+0];
            temp1 = A[k][j+1];
            temp2 = A[k][j+2];
            temp3 = A[k][j+3];
            B[j+0][k] = temp0;
            B[j+1][k] = temp1;
            B[j+2][k] = temp2;
            B[j+3][k]= temp3;
         }
      }
   }
}

void transpose_67_61(int M, int N, int A[M][N], int B[N][M]) {
   int temp = 0;
   int diag = 0;
   for (int i = 0; i < 61; i+=16) {
      for (int j = 0; j < 67; j+=16) {
         for (int k = j; k < M && k < j + 16; k++) {
	    for (int l = i; l < N && l < i + 16; l++) {
               if (k == l) {
                 temp = A[k][l];
                 diag = 1;
               } else {
                 B[l][k] = A[k][l];
               }
	    }
            if (diag) {
               B[k][k] = temp;
               diag = 0;
            }
         }
      }
   }
}

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M])
{
   if (M == 32 && N == 32) {
      transpose_32_32(M, N, A, B);
   } else if (M == 64) {
      transpose_64_64(M, N, A, B);
   } else {
      transpose_67_61(M, N, A, B);
   }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M])
{
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M])
{
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

