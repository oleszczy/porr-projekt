#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100
#define MINCF		0
#define ASN		1

int read_network(char *filename, int *source, int *tail, int *nodes, int *arcs, int (*nettab)[2])
{
	int type;				//typ sieci (MIN - min cost flow, ASN - assignment)
	char *res, str[100], c;
	int i, j, tmp, tmp1, tmp2, tmp3, tmp4;
	FILE *f;

	if((f = fopen(filename, "r")) == NULL) {		//filename - plik wejsciowy
		printf("Nie mozna otworzyc pliku.\n");
		exit(1);
	}

	while(1) {
		if((fscanf(f, "%c", &c)) == 0) {
			printf("Nie mozna odczytac znaku.\n");
			exit(1);
		}
		if(c != 'c') {
			break;
		}
		if((res = fgets(str, MAX_LINE_LENGTH, f)) == NULL) {
			printf("Nie mozna odczytac linii.\n");
			exit(1);
		}
	}

	if(c != 'p') {
		printf("Nie rozpoznano znaku poczatku linii.\n");
		exit(1);
	}

	if((fscanf(f, "%s %d %d\n", str, nodes, arcs)) == 0) {
		printf("Nie mozna odczytac parametrow sieci\n");
		exit(1);
	}

	if(strcmp(str, "min") == 0) {
		type = MINCF;
	}
	else if(strcmp(str, "asn") == 0) {
		type = ASN;
	}
	else {							//zalozenie: siec musi byc typu assignment lub min cost flow
		printf("Niewlasciwy typ sieci.\n");
		exit(1);
	}
	
	printf("%d\n", (*arcs)+(*nodes));
	//nettab = (int (*)[2])malloc(((*arcs)+(*nodes))*2*sizeof(int));		//przydzial pamieci dla tablicy z grafem
	
	if((fscanf(f, "%c %d", &c, &tmp)) == 0) {
		printf("Nie mozna odczytac znaku 2.\n");
		exit(1);
	}

	if(c != 'n') {
		printf("Nie rozpoznano znaku poczatku linii.\n");
		exit(1);
	}

	*source = tmp;

	if((res = fgets(str, MAX_LINE_LENGTH, f)) == NULL) {
		printf("Nie mozna odczytac linii 2.\n");
		exit(1);
	}

	if((fscanf(f, "%c %d", &c, &tmp)) == 0) {
		printf("Nie mozna odczytac znaku 2.\n");
		exit(1);
	}

	if(c != 'n') {
		printf("Nie rozpoznano znaku poczatku linii.\n");
		exit(1);
	}

	*tail = tmp - 1;

	if((res = fgets(str, MAX_LINE_LENGTH, f)) == NULL) {
		printf("Nie mozna odczytac linii 2.\n");
		exit(1);
	}

	if((fscanf(f, "%c %d", &c, &tmp)) == 0) {
		printf("Nie mozna odczytac znaku 2.\n");
		exit(1);
	}

	if(c != 'a') {
		printf("Nie rozpoznano znaku poczatku linii.\n");
		exit(1);
	}

	nettab[0][0] = 0;
	nettab[0][1] = tmp;
	
	if(type == MINCF) {
		if((fscanf(f, " %d %d %d %d", &tmp, &tmp1, &tmp2, &tmp3)) == 0) {
			printf("Nie mozna odczytac znaku 3.\n");
			exit(1);
		}
	}
	else if(type == ASN) {
		if((fscanf(f, " %d %d", &tmp, &tmp1)) == 0) {
			printf("Nie mozna odczytac znaku 3.\n");
			exit(1);
		}
	}
	
	nettab[1][0] = tmp;
	nettab[1][1] = tmp1;

	for(i = 1, j = 1; i + j < (*arcs) + (*nodes); i++) {
		if((res = fgets(str, MAX_LINE_LENGTH, f)) == NULL) {
			printf("Nie mozna odczytac linii 3.\n");
			exit(1);
		}
		if((fscanf(f, "%c ", &c)) == 0) {
			printf("Nie mozna odczytac znaku 4.\n");
			exit(1);
		}
		else if(c != 'a') {
			break;
		}
		//printf("%c ", c);
		if(type == MINCF) {
			if((fscanf(f, "%d %d %d %d %d", &tmp, &tmp1, &tmp2, &tmp3, &tmp4)) == 0) {
				printf("Nie mozna odczytac znaku 5.\n");
				exit(1);
			}
			//printf("%d %d %d %d %d\n", tmp, tmp1, tmp2, tmp3, tmp4);
		}
		else if(type == ASN) {
			if((fscanf(f, "%d %d %d", &tmp, &tmp1, &tmp4)) == 0) {
				printf("Nie mozna odczytac znaku 5.\n");
				exit(1);
			}
		}
		if(tmp != j) {
			nettab[i+j][0] = 0;
			nettab[i+j][1] = tmp;
			j++;
		}
		nettab[i+j][0] = tmp1;
		nettab[i+j][1] = tmp4;
	}

	fclose(f);

	tmp = i + j;
	for(i = 0; i < tmp; i++) {
		//printf("%d %d\n", nettab[i][0], nettab[i][1]);
	}

	return 0;
}

/*int main()
{
	int source, tail, nodes, arcs;
	int (*network)[2];
	read_network("outp", &source, &tail, &nodes, &arcs, network);
	return 0;	
}*/
