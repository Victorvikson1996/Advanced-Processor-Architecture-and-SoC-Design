#include <arm_neon.h>
#include "neon.h"
#include <stdio.h>
#include <arm_neon.h>

void initializeArray_neon(int16_t* array ,int size) {
    int16x8_t defaultValue = vdupq_n_s16(2);  // Initialize a 128-bit vector with the default value (e.g., 123)

    for (int i = 0; i < size; i += 8) {
        vst1q_s16(&array[i], defaultValue);  // Store the 128-bit vector into the array
    }
}

int sum_neon(int16_t array[], int size){
	
	int16x4_t vec64a, vec64b; // create two D-register variables each one sequenced by 4*16bits
	int16x8_t target = vdupq_n_s16(0); //create one Q-register sequenced by 8*16bits
	int i;
	int64_t result = 0;
	
	for (i = 0; i < size; i+=8)
	{
		int16x8_t tampon = vld1q_s16(&array[i]);	//A chaque iteration on recupere les 8 elements du tableau (chaque element est sur 16 bits)
		target = vaddq_s16(target,tampon);
		
	}
	
	// target est coupé en 8 paquet de 16 bits :
	vec64a = vget_low_s16(target);	// vget_low_s16 permet de récuperer les 4 paquets de les plus proches du point faibles (=64 bits)
	vec64b = vget_high_s16(target);	//  vget_low_s16 permet de récuperer les 4 paquets de les plus proches du point forts (=64 bits)
	
	vec64a = vadd_s16(vec64a,vec64b);	//On somme les deux vecteurs pour obtenir le resultat dans le D-register vec64a
	
	result += vget_lane_s16(vec64a,0);	// On somme le premier paquet de 16 bits à resultat
	result += vget_lane_s16(vec64a,1);	// On somme le deuxieme paquet de 16 bits à resultat
    result += vget_lane_s16(vec64a,2);	// On somme le deuxieme paquet de 16 bits à resultat
	result += vget_lane_s16(vec64a,3);	// On somme le deuxieme paquet de 16 bits à resultat

	//printf("sum in neon = %lld ",result);
	return result;
}