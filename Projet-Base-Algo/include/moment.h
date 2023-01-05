/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

#ifndef MOMENT_H
#define MOMENT_H
#include "image.h"

/**  
* Cette fonction calcule les moments d'ordre 0, 1 et 2 des pixels situés dans un rectangle.  
*  
* @param img une image dans laquel se trouve les pixels. 
* @param num_bloc correspond au numéro du bloc.
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par ligne.
* @param M0 pointeur vers moment zéro qui correspond au nombre de pixels dans le block.
* @param M1 pointeur vers moment d'ordre 1 qui correspond à la somme des intensités (ou couleurs) des pixels dans le block.
* @param M2 pointeur vers moment d'ordre 2 qui correspond à la somme des carrés des intensités (ou couleurs) des pixels dans le block.  
*/
extern void give_moments(image img, int num_bloc, int n, int m, int* M0, double* M1, double* M2);
#endif
