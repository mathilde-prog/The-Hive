#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

int exit_game(){
    int rep;
    printf("Vous venez de trouver la sortie ! Souhaitez-vous quitter la map ? : (0: Non | 1: Oui) \n");
    scanf("%d", &rep);
    if (rep == 0){
        printf ("Vous êtes courageux ! L'aventure continue !\n");
        return 0;
    }
    else {
        printf("Félicitation pour votre parcours, vous pouvez maintenant vivre sans craindre pour votre vie ! \n A bientôt peut-être, pour de nouvelles aventures !");
        return 1;
    }
}

void help(perso_t * player){
  int i = 1, nb;

  if(!map_in_inventory(*player)){
    printf("Advice N°%d - Having a map would be helpful!\n",i++);
    printf("You can find one in these kind of places : city, military camp, market, favella.\n");
  }

  if(i == 1){
    printf("No advice\n");
  }
  do {
    printf("\nBack to the menu (1) : ");
    scanf("%d",&nb);
    if(nb != 1){
      printf("Type 1 to return to the inventory menu\n");
    }
  } while (nb != 1);
}
