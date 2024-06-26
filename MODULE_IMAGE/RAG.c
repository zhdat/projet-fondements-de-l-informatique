#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"

/* @TODO : Free les Init !!!!! */

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
	int i_min;
	int j_min;
	double erreur_min;
	double erreur;
	erreur = 0;
	erreur_min = -1;
	i_min = 0;
	j_min = 0;
	for (i = 0; i < r->nb_blocks; i++) { /* @TODO (voisins) */
		if (r->father[i] == i) {
			*indice1_block = i;
			for (j = i; j < r->nb_blocks; j++) {
				if (r->father[j] == j) {
					*indice2_block = j;
					erreur = ((r->m[indice1_block].M0 * r->m[indice2_block].M0) / (r->m[indice1_block].M0 + r->m[indice2_block].M0)) * /* @TODO */
				}
				if (erreur < erreur_min) {
					erreur_min = erreur;
					i_min = i;
					j_min = j;
					*indice1_block = i_min;
					*indice2_block = j_min;
				}
			}
		}
	}
	return erreur_min;
}

/* Mise à jour des moments */
static void update_moments_priv(rag r, int region1, int region2){ /* Met à jour les moments de la région fusionnée. */
	int i;
	r->m[region2].M0 = r->m[region1].M0 + r->m[region2].M0;
	for (i = 0; i < 3; i++) {
		r->m[region2].M1[i] = r->m[region1].M1[i] + r->m[region2].M1[i];
		r->m[region2].M2[i] = r->m[region1].M2[i] + r->m[region2].M2[i];
	}
}

/* Mise à jour des listes de voisins des deux régions fusionnées */
static void update_neighbors_priv(rag r, int region1, int region2){ /* Met à jour les listes de voisins des deux régions fusionnées. */
	cellule c = r->neighbors[region1];
	for (c = r->neighbors[region1]; c != NULL; c = c->next) {
		if (c->block != region2) {
			cellule c2 = malloc(sizeof(cellule));
			c2->block = c->block;
			c2->next = r->neighbors[region2];
			r->neighbors[region2] = c2;
		}
	}
}


void RAG_merge_region(rag r, int region1, int region2){ /* Fusionne les 2 régions en mettant à jour : le tableau father, les moments, les voisins et l'erreur de partition. */
	int i;

	/* Mise à jour du tableau father */
	r->father[region1] = region2;

	/* Mise à jour des moments */
	update_moments_priv(r, region1, region2);

	/* Mise à jour des listes de voisins des deux régions fusionnées */
	update_neighbors_priv(r, region1, region2);

	/* Mise à jour de l'erreur de partition */
	r->erreur_partition = ((r->m[indice1_block].M0 * r->m[indice2_block].M0) / (r->m[indice1_block].M0 + r->m[indice2_block].M0)) * /* @TODO */
}

extern void RAG_normalize_parents(rag r){ /* effectue un parcours rétrograde du tableau father en remplçant pour chaque indice i, father[i] par father[father[i]]. */
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = r->father[r->father[i]];
	}
}

extern void RAG_give_mean_color(rag r, int indice_block, int *average_color){ /* renvoie dans le dernier paramètre la courleur moyenne du block parent du block dont l'indice est passé en second paramètre. */
	int i;
	int indice_parent = r->father[indice_block];
	for (i = 0; i < 3; i++) {
		average_color[i] = r->m[indice_parent].M1[i] / r->m[indice_parent].M0;
	}
}