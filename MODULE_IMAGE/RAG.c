#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"

struct moments
{
	int M0;
	double M1[3];
	double M2[3];
};
typedef struct cellule* cellule;

struct cellule
{
	int block;
	cellule next;
};
typedef struct moments* moments;

struct RAG {
	image  img;
	int nb_blocks;
	long double erreur_partition;
	moments m;
	int * father;
	cellule *neighbors;};

