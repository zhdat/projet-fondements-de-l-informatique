#include <stdio.h>
#include <stdlib.h>
#include "RAG.h"
#include "moment.h"
#include "image.h"
#include "fusion_iterative.h"

 /* Récupère le nom d'un image, le nombre de block en ligne et en colonne ainsi qu'un seuil dans argv[1], argv[2], argv[3] et argv[4]. 
Ce programme :
    - Crée un RAG à partir de l’image (qui aura été chargé à partir de son nom) et des nombres de blocks par lignes et colonnes.
    - Appelle la fonction perform merge, avec une valeur de seuil lue en paramètre. 
    - Récupère l’image résultat avec create output image et l’enregistre dans un fichier (on pourra plus simplement l’envoyer sur le flot de sortie stdout).*/
int main(int argc, char *argv[]){
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
    img = image_charger(argv[1]);
    n = atoi(argv[2]);
    m = atoi(argv[3]);
    seuil = atof(argv[4]);
    r = create_RAG(img, n, m);
    perform_merge(r, seuil);
    img_out = create_output_image(r);
    image_sauvegarder(img_out, "output.ppm");
    return 0;
}
