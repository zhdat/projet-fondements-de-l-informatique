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

extern void give_moments(image img, int num_bloc, int n, int m, int* M0, double* M1, double* M2){
    
    int nbr_ligne; /* Ligne du block */
    int nbr_colonne; /* Colonne du block */
    int pixel_start_x;
    int pixel_start_y;
    Point p;
    int i;
    int j;
    int nbr_pixel;
    int tmp;
    double R;
    double G;
    double B;
    double GR;
    double R2;
    double G2;
    double B2;
    double GR2;
    double tableau_RGB[3];

    nbr_colonne = image_give_largeur(img) / n;
    nbr_ligne = image_give_hauteur(img) / m;
    pixel_start_x = nbr_colonne * num_bloc % m;
    pixel_start_y = nbr_ligne * num_bloc / m;
    nbr_pixel = nbr_colonne * nbr_ligne;
    tmp = 0;
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

    if (image_give_dim(img) == 3){
        while (tmp < nbr_pixel)
        {
          if (nbr_ligne % 2 == 0){
            for (i = 0; i < nbr_ligne / 2 - 1; i++){
                for (j = 0; j < nbr_colonne; j++){
                    tableau_RGB[0] = image_lire_pixel(img)[0];
                    tableau_RGB[1] = image_lire_pixel(img)[1];
                    tableau_RGB[2] = image_lire_pixel(img)[2];
                    R = R + tableau_RGB[0];
                    R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                    G = G + tableau_RGB[1];
                    G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                    B = B + tableau_RGB[2];
                    B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                    tmp += 1;
                    *M0 += 1;
                    image_pixel_droite(img);
                }
                image_pixel_dessous(img);

                for (j = 0; j < nbr_colonne; j++){
                    tableau_RGB[0] = image_lire_pixel(img)[0];
                    tableau_RGB[1] = image_lire_pixel(img)[1];
                    tableau_RGB[2] = image_lire_pixel(img)[2];
                    R = R + tableau_RGB[0];
                    R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                    G = G + tableau_RGB[1];
                    G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                    B = B + tableau_RGB[2];
                    B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                    tmp+=1;
                    *M0 += 1;
                    image_pixel_gauche(img);
                }
                image_pixel_dessous(img);
            }
            for (j = 0; j < nbr_colonne; j++){ 
                tableau_RGB[0] = image_lire_pixel(img)[0];
                tableau_RGB[1] = image_lire_pixel(img)[1];
                tableau_RGB[2] = image_lire_pixel(img)[2];
                R = R + tableau_RGB[0];
                R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                G = G + tableau_RGB[1];
                G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                B = B + tableau_RGB[2];
                B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                tmp+=1;
                *M0 += 1;
                image_pixel_droite(img);
            }
            image_pixel_dessous(img);
            for (j = 0; j < nbr_colonne; j++){ 
                tableau_RGB[0] = image_lire_pixel(img)[0];
                tableau_RGB[1] = image_lire_pixel(img)[1];
                tableau_RGB[2] = image_lire_pixel(img)[2];
                R = R + tableau_RGB[0];
                R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                G = G + tableau_RGB[1];
                G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                B = B + tableau_RGB[2];
                B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                tmp+=1;
                *M0 += 1;
                image_pixel_gauche(img);
            }
        }else {
          for (i = 0; i < nbr_ligne / 2 - 1; i++){
                for (j = 0; j < nbr_colonne; j++){
                    tableau_RGB[0] = image_lire_pixel(img)[0];
                    tableau_RGB[1] = image_lire_pixel(img)[1];
                    tableau_RGB[2] = image_lire_pixel(img)[2];
                    R = R + tableau_RGB[0];
                    R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                    G = G + tableau_RGB[1];
                    G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                    B = B + tableau_RGB[2];
                    B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                    tmp += 1;
                    *M0 += 1;
                    image_pixel_droite(img);
                }
                image_pixel_dessous(img);

                for (j = 0; j < nbr_colonne; j++){
                    tableau_RGB[0] = image_lire_pixel(img)[0];
                    tableau_RGB[1] = image_lire_pixel(img)[1];
                    tableau_RGB[2] = image_lire_pixel(img)[2];
                    R = R + tableau_RGB[0];
                    R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                    G = G + tableau_RGB[1];
                    G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                    B = B + tableau_RGB[2];
                    B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                    tmp+=1;
                    *M0 += 1;
                    image_pixel_gauche(img);
                }
                image_pixel_dessous(img);
            }
            for (j = 0; j < nbr_colonne; j++){ 
                tableau_RGB[0] = image_lire_pixel(img)[0];
                tableau_RGB[1] = image_lire_pixel(img)[1];
                tableau_RGB[2] = image_lire_pixel(img)[2];
                R = R +tableau_RGB[0];
                R2 = R2 + tableau_RGB[0] * tableau_RGB[0];
                G = G + tableau_RGB[1];
                G2 = G2 + tableau_RGB[1] * tableau_RGB[1];
                B = B + tableau_RGB[2];
                B2 = B2 + tableau_RGB[2] * tableau_RGB[2];
                tmp+=1;
                *M0 += 1;
                image_pixel_droite(img);
            }
        }
      }
        M1[0] = R;
        M1[1] = G;
        M1[2] = B;
        M2[0] = R2;
        M2[1] = G2;
        M2[2] = B2;

    } else{ /* @TODO Gris */
        while (tmp < nbr_pixel)
        {
            for (i = 0; i < nbr_ligne; i++){
                for (j = 0; j < nbr_colonne; j++){
                    *tableau_RGB = *image_lire_pixel(img);
                    GR += tableau_RGB[0];
                    GR2 += tableau_RGB[0] * tableau_RGB[0];
                    tmp += 1;
                    *M0 += 1;
                    image_pixel_droite(img);
                }
                image_pixel_dessous(img);

                for (j = 0; j < nbr_colonne; j++){
                    *tableau_RGB = *image_lire_pixel(img);
                    GR += tableau_RGB[0];
                    GR2 += tableau_RGB[0] * tableau_RGB[0];
                    tmp+=1;
                    *M0 += 1;
                    image_pixel_gauche(img);
                }
                image_pixel_dessous(img);
            }
        }
        M1[0] = GR;
        M2[0] = GR2;
    }

}
