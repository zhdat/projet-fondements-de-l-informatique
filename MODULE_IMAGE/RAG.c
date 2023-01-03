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

static void init_moments_priv(rag r,int n,int m){ /* Initialise les moments des blocks à l'aide de give_moments() */
	int i;
	int M0;
	double M1[3];
	double M2[3];
	r->m = malloc(r->nb_blocks * sizeof(moments));
	for (i = 0; i < r->nb_blocks; i++) {
		give_moments(r->img, i, n, m, &M0, M1, M2);
		r->m[i].M0 = M0;
		r->m[i].M1[0] = M1[0];
		r->m[i].M1[1] = M1[1];
		r->m[i].M1[2] = M1[2];
		r->m[i].M2[0] = M2[0];
		r->m[i].M2[1] = M2[1];
		r->m[i].M2[2] = M2[2];
	}
}

static void init_father_priv(rag r){ /* Initialise le père de chaque block à lui même. */
	int i;
	r->father = malloc(r->nb_blocks * sizeof(int));
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = i;
	}
}

static void init_neighbors_priv(rag r, int n, int m){ /* Initialise les listes de voisins de chaque blocks */
	r->neighbors = malloc(r->nb_blocks * sizeof(cellule));
	int i;
	int j;
	int k;
	for (i = 0; i < r->nb_blocks; i++) {
		r->neighbors[i] = NULL;
	}

	for (j = 0; j < n; j++){
		for (k = 0; k < m; k++){
			if (j < n - 1) {
				cellule c = malloc(sizeof(cellule));
				c->block = j * m + k;
				c->next = r->neighbors[(j + 1) * m + k];
				r->neighbors[(j + 1) * m + k] = c;
			}
			if (k < m - 1) {
				cellule c = malloc(sizeof(cellule));
				c->block = j * m + k;
				c->next = r->neighbors[j * m + k + 1];
				r->neighbors[j * m + k + 1] = c;
			}
		}
	}
}

static init_partition_error_priv(rag r){ /* initialise l'erreur de partition. L'erreur de partition est définie par la somme des erreur quadratiques des blocks. */
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->erreur_partition += (r->m[i].M2[0] - (r->m[i].M1[0] * r->m[i].M1[0]) / r->m[i].M0) + (r->m[i].M2[1] - (r->m[i].M1[1] * r->m[i].M1[1]) / r->m[i].M0) + (r->m[i].M2[2] - (r->m[i].M1[2] * r->m[i].M1[2]) / r->m[i].M0);
	}
}

extern rag create_RAG(image img, int n, int m){ /* Crée un RAG à partir d'une image et de la taille des blocks. */
	rag r = malloc(sizeof(struct RAG));
	r->img = img;
	r->nb_blocks = n * m;
	r->erreur_partition = 0;

	init_father_priv(r);
	init_neighbors_priv(r, n, m);

	init_moments_priv(r, n, m);
	init_partition_error_priv(r);
	return r;
}

extern double RAG_give_closest_region(rag r, int *indice1_block, int *indice2_block){ /* renvoie les deux indices de blocks dont la fusion induit la plus petite augmentation d'erreur quadratique. Seuls les blocks vérifiant father[i]==i seront pris en compte dans le calcul. Cette fonction renvoie la valeur de cette augmentation. */
	int i;
	int j;
	double erreur;
	for (i = 0; i < r->nb_blocks; i++) {
		if (r->father[i] == i) {
			*indice1_block = i;
			for (j = i; j < r->nb_blocks; j++) {
				if (r->father[j] == j) {
					*indice2_block = j;
					erreur = ((r->m[indice1_block].M0 * r->m[indice2_block].M0) / (r->m[indice1_block].M0 + r->m[indice2_block].M0)) * /* @TODO */
				}
			}
		}
	}
}

void RAG_merge_region(rag r, int region1, int region2){ /* Fusionne les 2 régions en mettant à jour : le tableau father, les moments, les voisins et l'erreur de partition. */
	int i;

	r->father[region1] = region2;

	r->m[region2].M0 = r->m[region1].M0 + r->m[region2].M0;
	for (i = 0; i < 3; i++) {
		r->m[region2].M1[i] = r->m[region1].M1[i] + r->m[region2].M1[i];
		r->m[region2].M2[i] = r->m[region1].M2[i] + r->m[region2].M2[i];
	}

	
}