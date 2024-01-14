#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "neon.h"

#define SIZE_ARRAY 2048

void initializeArray_c(int16_t array[], int size);
int sum_c(int16_t tableau[], int taille);

void initializeArray_c(int16_t array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 2;
    }
}

int sum_c(int16_t tableau[], int taille) {
    int somme = 0;

    for (int i = 0; i < taille; i++) {
        somme += tableau[i];
    }

    return somme;
}

int main()
{
	int16_t array_c[SIZE_ARRAY] ;
	int16_t array_neon[SIZE_ARRAY] ;
	XTime Begin_c, End_c, LastCycles_c;
	XTime Begin_neon, End_neon, LastCycles_neon;

	u64 tLastUS;
	int32_t resultSum_c = 0;
	int32_t resultSum_neon = 0;

    init_platform();
	
	
	//C PART
	XTime_GetTime(&Begin_c);
	initializeArray_c(array_c,SIZE_ARRAY);
	resultSum_c =  sum_c(array_c,SIZE_ARRAY);
	
	XTime_GetTime(&End_c);
	LastCycles_c = End_c-Begin_c;
	tLastUS = ( LastCycles_c*1000000 )/COUNTS_PER_SECOND;
	printf("Result sum C: %ld, timestamp = %lld microseconds\n", resultSum_c, tLastUS);
	
	//NEON PART
	XTime_GetTime(&Begin_neon);
	initializeArray_neon(array_neon,SIZE_ARRAY);
	resultSum_neon = sum_neon(array_neon,SIZE_ARRAY);
	
	XTime_GetTime(&End_neon);
	LastCycles_neon = End_neon-Begin_neon;
	tLastUS = ( LastCycles_neon*1000000 )/COUNTS_PER_SECOND;
	
	printf("Result sum neon: %ld, timestamp = %lld microseconds\n", resultSum_neon, tLastUS);;
	
    cleanup_platform();
    return 0;
}