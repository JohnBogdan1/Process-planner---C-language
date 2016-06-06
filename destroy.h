/* Ion Bogdan Ionut - 312CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "planificator.h"

void destroy(ASt stiva)
{
	//pozitionare in varful stivei
    TLG tmp = stiva -> vf, tmp1 = NULL;

	//elimin fiecare informatie cat timp exista
	while (tmp != NULL) {
		tmp1 = tmp;
		tmp = tmp->urm;

		free(tmp1 -> info);
		free(tmp1);

		//reduc dimensiunea stivei
		stiva -> dime--;
	}
	
	stiva -> dime = 0;

	//setez varful stivei la NULL
	stiva -> vf = NULL;

	tmp = NULL;

	//eliberez stiva
	free(stiva);
}

void destroyQ(AQ queue)
{
	//pozitionare in la inceputul cozii
    TLG tmp = queue -> ic, tmp1 = NULL;
	
	//elimin fiecare informatie cat timp exista
	while (tmp != NULL) {
		tmp1 = tmp;
		tmp = tmp -> urm;

		free(tmp1 -> info);
		free(tmp1);

		//reduc dimensiunea cozii
		queue -> dime--;
	}
		
	//setez inceputul si sfarsitul cozii la NULL
	queue -> ic = NULL;
	queue -> sc = NULL;
	queue -> dime = 0;

	tmp = NULL;

	//eliberez coada
	free(queue);
	
}
