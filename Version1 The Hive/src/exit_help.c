#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file exit_help.c
 * \brief Sortie + Aide 
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/

/**
 * \fn int exit_game()
 * \brief Propose au joueur de quitter ou non la carte lorsqu'il vient de trouver la sortie.
 * \return Un \a int : 1 si le joueur décide de quitter la carte. 0 s'il décide de continuer l'aventure.
*/
int exit_game(){
    int rep;

    printf("Vous venez de trouver la sortie ! Souhaitez-vous quitter la map ? (Oui = 1, Non = 0)\n");
    scanf("%d", &rep);
    if (rep == 0){
        printf ("Vous êtes courageux ! L'aventure continue !\n");
        return 0;
    }
    else {
        printf("Félicitation pour votre parcours, vous pouvez maintenant vivre sans craindre pour votre vie ! \n A bientôt peut-être, pour de nouvelles aventures !\n");
        return 1;
    }
}

/**
 * \fn void help(perso_t * player)
 * \brief Donne des conseils au joueur suivant ses difficultés
 * \param perso_t * player 
 * \return Rien
*/
void help(perso_t * player){
  int i = 1, nb;

  if(!item_in_inventory(*player,"map")){
    printf("Conseil N°%d - Posséder une carte serait utile!\n",i++);
    printf("Essayez de vous rendre dans une ville, un camp militaire, un marché ou une favella. Vous aurez plus de chances d'en trouver une!\n");
  }

  if(i == 1){
    printf("Aucun conseil\n");
  }
  do {
    printf("\nRetour au menu (1) : ");
    scanf("%d",&nb);
    if(nb != 1){
      printf("Saisissez 1 pour retourner au menu\n");
    }
  } while (nb != 1);
}
