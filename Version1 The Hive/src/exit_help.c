#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

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

void help(perso_t * player){
  int i = 1, nb;

  if(!map_in_inventory(*player)){
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
