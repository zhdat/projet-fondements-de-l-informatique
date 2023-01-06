/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void init_moments_priv(rag r,int n,int m){ /* Initialise les moments des blocks à l'aide de give_moments() */
	int i;
	r->m = malloc(r->nb_blocks * sizeof(struct moments));
	for (i = 0; i < r->nb_blocks; i++) {
		give_moments(r->img, i, n, m, &(r->m[i].M0), r->m[i].M1, r->m[i].M2);
	}
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void free_moments_priv(rag r){
	free(r->m);
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void init_father_priv(rag r){ /* Initialise le père de chaque block à lui même. */
	int i;
	r->father = malloc(r->nb_blocks * sizeof(int));
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = i;
	}
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void free_father_priv(rag r){
	free(r->father);
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void init_neighbors_priv(rag r, int n, int m){ /* Initialise les listes de voisins de chaque blocks */
	int i;
	int j;
	int k;
	r->neighbors = malloc(r->nb_blocks * sizeof(struct cellule));
	for (i = 0; i < r->nb_blocks; i++) {
		r->neighbors[i] = NULL;
	}

	for (j = 0; j < n; j++){
		for (k = 0; k < m; k++){
			if (j < n - 1) {
				cellule c = malloc(sizeof(struct cellule));
				c->block = (j + 1) * m + k;
				c->next = r->neighbors[j * m + k];
				r->neighbors[j * m + k] = c;
			}
			if (k < m - 1) {
				cellule c = malloc(sizeof(struct cellule));
				c->block = j * m + k + 1;
				c->next = r->neighbors[j * m + k];
				r->neighbors[j * m + k] = c;
			}
		}
	}
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void free_neighbors_priv(rag r){
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		cellule c = r->neighbors[i];
		while (c != NULL) {
			cellule tmp = c;
			c = c->next;
			free(tmp);
		}
	}
	free(r->neighbors);
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void init_partition_error_priv(rag r){ /* initialise l'erreur de partition. L'erreur de partition est définie par la somme des erreur quadratiques des blocks. */
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->erreur_partition += (r->m[i].M2[0] - (r->m[i].M1[0] * r->m[i].M1[0]) / r->m[i].M0) + (r->m[i].M2[1] - (r->m[i].M1[1] * r->m[i].M1[1]) / r->m[i].M0) + (r->m[i].M2[2] - (r->m[i].M1[2] * r->m[i].M1[2]) / r->m[i].M0);
	}
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
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


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
extern void free_RAG(rag r){
	free_father_priv(r);
	free_neighbors_priv(r);
	free_moments_priv(r);
	free(r);
}

double get_erreur(rag r, int i, int j) {
    double mu_B[3];
    double mu_Bp[3];
    double diff_mu[3];
    double norme_2;
    double erreur;

    mu_B[0] = r->m[i].M1[0] / r->m[i].M0;
    mu_B[1] = r->m[i].M1[1] / r->m[i].M0;
    mu_B[2] = r->m[i].M1[2] / r->m[i].M0;
    mu_Bp[0] = r->m[j].M1[0] / r->m[j].M0;
    mu_Bp[1] = r->m[j].M1[1] / r->m[j].M0;
    mu_Bp[2] = r->m[j].M1[2] / r->m[j].M0;

    diff_mu[0] = mu_B[0] - mu_Bp[0];
    diff_mu[1] = mu_B[1] - mu_Bp[1];
    diff_mu[2] = mu_B[2] - mu_Bp[2];

    norme_2 = diff_mu[0] * diff_mu[0] + diff_mu[1] * diff_mu[1] + diff_mu[2] * diff_mu[2];

    erreur = ((r->m[i].M0 * r->m[j].M0) / (r->m[i].M0 + r->m[j].M0)) * norme_2;
    return erreur;
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
extern double RAG_give_closest_region(rag r, int *indice1_block, int *indice2_block){ /* renvoie les deux indices de blocks dont la fusion induit la plus petite augmentation d'erreur quadratique. Seuls les blocks vérifiant father[i]==i seront pris en compte dans le calcul. Cette fonction renvoie la valeur de cette augmentation. */
	int i;
	int j;
	double erreur_min;
	double erreur;
	erreur_min = -1;
	*indice1_block = 0;
	*indice2_block = 1;

	for (i = 0; i < r->nb_blocks; i++) { /* @TODO (voisins) */
		if (r->father[i] == i) {
            cellule c = r->neighbors[i];
            while (c != NULL) {
                j = c->block;
                while (r->father[j] != j) {
                    j = r->father[j];
                }
                if (i != j) {
                    erreur = get_erreur(r, i, j);
                    if (erreur_min == -1 || erreur < erreur_min) {
                        erreur_min = erreur;
                        *indice1_block = i;
                        *indice2_block = j;
                    }
                }
                c = c->next;
            }
		}
	}
	return erreur_min;
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void update_moments_priv(rag r, int region1, int region2){ /* Met à jour les moments de la région fusionnée. */
	int i;
	r->m[region2].M0 = r->m[region1].M0 + r->m[region2].M0;
	for (i = 0; i < 3; i++) {
		r->m[region2].M1[i] = r->m[region1].M1[i] + r->m[region2].M1[i];
		r->m[region2].M2[i] = r->m[region1].M2[i] + r->m[region2].M2[i];
	}
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
static void update_neighbors_priv(rag r, int region1, int region2){ /* Met à jour les listes de voisins des deux régions fusionnées. */
	cellule c;
	for (c = r->neighbors[region1]; c != NULL; c = c->next) {
		if (c->block != region2) {
			cellule c2 = malloc(sizeof(struct cellule));
			c2->block = c->block;
			c2->next = r->neighbors[region2];
			r->neighbors[region2] = c2;
		}
	}
}


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
void RAG_merge_regions(rag r, int region1, int region2){ /* Fusionne les 2 régions en mettant à jour : le tableau father, les moments, les voisins et l'erreur de partition. */
	double mu_B[3];
	double mu_Bp[3];
	double diff_mu[3];
	double norme_2;


	/* Mise à jour du tableau father */
	r->father[region1] = region2;

	/* Mise à jour des moments */
	update_moments_priv(r, region1, region2);

	/* Mise à jour des listes de voisins des deux régions fusionnées */
	update_neighbors_priv(r, region1, region2);

	/* Mise à jour de l'erreur de partition */
	mu_B[0] = r->m[region1].M1[0] / r->m[region1].M0;
	mu_B[1] = r->m[region1].M1[1] / r->m[region1].M0;
	mu_B[2] = r->m[region1].M1[2] / r->m[region1].M0;
	mu_Bp[0] = r->m[region2].M1[0] / r->m[region2].M0;
	mu_Bp[1] = r->m[region2].M1[1] / r->m[region2].M0;
	mu_Bp[2] = r->m[region2].M1[2] / r->m[region2].M0;

	diff_mu[0] = mu_B[0] - mu_Bp[0];
	diff_mu[1] = mu_B[1] - mu_Bp[1];
	diff_mu[2] = mu_B[2] - mu_Bp[2];

	norme_2 = diff_mu[0] * diff_mu[0] + diff_mu[1] * diff_mu[1] + diff_mu[2] * diff_mu[2];

	r->erreur_partition = ((r->m[region1].M0 * r->m[region2].M0) / (r->m[region1].M0 + r->m[region2].M0)) * norme_2;
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
/* @TODO placer cette fonction*/
extern void RAG_normalize_parents(rag r){ /* effectue un parcours rétrograde du tableau father en remplçant pour chaque indice i, father[i] par father[father[i]]. */
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = r->father[r->father[i]];
	}
}

/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
extern void RAG_give_mean_color(rag r, int indice_block, unsigned char *average_color){ /* renvoie dans le dernier paramètre la courleur moyenne du block parent du block dont l'indice est passé en second paramètre. */
	int i;
	int indice_parent = r->father[indice_block];
	for (i = 0; i < 3; i++) {
		average_color[i] = r->m[indice_parent].M1[i] / r->m[indice_parent].M0;
	}
}
