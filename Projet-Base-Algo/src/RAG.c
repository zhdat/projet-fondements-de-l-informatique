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
* Permet d'initialiser les moments de la structure RAG.  
*  
* @param r structure RAG.
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par colonne.
*   
*/
static void init_moments_priv(rag r,int n,int m){
	int i;
	r->m = malloc(r->nb_blocks * sizeof(struct moments));
	for (i = 0; i < r->nb_blocks; i++) {
		give_moments(r->img, i, n, m, &(r->m[i].M0), r->m[i].M1, r->m[i].M2);
	}
}

/**  
* Permet de désallouer les moments de la structure RAG.  
*  
* @param r structure RAG. 
*   
*/
static void free_moments_priv(rag r){
	free(r->m);
}

/**  
* Permet d'initialiser les parents des cellules.  
*  
* @param r structure RAG.
* 
*/
static void init_father_priv(rag r){
	int i;
	r->father = malloc(r->nb_blocks * sizeof(int));
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = i;
	}
}

/**  
* Permet de désallouer les parents des cellules.  
*  
* @param r structure RAG. 
*   
*/
static void free_father_priv(rag r){
	free(r->father);
}

/**  
* Permet d'initialiser les voisins des cellules.  
*  
* @param r structure RAG.
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par colonne.
* 
*/
static void init_neighbors_priv(rag r, int n, int m){
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
* Permet de désallouer les voisins des cellules.  
*  
* @param r structure RAG. 
*   
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
* Permet d'initialiser l'erreur de partitions.  
*  
* @param r structure RAG.
* 
*/
static void init_partition_error_priv(rag r){
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		if (r->m[i].M1[1] == -1){ /* Image en nuances de gris. */
			r->erreur_partition += (r->m[i].M2[0] - (r->m[i].M1[0] * r->m[i].M1[0]) / r->m[i].M0);
		}else { /* Image en couleur. */
			r->erreur_partition += (r->m[i].M2[0] - (r->m[i].M1[0] * r->m[i].M1[0]) / r->m[i].M0) + (r->m[i].M2[1] - (r->m[i].M1[1] * r->m[i].M1[1]) / r->m[i].M0) + (r->m[i].M2[2] - (r->m[i].M1[2] * r->m[i].M1[2]) / r->m[i].M0);
		}
	}
}

extern rag create_RAG(image img, int n, int m){
	rag r = malloc(sizeof(struct RAG));
	r->img = img;
	r->nb_blocks = n * m;
	r->erreur_partition = 0;

	init_father_priv(r); /* Initialisation des parents */
	init_neighbors_priv(r, n, m); /* Initialisation des voisins */

	init_moments_priv(r, n, m); /* Initialisation des moments */
	init_partition_error_priv(r); /* Initialisation de l'erreur de partition */
	return r;
}

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

    if (r->m[i].M1[1] == -1){ /* Erreur dans le cas où l'image est en nuance de gris. */
    	mu_B[0] = r->m[i].M1[0] / r->m[i].M0;
		mu_Bp[0] = r->m[j].M1[0] / r->m[j].M0;

		diff_mu[0] = mu_B[0] - mu_Bp[0];

		norme_2 = diff_mu[0] * diff_mu[0];

		erreur = ((r->m[i].M0 * r->m[j].M0) / (r->m[i].M0 + r->m[j].M0)) * norme_2;

		return erreur;

    } else { /* Erreur dans le cas où l'image est en couleur. */
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

}

extern double RAG_give_closest_region(rag r, int *indice1_block, int *indice2_block){
	int i;
	int j;
	double erreur_min;
	double erreur;
	erreur_min = -1;
	*indice1_block = 0;
	*indice2_block = 1;

	for (i = 0; i < r->nb_blocks; i++) {
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
* Permet de mettre à jour les moments de la région fusionnée.
*
* @param r structure RAG.
* @param region1 indice de block.
* @param region2 indice de block.
*
*/
static void update_moments_priv(rag r, int region1, int region2){
	int i;
	r->m[region2].M0 = r->m[region1].M0 + r->m[region2].M0;
	if (r->m[region1].M1[1] == -1) { /* Dans le cas où l'image est en nuance de gris. */
		r->m[region2].M1[0] = r->m[region1].M1[0] + r->m[region2].M1[0];
		r->m[region2].M2[0] = r->m[region1].M2[0] + r->m[region2].M2[0];
	} else {
		for (i = 0; i < 3; i++) { /* Dans le cas où l'image est en couleur. */
			r->m[region2].M1[i] = r->m[region1].M1[i] + r->m[region2].M1[i];
			r->m[region2].M2[i] = r->m[region1].M2[i] + r->m[region2].M2[i];
		}
	}
}


/**
* Permet de mettre à jour les listes des voisins des deux régions fusionnées.
*
* @param r structure RAG.
* @param region1 indice de block.
* @param region2 indice de block.
*
*/
static void update_neighbors_priv(rag r, int region1, int region2){
	cellule c;
	for (c = r->neighbors[region1]; c != NULL; c = c->next) {
		if (c->block != region2) {
            cellule c2 = malloc(sizeof(struct cellule));
            c2->block = c->block;
            c2->next = r->neighbors[region2];
            r->neighbors[region2] = c2;
        }
	}
    r->neighbors[region1] = NULL;
}

void RAG_merge_regions(rag r, int region1, int region2){
	double mu_B[3];
	double mu_Bp[3];
	double diff_mu[3];
	double norme_2;

	/* Mise à jour de l'erreur de partition */
	if (r->m[region1].M1[1] == -1){ /* Dans le cas où l'image est en nuance de gris. */
		mu_B[0] = r->m[region1].M1[0] / r->m[region1].M0;
		mu_Bp[0] = r->m[region2].M1[0] / r->m[region2].M0;

		diff_mu[0] = mu_B[0] - mu_Bp[0];

		norme_2 = diff_mu[0] * diff_mu[0];

		r->erreur_partition = ((r->m[region1].M0 * r->m[region2].M0) / (r->m[region1].M0 + r->m[region2].M0)) * norme_2;

	} else { /* Dans le cas où l'image est en couleur. */
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


	/* Mise à jour du tableau father */
	r->father[region1] = region2;

	/* Mise à jour des moments */
	update_moments_priv(r, region1, region2);

	/* Mise à jour des listes de voisins des deux régions fusionnées */
	update_neighbors_priv(r, region1, region2);
	
}

extern void RAG_normalize_parents(rag r){
	int i;
	for (i = 0; i < r->nb_blocks; i++) {
		r->father[i] = r->father[r->father[i]];
	}
}

extern void RAG_give_mean_color(rag r, int indice_block, unsigned char *average_color){
	int i;
	int indice_parent = r->father[indice_block];

	if (r->m[indice_parent].M1[1] == -1){ /* Dans le cas où l'image est en nuance de gris. */
		average_color[0] = r->m[indice_parent].M1[0] / r->m[indice_parent].M0;
	} else { /* Dans le cas où l'image est en couleur. */
		for (i = 0; i < 3; i++) {
		 average_color[i] = r->m[indice_parent].M1[i] / r->m[indice_parent].M0;
		}
	}

}
