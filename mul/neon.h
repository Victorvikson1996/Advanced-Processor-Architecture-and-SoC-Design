#ifndef __NEON_H_
#define __NEON_H_

#define NB_LINES 4
#define NB_COLUMNS 4

void neon_matrix_product(const float *matA, const float *matB, float *matResult);
#endif