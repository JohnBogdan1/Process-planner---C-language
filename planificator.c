/* Ion Bogdan Ionut - 312CB */

#include "planificator.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//functia de comparare a doua elemente intregi
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

//initializarea stivei
ASt InitS()
{
	ASt S = NULL;

	//aloc memorie
	S = (ASt) malloc( sizeof(TStiva) );

	if(!S)
		return NULL;

	//setez varful si dimensiunea
	S -> vf = NULL;
	S -> dime = 0;

	return S;
}

//functia de introducere in stiva
void Push(ASt S, int id, int prioritate, int pas)
{
	//aloc celula si informatia
	TLG nou = (TLG )malloc( sizeof(TCelulaG) );
	nou -> info = (PS*) malloc( sizeof(PS) );

	( (PS *)(nou -> info) ) -> id = id;
	( (PS *)(nou -> info) ) -> priority = prioritate;
	( (PS *)(nou -> info) ) -> pas = pas;

	//introduc elementul in varful stivei
	nou -> urm = S -> vf;
	S -> vf = nou;

	//incrementez dimensiunea
	S -> dime++;
	
}

//functia de scoatere element din stiva si introducere in coada
int Pop(AQ q, ASt S)
{
	//pozitionare in varful stivei
	TLG sters = S -> vf;

	int x = ( (PS *)(sters -> info) ) -> id;
	int y = ( (PS *)(sters -> info) ) -> priority;
	int z = ( (PS *)(sters -> info) ) -> pas;

	//introduc informatia in coada
	start(q, x, y, z);

	S -> vf = sters -> urm;
	
	//sterg informatia din stiva
	free(sters -> info);
	free(sters);

	S -> dime--;

	return 0;
}

//functia de afisare a stivei
void displayS(ASt stiva, FILE *output) {

	//pozitionare in varful stivei
	TLG tmp = stiva -> vf;

	//parcurg si afisez
	while (tmp != NULL) {
		fprintf(output, "%d ", ( (PS *)(tmp -> info) ) -> id);
		tmp = tmp -> urm;
	}
}

//initializarea cozii
AQ InitQ()
{
	AQ queue = NULL;

	//aloc memorie
	queue = (AQ) malloc(sizeof(TCoada));

	if (!queue)
		return NULL;
	
	//setez inceputul, sfarsitul si dimensiunea cozii
	queue -> ic = queue -> sc = NULL;
	queue -> dime = 0;

	return queue;
}

//functia de introducere in coada a id-ului
void start(AQ queue, int id, int prioritate, int pas)
{
	TLG tmp = NULL, p = NULL, q = NULL, r = NULL, s = NULL;
	int priority, val_pas;

	//aloc memorie pentru celula si informatie
	tmp = (TLG) malloc( sizeof(TCelulaG) );
	tmp -> info = (PS*) malloc( sizeof(PS) );
	

	( (PS *)(tmp -> info) ) -> id = id;
	( (PS *)(tmp -> info) ) -> priority = prioritate;
	( (PS *)(tmp -> info) ) -> pas = pas;
	
	//pozitionare la inceputul cozii
	q = queue->ic;
	s = queue->ic;

	//daca coada e nula
	//sau daca exista un id cu o prioritate mai mica sau egala
	if (q == NULL || prioritate >= ( (PS *)(q -> info) ) -> priority) {

		//daca e nula, introduc informatia la inceput
		if (q == NULL) {
			tmp -> urm = queue -> ic;
			queue -> ic = tmp;
		}

		//daca nu e nula si prioritatea id-ului este mai mica sau egala
		if (q != NULL && prioritate >= ( (PS *)(q -> info) ) -> priority){

			//daca prioritatea id-ului ce trebuie introdus 
			//este egala cu prioritatea id-ului ce exista in coada
			if (prioritate == ( (PS *)(q -> info) ) -> priority) {

				//parcurg coada pana gasesc un id cu o prioritate diferita
				//si un pas mai mare
				//retin id-ul anterior
				while (q != NULL) {

					if (prioritate != ( (PS *)(q -> info) ) -> priority)
						break;
					else if ( pas < ( (PS *)(q -> info) ) -> pas)
						break;

					s = q;
					q = q -> urm;
				}

				//introduc in coada in functie de pas
				if (( (PS *)(s -> info) ) -> pas > pas) {
					tmp -> urm = queue -> ic;
					queue -> ic = tmp;
				} else {
					tmp -> urm = s -> urm;
					s -> urm = tmp;
				}
			//daca prioritatea id-ului ce trebuie introdus in coada
			//este mai mare ca prioritatea id-ului ce exista in coada
			} else {
				tmp -> urm = queue -> ic;
				queue -> ic = tmp;
			}
		}
	//daca coada nu este nula
	} else {
		//pozitionare la inceputul cozii
		p = queue -> ic;
		r = queue -> ic;
		while (p -> urm != NULL) {
			priority = ( (PS *)(p -> urm -> info) ) -> priority;

			if (priority <= prioritate){
				//daca sunt prioritati identice
				if (priority == prioritate){

					//parcurg coada pana gasesc un id cu o prioritate diferita
					//si un pas mai mare
					//retin id-ul anterior
					while(p -> urm != NULL){
						priority = ( (PS *)(p -> urm -> info) ) -> priority;
						val_pas = ( (PS *)(p -> urm -> info) ) -> pas;

						if (priority != prioritate)
							break;
						else if (val_pas > pas)
							break;

						r = p;
						p = p -> urm;
					}

				}
				break;
			}

			p = p -> urm;
		}
		if (r != NULL){
			//daca au aceeasi prioritate
			if (( (PS *)(p -> info) ) -> priority == prioritate) {
				//introduc in coada in functie de pas
				if (( (PS *)(p -> info) ) -> pas < pas) {
					tmp -> urm = p -> urm;
					p -> urm = tmp;
				} else {
					tmp -> urm = r -> urm;
					r -> urm = tmp;
				}
			//daca au prioritati diferite
			} else {
				tmp -> urm = p -> urm;
				p -> urm = tmp;
			}
		}
	}
}

