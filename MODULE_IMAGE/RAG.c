#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"

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
	cellule *neighbors;
};

extern rag create_RAG(image img, int n, int m) {
	rag r = malloc(sizeof(struct RAG));
	r->img = img;
	r->nb_blocks = n * m;
	r->erreur_partition = 0;
	r->m = malloc(sizeof(struct moments) * r->nb_blocks);
	r->father = malloc(sizeof(int) * r->nb_blocks);
	r->neighbors = malloc(sizeof(cellule) * r->nb_blocks);
	init_moments_priv(r, n, m);
	init_father_priv(r);
	init_neighbors_priv(r, n, m);
	init_partition_error_priv(r);
	return r;
}

static void init_moments_priv(rag r,int n,int m){
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		give_moments(r->img, i, n, m, &(r->m[i].M0), r->m[i].M1, r->m[i].M2);
	}
}

static void init_father_priv(rag r){
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = i;
	}
}

static void init_neighbors_priv(rag r,int n,int m){
	
}

static void init_partition_error_priv(rag r);
