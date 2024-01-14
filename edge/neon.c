#include <arm_neon.h>
#include "neon.h"

void edge_ni(const uint8_t i_MatX[NB_LINES][NB_COLUMNS], uint8_t io_MatResult[NB_LINES][NB_COLUMNS]) {

    for (int loop_line = 1; loop_line < NB_LINES - 1; loop_line++) {
        for (int loop_column = 1; loop_column < NB_COLUMNS - 1; loop_column+=8) {
            //On load chaque élément E-W-N-S par colonne de 8
            uint8x8_t W = vld1_u8(&i_MatX[loop_line][loop_column - 1]);
            uint8x8_t E = vld1_u8(&i_MatX[loop_line][loop_column + 1]);
            uint8x8_t N = vld1_u8(&i_MatX[loop_line - 1][loop_column]);
            uint8x8_t S = vld1_u8(&i_MatX[loop_line + 1][loop_column]);

            // Calcul les differences 
            uint8x8_t diff1 = vabd_u8(E, W);
            uint8x8_t diff2 = vabd_u8(N, S); 

            // Ajout des deux différences
            uint8x8_t sum = vadd_u8(diff1, diff2);  // |e-w|+|n-s|

            // Comparaison
            uint8x8_t result = vcge_u8(sum, vdup_n_u8(THRESHOLD));
			// Conversion à 1
			result = vand_u8(result, vdup_n_u8(1));

            vst1_u8(&io_MatResult[loop_line][loop_column], result);
        }
    }
}