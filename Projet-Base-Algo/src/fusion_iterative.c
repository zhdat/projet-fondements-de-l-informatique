/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
* @file fusion_iterative.c
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"
#include "fusion_iterative.h"


void perform_merge(rag r, double seuil) {
    double erreur_init;
    double erreur_seuil;
    double erreur_after_merge;
    int i = 0;
    int j = 0;
    double tmp;

    erreur_init = r->erreur_partition;
    erreur_seuil = erreur_init * seuil;
    erreur_after_merge = erreur_init;
    tmp = RAG_give_closest_region(r, &i, &j); /* Création d'une variable afin de pouvoir détecter quand toutes les fusions possibles ont été testée */

    while (erreur_after_merge < erreur_seuil && tmp != -1) {
        RAG_merge_regions(r, i, j);
        erreur_after_merge += RAG_give_closest_region(r, &i, &j);
        tmp = RAG_give_closest_region(r, &i, &j);
        RAG_normalize_parents(r);
    }
}

image create_output_image(rag r, int n, int m) {
    int i;
    int j;
    int k;
    int pixel_start_x;
    int pixel_start_y;
    int nbr_pixel_colonne;
    int nbr_pixel_ligne;
    int c;
    image img = r->img;
    int dim = image_give_dim(img);
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);
    unsigned char mean_color[3];
    image img_out;
    img_out = FAIRE_image();
    nbr_pixel_colonne = H / m;
    nbr_pixel_ligne = L / n;
    image_initialize(img_out, dim, L, H);
    for (k = 0; k < n * m; k++){
        pixel_start_x = (k % n) * nbr_pixel_ligne;
        pixel_start_y = (k / n) * nbr_pixel_colonne;
        c = k;
        while (r->father[c] != c){
            c = r->father[c];
        }
        RAG_give_mean_color(r, c, mean_color);
        for (i = pixel_start_x; i < pixel_start_x + nbr_pixel_ligne; i++){
            for (j = pixel_start_y; j < pixel_start_y + nbr_pixel_colonne; j++){
                image_write_pixel(img_out, j, i, mean_color);
            }
        }
    }
    return img_out;
}
