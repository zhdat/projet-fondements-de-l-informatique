#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "moment.h"

extern void give_moments(image img, int num_bloc, int n, int m, int* zero, double* un, double* deux){
    *zero = n * m;
    
    point p;
    int i;
    int j;
    p->coordx = (Largeur/n * (num_bloc % m));
    p->coordy = (Hauteur/n * (num_bloc / m));
    image_move_to(img, p);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            *un = *un + *(double *)image_lire_pixel(img);
            image_pixel_suivant(img);
        }
    }
    
    p->coordx = (Largeur/n * (num_bloc % m));
    p->coordy = (Hauteur/n * (num_bloc / m));
    image_move_to(img, p);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            *un = *un + *(double *)image_lire_pixel(img) * *(double *)image_lire_pixel(img);
            image_pixel_suivant(img);
        }
    }
}