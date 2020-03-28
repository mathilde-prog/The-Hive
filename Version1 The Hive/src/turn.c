#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/* Passer au prochain tour */
void next_turn(perso_t * player, int * nb_rh){
  *nb_rh = 0;
  printf("On passe au tour suivant!\n");
  printf("Vous récupérez %d points d'action!\n", 5-player->pa);
  player->pa = 5; //Récupère 5 points d'actions
  player->turns--;
  sleep(2);
}

/* rest_and_heal: allows the player to rest and gain pv and pe (proportionate to his number of pa) */
void rest_and_heal(perso_t * player, int * nb_rh){
  int value = player->pa * 5;

  if((*nb_rh) == 0){
    printf("Reposez vous un instant zzZZ\n"); sleep(1);
    player->pv += value;
    player->pe += value;
    printf("PV +%d\tPE +%d\n",value,value);
    *nb_rh = 1;
  }
  else {
    printf("Vous vous êtes déjà reposé pendant ce tour!\n");
  }

  sleep(2);
}

/* Recherche des items */
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available){
    categ_hexa categ = map[player->posX][player->posY].categ;

    if(categ != other){
      generate_items(Tab_Items, nb_items_available, player, categ);
    }
    else { // Aucun item g�n�r� si fronti�re ou
      printf("Nothing appears!\n");
      sleep(2);
    }
}
