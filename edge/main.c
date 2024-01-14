#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "platform.h"
#include "xtime_l.h"
#include "neon.h"



void edge_c( const uint8_t i_MatX[NB_LINES][NB_COLUMNS], uint8_t io_MatResult[NB_LINES][NB_COLUMNS])
{
	int16_t l_quantity = 0;
	for( uint8_t loop_line = 1; loop_line < NB_LINES-1; loop_line++)
	{	
		for(uint8_t loop_column = 1; loop_column < NB_COLUMNS-1; loop_column++)
		{
			l_quantity =  abs(i_MatX[loop_line][loop_column+1] - i_MatX[loop_line][loop_column-1]) + abs(i_MatX[loop_line-1][loop_column] - i_MatX[loop_line+1][loop_column]);
			if(l_quantity >= THRESHOLD) {
				io_MatResult[loop_line][loop_column] = 1;
			}
			else {
				io_MatResult[loop_line][loop_column] = 0;
			}
		}
	}
}

void init_mat(uint8_t i_MatX[NB_LINES][NB_COLUMNS], uint8_t i_MatY[NB_LINES][NB_COLUMNS], uint8_t i_MatZ[NB_LINES][NB_COLUMNS])
{
	uint8_t triangular_zero = 0;
	for( uint8_t loop_line = 0; loop_line < NB_LINES; loop_line++)
	{
		for(uint8_t loop_column = 0; loop_column < NB_COLUMNS; loop_column++)
		{
			if(loop_column <= triangular_zero) {
				i_MatX[loop_line][loop_column] = 0;
			}
			else {
				i_MatX[loop_line][loop_column] = 100;
			}
			i_MatY[loop_line][loop_column] = 0;
			i_MatZ[loop_line][loop_column] = 0;		
		}
		printf("\n");
		triangular_zero++;
	}
}

void print_mat( uint8_t i_MatRes[NB_LINES][NB_COLUMNS])
{
	for( uint8_t loop_line = 0; loop_line < NB_LINES; loop_line++)
	{
		for(uint8_t loop_column = 0; loop_column < NB_COLUMNS; loop_column++)
		{
			printf("%d\t", i_MatRes[loop_line][loop_column]);
		}
		printf("\n");
	}
}

int main()
{
	XTime tBegin, tEnd, tLastCycles;
	uint64_t tLastUS;
	uint8_t l_matX[NB_LINES][NB_COLUMNS];
	uint8_t l_matY[NB_LINES][NB_COLUMNS];
	uint8_t l_matZ[NB_LINES][NB_COLUMNS];
	init_mat(l_matX, l_matY, l_matZ);
    
	init_platform();
	
	//C PART
	XTime_GetTime(&tBegin);
	edge_c(l_matX, l_matY);
	XTime_GetTime(&tEnd);
	tLastCycles = tEnd-tBegin;
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	printf("EDGE IN C timestamp = %lld microseconds :  %lld elapsed cycle\n", tLastCycles, tLastUS);
	print_mat(l_matY);
	
	//NEON PART
	XTime_GetTime(&tBegin);
	edge_ni(l_matX, l_matZ);
	XTime_GetTime(&tEnd);
	tLastCycles = tEnd-tBegin;
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	printf("EDGE IN NEON timestamp = %lld microseconds :  %lld elapsed cycle\n", tLastCycles, tLastUS);
	print_mat(l_matZ);
    
	cleanup_platform();
    return 0;
}
