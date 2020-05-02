#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file fish.c
 * \brief Fonctionnalité : pêcher
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void fish (perso_t * player, cell_t map[D][D])
 * \brief Permet au joueur de pêcher s'il se situe sur un hexagone de type \a lac ou \a mer et s'il a une canne à pêche dans son inventaire.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Rien
*/
void fish (perso_t * player, cell_t map[D][D]){
  int rep;

  if((map[player->posX][player->posY].type == lac) || (map[player->posX][player->posY].type == mer)){
    if(item_in_inventory(*player, "fishing rod") != -1){
      int chance = rng(30); // 30% de chance d'attraper un poisson
      if(chance){
        item_t * fish = creer_item("fish",food,0,0,0,0,0,0,0,0,0,0,0);
        printf("\n   Wow vous avez attrapé un poisson!\n");
        printf("   Souhaitez-vous ajouter ce poisson à votre inventaire ? (Oui = 1, Non = 0)\n");
        do {
          scanf("%d",&rep);
          if (rep < 0 || rep > 1){
            printf("Valeur incorrecte. Veuillez resaissir : ");
          }
        } while(rep < 0 || rep > 1);

        if(rep){
          add_item_to_inventory(player,*fish);
          sleep(2);
        }
      }
      else {
        printf("\n   Rien ne mord...\n");
        sleep(2);
      }
    }
    else {
      printf("\n   Vous ne pouvez pas pêcher sans canne à pêche!\n");
			sleep(2);
    }
  }
  else {
		if(item_in_inventory(*player, "fishing rod") != -1){
			printf("\n   Vous ne pouvez pas utiliser votre canne à pêche ici...\n");
		}
		else {
			printf("\n   Pour pêcher, vous avez besoin d'une canne à pêche!\n");
		}
    sleep(2);
  }
}
