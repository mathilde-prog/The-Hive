#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/commun.h"

/**
 * \file fonctions_pratiques.c
 * \brief Fontions pratiques utilisées dans tout le code
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void entree_pour_continuer()
 * \brief Actionne la continuité du jeu par la touche "entrée".
 * \return Rien
*/
void entree_pour_continuer(){
  while(getchar() != '\n');
  printf("   >>> Appuyer sur la touche entrée pour continuer ");
  while(getchar() != '\n');
}

/**
 * \fn void clrscr()
 * \brief Efface la sortie du terminal, le remet à zéro.
 * \return Rien
*/
void clrscr(){ // fonction pour clear l'output de terminal
    system("clear");
}


/**
 * \fn int range(int a,int b)
 * \brief Génère un nombre aléatoire compris entre deux entiers passés en paramètre.
 * \param a Valeur min de l'intervalle (inclus)
 * \param b Valeur max de l'intervalle (inclus)
 * \return Retourne un \a int dans l'intervalle [a;b]
*/
int range(int a,int b){ // generates random number in range
  return (rand()%(b-a+1))+a;
}

/**
 * \fn int rng(int prob)
 * \brief Génère 0 ou 1 en fonction de la probabilité en pourcentage passée en paramètre.
 * \param prob Probabilité en pourcentage
 * \return Retourne un \a int : 1 ou 0.
*/
int rng(int prob){ // returns 0 or 1 with a given chance
  return (rand()%100)<prob;
}
