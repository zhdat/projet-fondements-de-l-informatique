/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

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


/**  
* Cette fonction remplit la structure RAG.  
*  
* @param img image. 
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par colonne.
* 
* @return renvoie la structure RAG.  
*   
*/
extern rag create_RAG(image img, int n, int m);


/**  
* Permet de désallouer la structure RAG.  
*  
* @param r structure RAG. 
*   
*/
extern void free_RAG(rag r);


/**
* Permet de récupérer l'erreur.
*
* @param r structure RAG.
* @param i indice de block.
* @param j indice de block.
*
*/
double get_erreur(rag r, int i, int j);

/**  
* Cherche deux indices de blocks induisant la plus petite augmentation d'erreur quadratique.  
*  
* @param r structure RAG.
* @param i indice de block.
* @param j indice de block.
* 
* @return Renvoie l'augmentation de l'erreur quadratique.
* 
*/
extern double RAG_give_closest_region(rag r, int * i, int * j);


/**  
* Fusionne les deux régions passées en paramètres en effectuant :
* - Mise à jour du tableau father
* - Mise à jour des moments
* - Mise à jour des listes des deux régions fusionnées
* - Mise à jour de l'erreur de partition.
*  
* @param r structure RAG.
* @param i indice de block.
* @param j indice de block.
* 
*/
void RAG_merge_regions(rag r, int i, int j);


/**  
* Effectue un parcours rétrograde du tableau father en remplaçant pour chaque indice i, father[i] par father[father[i]].  
*  
* @param r structure RAG.
* 
*/
extern void RAG_normalize_parents(rag r);


/**  
* Calcule la couleur moyenne d'un block.  
*  
* @param r structure RAG.
* @param indice_block indice de block.
* @param average_color couleur moyenne.
* 
*/
extern void RAG_give_mean_color(rag r, int indice_block, unsigned char *average_color);
#endif
