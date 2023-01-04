/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/* Récupère le nom d'un image, le nombre de block en ligne et en colonne ainsi qu'un seuil dans argv[1], argv[2], argv[3] et argv[4]. 
Ce programme :
    - Crée un RAG à partir de l’image (qui aura été chargé à partir de son nom) et des nombres de blocks par lignes et colonnes.
    - Appelle la fonction perform merge, avec une valeur de seuil lue en paramètre. 
    - Récupère l’image résultat avec create output image et l’enregistre dans un fichier (on pourra plus simplement l’envoyer sur le flot de sortie stdout).
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"
#include "fusion_iterative.h"

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
   return EXIT_SUCCESS;
}
