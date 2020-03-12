#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/* Passer au prochain tour */
void next_turn(perso_t * player){
  player->pa = 5; //Récupère 5 points d'actions
  player->turns--;
}

/* rest_and_heal: allows the player to rest and gain pv and pe (proportionate to his number of pa) */
void rest_and_heal(perso_t * player){
  int value = player->pa * 5;

  printf("Let's take some rest zzZZ\n"); sleep(1);
  player->pv += value;
  player->pe += value;
  printf("PV +%d\tPE +%d\n",value,value);
  sleep(2);
}

/* Recherche des items */
void scavenge(int map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available){
    categ_hexa categ = category_hexagon(map, player->posX, player->posY);

    if(categ != other){
      generate_items(Tab_Items, nb_items_available, player, categ);
    }
    else { // Aucun item généré si frontière ou
      printf("Nothing appears!\n");
      sleep(2);
    }
}
