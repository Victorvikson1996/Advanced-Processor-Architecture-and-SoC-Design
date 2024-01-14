#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xtime_l.h"
#include "neon.h"

#define MATRIX_ROWS 4
#define MATRIX_COLS 4

void print_matrix(const float matrix[MATRIX_ROWS][MATRIX_COLS]);
void multiply_matrices_c(float matrix_A[MATRIX_ROWS][MATRIX_COLS], float matrix_B[MATRIX_ROWS][MATRIX_COLS], float result_C[MATRIX_ROWS][MATRIX_COLS]);

int main()
{
    XTime start_time, end_time, elapsed_cycles;
    u64 elapsed_microseconds;
    float matrix_A[MATRIX_ROWS][MATRIX_COLS] = { {1,2,3,4}, {2,3,2,3}, {2,1,3,2}, {2,1,3,2} };                 
    float matrix_B[MATRIX_ROWS][MATRIX_COLS] = { {3,5,4,1}, {2,1,1,3}, {2,3,6,5}, {4,3,2,1} };    
    float result_C[MATRIX_ROWS][MATRIX_COLS];
    float result_neon[MATRIX_ROWS][MATRIX_COLS];
    
    init_platform();
    // C PART
    XTime_GetTime(&start_time);
    multiply_matrices_c(matrix_A, matrix_B, result_C);
    XTime_GetTime(&end_time);
    elapsed_cycles = end_time - start_time;
    elapsed_microseconds = (elapsed_cycles * 1000000) / COUNTS_PER_SECOND;
    printf("Result C, timestamp = %lld microseconds : %lld elapsed cycles\n", elapsed_microseconds, elapsed_cycles);
    print_matrix(result_C);

    // NEON PART
    XTime_GetTime(&start_time);
    neon_matrix_product(matrix_A, matrix_B, result_neon);
    XTime_GetTime(&end_time);
    elapsed_cycles = end_time - start_time;
    elapsed_microseconds = (elapsed_cycles * 1000000) / COUNTS_PER_SECOND;
    printf("Result NEON, timestamp = %lld microseconds : %lld elapsed cycles\n", elapsed_microseconds, elapsed_cycles);
    print_matrix(result_neon);

    cleanup_platform();
    return 0;
}

void print_matrix(const float matrix[MATRIX_ROWS][MATRIX_COLS])
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            printf("%.2f\t", matrix[row][col]);
        }
        printf("\n");
    }
}

void multiply_matrices_c(float matrix_A[MATRIX_ROWS][MATRIX_COLS], float matrix_B[MATRIX_ROWS][MATRIX_COLS], float result_C[MATRIX_ROWS][MATRIX_COLS])
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        for (uint8_t j = 0; j < MATRIX_COLS; j++)
        {        
            result_C[i][j] = matrix_A[i][0] * matrix_B[0][j];
            for (uint8_t k = 1, l = 1; k < MATRIX_COLS; k++, l++)
            {
                result_C[i][j] += matrix_A[i][l] * matrix_B[k][j];
            }
        }
    }
}
