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


        printf("Wow vous avez attrapé un poisson!\n");

        do {
          printf("Souhaitez-vous ajouter ce poisson à votre inventaire ? (Oui = 1, Non = 0)\n");
          scanf("%d",&rep);
          if (rep < 0 || rep > 1){
            printf("Valeur incorrecte. Veuillez resaissir.\n");
          }
        } while(rep < 0 || rep > 1);

        if(rep){
          add_item_to_inventory(player,*fish);
          sleep(2);
        }
      }
      else {
        printf("Rien ne mord...\n");
        sleep(2);
      }
    }
    else {
      printf("Tu ne peux pas pêcher sans canne à pêche!\n");
			sleep(2);
    }
  }
  else {
		if(item_in_inventory(*player, "fishing rod") != -1){
			printf("Vous ne pouvez pas utiliser votre canne à pêche ici...\n");
		}
		else {
			printf("Pour pêcher, vous avez besoin d'une canne à pêche!\n");
		}
    sleep(2);
  }
}

/*
int main(){

  item_t * pass = creer_item("pass",misc,0,0,0,0,0,0);
  display_item(*pass);
  perso_t player;
  player.nb_items_inventory = 0;

  add_item_to_inventory(&player,*pass);
  display_inventory(player);

  srand(time(NULL));
  perso_t player;
  cell_t map[D][D];
  init_player(&player);
  map_init(map);
  player.nb_items_inventory = 0;
  item_t * fishing_rod = creer_item("fishing_rod",misc,0,0,0,0,0,0);
  add_item_to_inventory(&player,*fishing_rod);
  display_inventory(player);

  map[player.posX][player.posY].type = mer;
  fish(&player,map);
  display_inventory(player);

  display_item(player.inventory[1]);
  printf("index: %d\n", player.inventory[1].index);
  display_inventory(player);
  delete_item_in_inventory(&player,player.inventory[0]);
  display_inventory(player);
  return EXIT_SUCCESS;
}
*/
