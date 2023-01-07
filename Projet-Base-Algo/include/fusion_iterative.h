/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

#ifndef FUSION_ITERATIVE_H
#define FUSION_ITERATIVE_H
#include "moment.h"
#include "RAG.h"
#include "image.h"
#include "point.h"
#include "type_obj.h"

/**
* Cette fonction effectue itérativement des fusions de régions
* jusqu'à ce que l'erreur de partition soit inférieure au seuil passé en second paramètre.
*
* @param r structure RAG.
* @param seuil valeur permettant de contrôler le nombre fusion réaliser.
*
*
*/
void perform_merge(rag r, double seuil);

/**
* Cette fonction crée une image
* où chaque block est affiché avec la couleur moyenne de son block parent.
*
* @param r structure RAG.
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par colonne.
*
* @return image.
*
*/
image create_output_image(rag r, int n, int m);
#endif
