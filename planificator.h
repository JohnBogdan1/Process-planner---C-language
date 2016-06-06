/* Ion Bogdan Ionut - 312CB */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef _PLANIFICATOR_
#define _PLANIFICATOR_

//structura listei generice
typedef struct celula
{
	struct celula* urm;
	void* info;
} TCelulaG, *TLG;

//structura stivei
typedef struct stiva
{
	size_t dime;
	TLG vf;
} TStiva, *ASt;

//declarari de functii
int cmpfunc (const void * a, const void * b);
ASt InitS();
void Push(ASt S, int id, int prioritate, int pas);
void displayS(ASt stiva, FILE *output);
void destroy(ASt stiva);

//structura cozii
typedef struct coada
{
	size_t dime;
	TLG ic, sc;

} TCoada, *AQ;

//declarari de functii
AQ InitQ();
void start(AQ queue, int id, int prioritate, int pas);
void end(AQ queue, int id);
void destroyQ(AQ queue);
void displayQ(AQ queue, FILE *output);
int Pop(AQ q, ASt S);
void *popq(AQ queue, ASt S, int id);
void PushQ(AQ queue, int id, int prioritate, int pas);

//structura cu informatii despre id, prioritate si pas
typedef struct
{
	int id, priority, pas;

} PS;


#endif
