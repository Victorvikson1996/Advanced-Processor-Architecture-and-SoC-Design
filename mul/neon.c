#include <arm_neon.h>
#include "neon.h"
#include <stdio.h>
#include <arm_neon.h>


void neon_matrix_product(const float *matA, const float *matB, float *matResult)
{
    float32x4_t col0, col1, col2, col3, result;
    
    col0 = vld1q_f32(matB);
    col1 = vld1q_f32(matB + 4);
    col2 = vld1q_f32(matB + 8);
    col3 = vld1q_f32(matB + 12);

    for (uint8_t loop = 0; loop < 16; loop += 4)
    {
        float32x4_t line = vld1q_f32(matA + loop);
        
        result = vmulq_lane_f32(col0, vget_low_f32(line), 0);
        result = vmlaq_lane_f32(result, col1, vget_low_f32(line), 1);
        result = vmlaq_lane_f32(result, col2, vget_high_f32(line), 0);
        result = vmlaq_lane_f32(result, col3, vget_high_f32(line), 1);

        vst1q_f32(matResult + loop, result);
    }
}

