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
#include "fusion_iterative.h"


void perform_merge(rag r, double seuil){ /* effectue itérativement des fusions de régions jusqu'à ce que l'erreur de partition soit inférieure au seuil passé en second paramètre. */
    double erreur_init;
    double erreur_seuil;
    double erreur_after_merge;
    int i = 0;
    int j = 0;
    double tmp;

    erreur_init = r->erreur_partition;
    erreur_seuil = erreur_init * seuil/100;
    erreur_after_merge = erreur_init;
    tmp = RAG_give_closest_region(r, &i, &j);

    erreur_after_merge += RAG_give_closest_region(r, &i, &j);
    while (erreur_after_merge < erreur_seuil && tmp != -1)
    {
        RAG_merge_regions(r, i, j);
        erreur_after_merge += RAG_give_closest_region(r, &i, &j);
        tmp = RAG_give_closest_region(r, &i, &j);
        RAG_normalize_parents(r);
    }
}

image create_output_image(rag r, int n, int m){ /* crée une image où chaque block est affiché avec la couleur moyenne de son block parent. */
/*    int i;
    int j;
    int k;
    int pixel_start_x;
    int pixel_start_y;
    int nbr_pixel_colonne;
    int nbr_pixel_ligne;
    int c;
    image img = r->img;
    image img_out;
    img_out = FAIRE_image();
    int dim = image_give_dim(img);
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);
    int mean_color[3];
    nbr_pixel_colonne = H / m;
    nbr_pixel_ligne = L / n;
    image_initialize(img_out, dim, L, H);
    for (k = 0; k < n * m; k++){
        pixel_start_x = nbr_colonne * k % m;
        pixel_start_y = nbr_ligne * k / m;
        c = k;
        while (r->father[c] != c){
            c = r->father[c];
        }
        RAG_give_mean_color(r, c, mean_color);
        for (i = pixel_start_y; i < pixel_start_y + nbr_pixel_ligne; i++){
            for (j = pixel_start_x; j < pixel_start_x + nbr_pixel_colonne; j++){
                image_write_pixel(img_out, i, j, (unsigned char *) mean_color);
            }
        }
    }

    return img_out; */
    int i;
    int j;
    image img = adj->img;
    image img_out;
    int dim = image_give_dim(img);
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);
    int mean_color[3];
    unsigned char mean_tab[3]; 
    int n_block;
    img_out = FAIRE_image();
    image_initialize(img_out, dim, L, H);
    int k;
    /*
    for (i=0; i<nb_blocks; i++){
        mean_tab[i] = 
    }*/
    for (i=0; i<H; i++){
        for (j=0; j<L; j++){
            n_block = j/(L/n) + (i/(H/m))*n;
            
            RAG_give_mean_color(adj, n_block, mean_color);
            printf("%d %d %d\n",mean_color[0],mean_color[1],mean_color[2]);
            for (k=0; k<3; k++){
                mean_tab[k] = (unsigned char)mean_color[k];
            }
            image_write_pixel(img_out, i, j, mean_tab);
        }
    }
    return img_out;
}
    

