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
    int *i = NULL;
    int *j = NULL;

    erreur_init = r->erreur_partition;
    erreur_seuil = erreur_init * seuil/100;
    erreur_after_merge = erreur_init;
    *i = 0;
    *j = 0;

    erreur_after_merge = RAG_give_closest_region(r, i, j);
    while (erreur_after_merge < erreur_seuil)
    {
        RAG_merge_regions(r, *i, *j);
        erreur_after_merge = RAG_give_closest_region(r, i, j);
    }
}

image create_output_image(rag r){ /* crée une image où chaque block est affiché avec la couleur moyenne de son block parent. */
    image output_image;
    return output_image;
}
