#ifndef RAG_H
#define RAG_H
#include "image.h"

struct moments {
	int M0;
	double M1[3];
	double M2[3];
};

typedef struct moments* moments;

typedef struct cellule* cellule;

struct cellule {
	int block;
	cellule next;
};

struct RAG {
	image  img;
	int nb_blocks;
	long double erreur_partition;
	moments m;
	int * father;
	cellule *neighbors;
};

typedef struct RAG * rag;

extern rag create_RAG(image img, int n, int m);

static void init_moments_priv(rag r,int n,int m);

static void init_father_priv(rag r);

static void init_neighbors_priv(rag r,int n,int m);

static void init_partition_error_priv(rag r);

extern double RAG_give_closest_region(rag r, int * i, int * j);

void RAG_merge_regions(rag r, int i, int j);

extern void RAG_normalize_parents(rag r);

extern void RAG_give_mean_color(rag r, int indice_block, int *average_color);
#endif
