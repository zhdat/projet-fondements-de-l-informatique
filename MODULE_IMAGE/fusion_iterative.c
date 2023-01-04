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
    int *i;
    int *j;

    erreur_init = r->erreur_partition;
    erreur_seuil = erreur_init * seuil/100;
    erreur_after_merge = erreur_init;
    *i = 0;
    *j = 0;

    erreur_after_merge = RAG_give_closest_region(r, *i, *j);
    while (erreur_after_merge < erreur_seuil)
    {
        RAG_merge_regions(r, *i, *j);
        erreur_after_merge = RAG_give_closest_region(r, *i, *j);
    }
}

image create_output_image(rag r){ /* crée une image de sortie où chaque block est affiché avec la couleur moyenne de son block parent. */
    int i;
    int j;
    int k;
    int indice_block;
    int indice_block_parent;
    int *average_color;
    image img;

    img = r->img;
    average_color = malloc(3 * sizeof(int));
    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            indice_block = i * img->width + j;
            indice_block_parent = r->father[indice_block];
            RAG_give_mean_color(r, indice_block_parent, average_color);
            for (k = 0; k < 3; k++)
            {
                img->data[i][j][k] = average_color[k];
            }
        }
    }
    free(average_color);
    return img;
}
