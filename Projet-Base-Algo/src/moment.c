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
    int R;
    int G;
    int B;
    int GR;
    int R2;
    int G2;
    int B2;
    int GR2;
    int tableau_RGB[3];

    
    nbr_colonne = (int)(img->largeur / n);
    nbr_ligne = (int)(img->hauteur / m);
    pixel_start_x = nbr_colonne * num_bloc % m;
    pixel_start_y = nbr_ligne * num_bloc / m;
    nbr_pixel = nbr_colonne * nbr_ligne;
    tmp = 0;
    *M0 = 0;
    *M1 = 0;
    *M2 = 0;

    COORDX(p) = pixel_start_x;
    COORDY(p) = pixel_start_y;
    image_move_to(img, &p);

    if (image_give_dim(img) == 3){
        while (tmp < nbr_pixel)
        {
            for (i = 0; i < nbr_ligne; i++){
                for (j = 0; j < nbr_colonne; j++){
                    *tableau_RGB = *image_lire_pixel(img);
                    R += tableau_RGB[0];
                    R2 += tableau_RGB[0] * tableau_RGB[0];
                    G += tableau_RGB[1];
                    G2 += tableau_RGB[1] * tableau_RGB[1];
                    B += tableau_RGB[2];
                    B2 += tableau_RGB[2] * tableau_RGB[2];
                    tmp += 1;
                    *M0 += 1;
                    image_pixel_droite(img);
                }
                image_pixel_dessous(img);

                for (j = 0; j < nbr_colonne; j++){
                    *tableau_RGB = *image_lire_pixel(img);
                    R += tableau_RGB[0];
                    R2 += tableau_RGB[0] * tableau_RGB[0];
                    G += tableau_RGB[1];
                    G2 += tableau_RGB[1] * tableau_RGB[1];
                    B += tableau_RGB[2];
                    B2 += tableau_RGB[2] * tableau_RGB[2];
                    tmp+=1;
                    *M0 += 1;
                    image_pixel_gauche(img);
                }
                image_pixel_dessous(img);
            }
        }
    } else{
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
    }
    M1[1] = R;
    M1[2] = G;
    M1[3] = B;
    M2[1] = R2;
    M2[2] = G2;
    M2[3] = B2;
}