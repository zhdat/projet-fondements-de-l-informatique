/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.

-   * No portion of this document may be reproduced, copied
    
-   * or revised without written permission of the authors. */
    

/**

-   * @author Calliste RAVIX <calliste.ravix@ecole.ensicaen.fr>
    
-   * @author Maxime MICHEL <maxime.michel@ecole.ensicaen.fr> * @version 0.1.0 - 2023-01-05  
    *
    

* @todo Une meilleur gestion des images en niveau de gris * @bug Image au format ".pgm".
*/

/**  
* @file main.c  
*  
* Le but de ce programme est de ségmenter une image en différents blocks.
*/

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"
#include "fusion_iterative.h"

int main(int argc, char *argv[]) {
   #define USAGE "Usage : %s text_file\n"
   image img;
   rag r;
   int n;
   int m;
   double seuil;
   image img_out;

   if ((argc > 1) && (!strcasecmp("-h", argv[1]))) {
      fprintf(stderr, USAGE, argv[0]);
      return EXIT_FAILURE;
   }   

   if (argc != 5)
   {
      printf("Erreur : nombre d'arguments incorrect.\n");
      return 1;
   }
   img = FAIRE_image();
   image_charger(img, argv[1]);
   n = atoi(argv[2]);
   m = atoi(argv[3]);
   seuil = atof(argv[4]);
   r = create_RAG(img, n, m);
   perform_merge(r, seuil);
   img_out = create_output_image(r, atoi(argv[2]), atoi(argv[3]));
   image_sauvegarder(img_out, "output.ppm");
   free_RAG(r);
   return EXIT_SUCCESS;
}
