#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "moment.h"
#include "objet.h"
#include "point.h"
#include "image.c"

extern void give_moments(image img, int num_bloc, int n, int m, int* M0, double* M1, double* M2){
    
    int i;
    int j;
    int nbr_ligne; // Ligne du block
    int nbr_colonne; // Colonne du block
    int pixel_start_x;
    int pixel_start_y;
    int pixel_end_x;
    int pixel_end_y;

    
    nbr_colonne = img->largeur / n;
    nbr_ligne = img->hauteur / m;
    pixel_start_x = nbr_colonne * i % m;
    pixel_start_y = nbr_ligne * i / m;
    pixel_end_x = (nbr_colonne + 1) * i % m; // A revoir !
    pixel_end_y = (nbr_ligne + 1) * i / m; // A revoir !
    
    *M0 = 0;
    *M1 = 0;
    *M2 = 0;
    
    for (i = pixel_start_x; i < pixel_end_x; i++) {
        for (j = pixel_start_y; j < pixel_end_y; j++) {
            *M0 += 1;
            *M1 += image_lire_pixel(img);
            *M2 += image_lire_pixel(img) * image_lire_pixel(img);
        }
    }
    
    
    
}