//functia de inserare in coada auxiliara
void PushQ(AQ queue, int id, int prioritate, int pas)
{
	//aloc celula si informatia
	TLG nou = (TLG )malloc( sizeof(TCelulaG) );
	nou -> info = (PS*) malloc( sizeof(PS) );

	( (PS *)(nou -> info) ) -> id = id;
	( (PS *)(nou -> info) ) -> priority = prioritate;
	( (PS *)(nou -> info) ) -> pas = pas;

	//daca varful cozii e NULL, inceputul si sfarsitul coincid
	if(queue -> ic == NULL) {
		queue -> ic = nou;
		queue -> sc = nou;
		queue -> ic -> urm = queue -> sc -> urm = NULL;
	} else {
		//altfel, inserez la sfarsit
		queue -> sc -> urm = nou;
		queue -> sc = nou;
		queue -> sc -> urm = NULL;

}
	//incrementez dimensiunea
	queue -> dime++;

}

//functia de eliminare din coada a id-ului
void end(AQ queue, int id)
{
	//pozitionare la inceputul cozii de priritati
	TLG tmp = queue -> ic, tmp1 = NULL, tmp2 = NULL;

	//initializare coada auxiliara
	AQ aux = InitQ();
	int x, y, z;

	//parcurg coada si extrag de la inceput
	while (tmp) {
		if (( (PS *)(tmp -> info) ) -> id == id){

			//inceputul cozii avanseaza
			queue -> ic = tmp -> urm;
			tmp1 = tmp;
			tmp = tmp -> urm;

			//sterg informatia
			free(tmp1 -> info);
			free(tmp1);

			break;
		} else {

			x = ( (PS *)(tmp -> info) ) -> id;
			y = ( (PS *)(tmp -> info) ) -> priority;
			z = ( (PS *)(tmp -> info) ) -> pas;
			
			//introduc id-ul intr-o coada auxiliara
			PushQ(aux, x, y, z);

			//inceputul cozii avanseaza
			queue -> ic = tmp -> urm;
			tmp1 = tmp;
			tmp = tmp -> urm;

			//sterg informatia
			free(tmp1 -> info);
			free(tmp1);
		}
	}

	//pozitionare la inceputul cozii auxiliare
	TLG tnt = aux -> ic;

	//extrag id-urile din coada auxiliara 
	//le introduc in coada de prioritati
	while (tnt) {
		x = ( (PS *)(tnt -> info) ) -> id;
		y = ( (PS *)(tnt -> info) ) -> priority;
		z = ( (PS *)(tnt -> info) ) -> pas;
		start(queue, x, y, z);

		//inceputul cozii avanseaza
		aux -> ic = tnt -> urm;
		tmp2 = tnt;
		tnt = tnt -> urm;

		//sterg informatia
		free(tmp2 -> info);
		free(tmp2);
		
	}
	
	//distrugere coada auxiliara
	destroyQ(aux);
}

//functia de scoatere id din coada si introducere id in stiva
void *popq(AQ queue, ASt S, int id)
{
	//pozitionare la inceputul cozii
	TLG tmp = queue -> ic, tmp1 = NULL, tmp2 = NULL;

	//initializare coada auxiliara
	AQ aux = InitQ();
	int x, y, z;

	//parcurg coada si extrag de la inceput
	while (tmp) {
		if (( (PS *)(tmp -> info) ) -> id == id){
			x = ( (PS *)(tmp -> info) ) -> id;
			y = ( (PS *)(tmp -> info) ) -> priority;
			z = ( (PS *)(tmp -> info) ) -> pas;

			Push(S, x, y, z);

			//inceputul cozii avanseaza
			queue -> ic = tmp -> urm;
			tmp1 = tmp;
			tmp = tmp -> urm;

			//sterg informatia
			free(tmp1 -> info);
			free(tmp1);

			break;
		} else {

			x = ( (PS *)(tmp -> info) ) -> id;
			y = ( (PS *)(tmp -> info) ) -> priority;
			z = ( (PS *)(tmp -> info) ) -> pas;
			
			//introduc id-ul intr-o coada auxiliara
			PushQ(aux, x, y, z);

			//inceputul cozii avanseaza
			queue -> ic = tmp -> urm;
			tmp1 = tmp;
			tmp = tmp -> urm;

			//sterg informatia
			free(tmp1 -> info);
			free(tmp1);
		}
	}

	//pozitionare la inceputul cozii auxiliare
	TLG tnt = aux -> ic;

	//extrag id-urile din coada auxiliara 
	//le introduc in coada de prioritati
	while (tnt) {
		x = ( (PS *)(tnt -> info) ) -> id;
		y = ( (PS *)(tnt -> info) ) -> priority;
		z = ( (PS *)(tnt -> info) ) -> pas;
		start(queue, x, y, z);

		//inceputul cozii avanseaza
		aux -> ic = tnt -> urm;
		tmp2 = tnt;
		tnt = tnt -> urm;

		//sterg informatia
		free(tmp2 -> info);
		free(tmp2);
		
	}
	
	//distrugere coada auxiliara
	destroyQ(aux);
	
	return 0;
}

//functia de afisare a cozii
void displayQ(AQ queue, FILE *output)
{
	//pozitionare la inceputul cozii
	TLG tmp = queue -> ic;

	//parcurg si afisez
	while (tmp) {
		fprintf(output,"%d ", ( (PS *)(tmp -> info) ) -> id);
		tmp = tmp -> urm;
	}
}
