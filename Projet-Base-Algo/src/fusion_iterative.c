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

    erreur_init = r->erreur_partition;
    erreur_seuil = erreur_init * seuil/100;
    erreur_after_merge = erreur_init;

    erreur_after_merge = RAG_give_closest_region(r, &i, &j);
    while (erreur_after_merge < erreur_seuil)
    {
        RAG_merge_regions(r, i, j);
        erreur_after_merge = RAG_give_closest_region(r, i, j);
    }
}

image create_output_image(rag r){ /* crée une image où chaque block est affiché avec la couleur moyenne de son block parent. */
    int i;
    int j;
    image img = r->img;
    image img_out;
    img_out = FAIRE_image();
    int dim = image_give_dim(img);
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);
    int mean_color[3];
    int n_block;
    image_initialize(img_out, dim, L, H);
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < L; j++)
        {
            n_block = (i*L) + j;
            RAG_give_mean_color(r, n_block, mean_color);
            image_write_pixel(img_out, i, j, (unsigned char *) mean_color);
        }
    }
    return img_out;
    
}
