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
#include "image.h"
#include "moment.h"
#include "objet.h"
#include "point.h"
#include "image.c"

extern void give_moments(image img, int num_bloc, int n, int m, int *M0, double *M1, double *M2) {

    /* Déclaration */
    int pixel_start_x;
    int pixel_start_y;
    Point p;
    int i;
    int j;
    double R;
    double G;
    double B;
    double GR;
    double R2;
    double G2;
    double B2;
    double GR2;
    int tableau_RGB[3];
    int nbr_pixel_colonne;
    int nbr_pixel_ligne;
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);

    /* Initialisation */
    nbr_pixel_colonne = H / m;
    nbr_pixel_ligne = L / n;
    pixel_start_x = (num_bloc % n) * nbr_pixel_ligne;
    pixel_start_y = (num_bloc / n) * nbr_pixel_colonne;
    *M0 = 0;
    M1[0] = 0;
    M1[1] = 0;
    M1[2] = 0;
    M2[0] = 0;
    M2[1] = 0;
    M2[2] = 0;
    R = 0;
    G = 0;
    B = 0;
    GR = 0;
    R2 = 0;
    G2 = 0;
    B2 = 0;
    GR2 = 0;
    COORDX(p) = pixel_start_x;
    COORDY(p) = pixel_start_y;
    image_move_to(img, &p);

    /* Calcul des moments (image couleur) */
    if (image_give_dim(img) == 3) {
        for (i = 0; i < nbr_pixel_colonne; i++) {
            for (j = 0; j < nbr_pixel_ligne; j++) {
                COORDX(p) = pixel_start_x + j;
                COORDY(p) = pixel_start_y + i;
                image_move_to(img, &p);
                tableau_RGB[0] = image_lire_pixel(img)[0];
                tableau_RGB[1] = image_lire_pixel(img)[1];
                tableau_RGB[2] = image_lire_pixel(img)[2];
                R += tableau_RGB[0];
                G += tableau_RGB[1];
                B += tableau_RGB[2];
                GR += tableau_RGB[0] * tableau_RGB[1];
                R2 += tableau_RGB[0] * tableau_RGB[0];
                G2 += tableau_RGB[1] * tableau_RGB[1];
                B2 += tableau_RGB[2] * tableau_RGB[2];
                GR2 += tableau_RGB[0] * tableau_RGB[1] * tableau_RGB[0] * tableau_RGB[1];
                *M0 += 1;
            }
        }

        M1[0] = R;
        M1[1] = G;
        M1[2] = B;
        M2[0] = R2;
        M2[1] = G2;
        M2[2] = B2;

    } else { /* Calcul des moments (image nuances de gris) */
        for (i = 0; i < nbr_pixel_colonne; i++) {
            for (j = 0; j < nbr_pixel_ligne; j++) {
                COORDX(p) = pixel_start_x + j;
                COORDY(p) = pixel_start_y + i;
                image_move_to(img, &p);
                tableau_RGB[0] = image_lire_pixel(img)[0];
                GR += tableau_RGB[0];
                GR2 += tableau_RGB[0] * tableau_RGB[0];
                *M0 += 1;
            }
        }

        M1[0] = GR;
        M1[1] = -1;
        M1[2] = -1;
        M2[0] = GR2;
        M2[1] = -1;
        M2[2] = -1;
    }
}
