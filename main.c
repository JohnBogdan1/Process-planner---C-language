/* Ion Bogdan Ionut - 312CB */

#include "planificator.h"
#include "destroy.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>




int main (int argc, char *argv[]) {

	AQ q = NULL;

	//initializez coada
	q = InitQ (sizeof(PS));
	if (!q) {destroyQ(q); return 1;}

	FILE *input = NULL, *output = NULL;
	if (argc != 3) {
		printf("Please, input three arguments!\n");
		return 1;
	}
	
	//deschid fisierele
	input = fopen( argv[1], "r" );

	if (input == NULL) {
		printf("\nCould not open file");
	}

	output = fopen( argv[2], "w" );
	
	if (output == NULL) {
		printf("\nCould not open file");
	}


	//nr_ev este numarul de evenimente
	//j, m sunt variabile auxiliare
	//nr_el reprezinta numarul de elemente din vector la un moment dat
	//dar fara duplicate in el
	int nr_ev, j, m, nr_el = 0;

	//citesc din fisierul de input numarul de evenimente
	//declar vectorul in care voi pune fiecare eveniment 
	fscanf(input,"%d", &nr_ev);
	int array[nr_ev];

	//declar un vector de stive
	ASt *s = malloc(sizeof(ASt*) * nr_ev);
	
	//initializez stivele
	for (j = 0; j < nr_ev; j++) {
		s[j] = InitS();

		if(!s[j]) {
			destroy(s[j]);
			return 0;
		}
			
	}

	//retin in variabilele a, b, c continutul fiecarei linii din in fisier
	//parcurg linie cu linie
	//pas reprezinta momentul de timp la care a fost pornit procesul
	//nr este pasul pe care il afisez in fisier
	char a[20];
	int i, b, c, nr = 1, pas = 1, k = 0;


	//citesc actiunile din fisier
	while (fscanf(input, "%s", a) == 1) {

		if (!strcmp(a, "start")) {

			fprintf(output, "%d\n", nr);

			//citesc id-ul si prioritatea
			fscanf(input," %d %d", &b, &c);

			//adaug in coada informatiile
			start(q, b, c, pas);

			//afisez coada
			displayQ(q, output);

			fprintf(output, "\n");

			//afisez stivele existente
			for (i = 0; i < nr_el; i++) {
					fprintf(output, "%d: ", array[i]);
					displayS(s[array[i]], output);
					fprintf(output, "\n");
				
			}

			fprintf(output,"\n");

			//incrementez pasul pentru procese
			//incrementezpasul pe care il afisez in fisier
			pas++;
			nr++;
		}
		if (!strcmp(a, "wait")){

			fprintf(output, "%d\n", nr);
			fscanf(input, " %d %d", &b, &c);

			//reactualizez numarul de elemente din vector
			//pentru ca atunci cand se executa comanda event
			//se elimina un element din vector
			k = nr_el;

			//adaug in vector evenimentul
			array[k++] = b;

			int n = 0;

			//elimin duplicatul din vector
			for (i = 0; i < k; i++) {
				for (m = i + 1; m < k;) {
					if (array[m] == array[i]) {
						for (n = m; n < k; n++) {
							array[n] = array[n + 1];
						}
						k--;
					} else
						m++;
					}
			}

			//sortez elementele din vector
			qsort(array, k, sizeof(int), cmpfunc);

			//scot elementul(id-ul) din coada si il introduc in stiva
			popq(q, s[b], c);

			//afisez coada
			displayQ(q, output);
			fprintf(output, "\n");

			//reactualizez numarul de elemente din vector
			//dupa eliminarea duplicatului
			nr_el = k;

			//afisez stivele existente
			for (i = 0; i < nr_el; i++) {
					fprintf(output, "%d: ", array[i]);
					displayS(s[array[i]], output);
					fprintf(output, "\n");
				
			}

			fprintf(output,"\n");
			nr++;
		}
		if (!strcmp(a, "event")) {

			fprintf(output, "%d\n", nr);
			fscanf(input, "%d", &b);

			//scot id-urile din stiva evenimentului respectiv
			//introduc id-urile in coada
			while(s[b] -> dime != 0 && s[b] != NULL)
				Pop(q, s[b]);

			//afisez coada
			displayQ(q,output);
			fprintf(output,"\n");

			//elimin elementul(evenimentul) din vector
			for(i = 0; i < nr_el; i++) {
				if (array[i] == b) {
					for(j = i; j < nr_el; j++)
						array[j] = array[j + 1];
					nr_el--;
					i--;
				}
			}

			//afisez stivele existente
			for (i = 0; i < nr_el; i++) {
					fprintf(output, "%d: ", array[i]);
					displayS(s[array[i]], output);
					fprintf(output, "\n");
				
			}
			fprintf(output, "\n");
			nr++;
		}
		if (!strcmp(a, "end")) {

			fprintf(output, "%d\n", nr);
			fscanf(input, "%d", &b);

			//elimin id-ul din coada
			end(q, b);

			//afisez coada
			displayQ(q, output);

			fprintf(output, "\n");

			//afisez stivele existente
			for (i = 0; i < nr_el; i++) {
					fprintf(output, "%d: ", array[i]);
					displayS(s[array[i]], output);
					fprintf(output, "\n");
				
			}

			fprintf(output, "\n");
			nr++;
		}
	}

	//distrug stivele
	for (j = 0; j < nr_ev; j++){
		destroy(s[j]);
	}

	//eliberez vectorul de stive
	free(s);

	//distrug coada
	destroyQ(q);
	
	//inchid fisierele
	fclose(input);
	fclose(output);
	
	return 0;
}
