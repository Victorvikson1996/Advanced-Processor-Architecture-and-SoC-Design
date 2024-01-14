#ifndef __NEON_H_
#define __NEON_H_

#define NB_LINES 10
#define NB_COLUMNS 10
#define THRESHOLD 150

void edge_ni(const uint8_t i_MatX[NB_LINES][NB_COLUMNS], uint8_t io_MatResult[NB_LINES][NB_COLUMNS]);

#endif