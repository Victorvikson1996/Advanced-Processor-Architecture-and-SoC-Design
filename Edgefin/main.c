#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "platform.h"
#include "xtime_l.h"
#include "neon.h"



void edge_c( const uint8_t i_MatX[NB_LINES][NB_COLUMNS], uint8_t io_MatResult[NB_LINES][NB_COLUMNS])
{
	int16_t l_quantity = 0;
	for( uint8_t line = 1; line < NB_LINES-1; line++)
	{	
		for(uint8_t column = 1; column < NB_COLUMNS-1; column++)
		{
			l_quantity =  abs(i_MatX[line][column+1] - i_MatX[line][column-1]) + abs(i_MatX[line-1][column] - i_MatX[line+1][column]);
			io_MatResult[line][column] = (l_quantity >= THRESHOLD)? 1 : 0;
		}
	}
}

void init_matrice(uint8_t X[NB_LINES][NB_COLUMNS], uint8_t Y[NB_LINES][NB_COLUMNS], uint8_t Z[NB_LINES][NB_COLUMNS])
{
	uint8_t l_nb_zero_per_line = NB_COLUMNS-1;
	for( uint8_t line = 0; line < NB_LINES; line++)
	{
		for(uint8_t column = 0; column < NB_COLUMNS; column++)
		{
			X[line][column] = (column <= l_nb_zero_per_line)?0:100;
			Y[line][column] = 0;
			Z[line][column] = 0;
		}
		printf("\n");
		l_nb_zero_per_line--;
	}
}

void print_matrice( uint8_t Res[NB_LINES][NB_COLUMNS])
{
	for( uint8_t line = 0; line < NB_LINES; line++)
	{
		for(uint8_t column = 0; column < NB_COLUMNS; column++)
		{
			printf("%d\t", Res[line][column]);
		}
		printf("\n");
	}
}

int main()
{
	XTime tBegin, tEnd, tLastCycles;
	uint64_t tLastUS;
	uint8_t X[NB_LINES][NB_COLUMNS];
	uint8_t Y[NB_LINES][NB_COLUMNS];
	uint8_t Z[NB_LINES][NB_COLUMNS];
	init_matrice(X, Y, Z);
    
	init_platform();
	printf("\n_______________________________ START _________________________\n");
	
	//C PART
	XTime_GetTime(&tBegin);
	edge_c(X, Y);
	XTime_GetTime(&tEnd);
	tLastCycles = tEnd-tBegin;
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	printf("[C CLASSIC] timestamp = %lld microseconds ==> %lld\n", tLastCycles, tLastUS);
	print_matrice(Y);
	
	//NEON PART
	XTime_GetTime(&tBegin);
	edge_ni(X, Z);
	XTime_GetTime(&tEnd);
	tLastCycles = tEnd-tBegin;
	tLastUS = ( tLastCycles*1000000 )/COUNTS_PER_SECOND;
	printf("[NEON] timestamp = %lld microseconds ==> %lld\n", tLastCycles, tLastUS);
	print_matrice(Z);
    
	cleanup_platform();
    return 0;
}
