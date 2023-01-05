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
    

* @todo the list of improvements suggested * @bug the list of known bugs.  
*/

/**  
* @file main.c  
*  
* Description of the program objectives. * All necessary references.  
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"
#include "fusion_iterative.h"


/**  
* A complete description of the function.  
*  
* @param par1 description of the parameter par1. * @param par2 description of the parameter par2. * @return description of the result.  
*/
int main(int argc, char *argv[]) {
   #define USAGE "Usage : %s text_file\n"

   if ((argc > 1) && (!strcasecmp("-h", argv[1]))) {
      fprintf(stderr, USAGE, argv[0]);
      return EXIT_FAILURE;
   }   
   
   image img;
   rag r;
   int n;
   int m;
   double seuil;
   image img_out;

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
   img_out = create_output_image(r);
   image_sauvegarder(img_out, "output.ppm");
   free_RAG(r);
   return EXIT_SUCCESS;
}
