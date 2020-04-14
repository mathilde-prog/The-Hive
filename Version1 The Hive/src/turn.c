#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/* Passer au prochain tour */
void next_turn(perso_t * player){
  printf("On passe au tour suivant!\n");
  printf("Vous récupérez %d points d'action!\n", 5-player->pa);
  player->pa = 5; //Récupère 5 points d'actions
  player->turns--;
  sleep(2);
}

/* rest_and_heal: allows the player to rest and gain pv and pe (proportionate to his number of pa) */
void rest_and_heal(perso_t * player){
  int value_pv = player->pa*5;
  int value_pe = player->pa*5;

  printf("Reposez vous un instant zzZZ\n");
  sleep(1);

  /* PV */
  if((player->pv + value_pv) > 100){
    value_pv = (100 - player->pv);
  }
  player->pv += value_pv;

  /* PE */
  if((player->pe + value_pe) > 100){
    value_pe = (100 - player->pe);
  }
  player->pe += value_pe;

  printf("PV +%d\tPE +%d\n",value_pv,value_pe);
  sleep(2);
  next_turn(player);
}

/* Recherche des items */
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available){
    categ_hexa categ = map[player->posX][player->posY].categ;

    // Si le joueur n'a pas déjà scavengé l'hexagone où il est
    if(map[player->posX][player->posY].scavenged == 1){
      printf("Tu es déjà passé par là!\n");
      sleep(2);
    }
    else {
      if(categ != other){
        generate_items(Tab_Items, nb_items_available, player, categ);
      }
      else { // Aucun item généré
        printf("Rien n'apparaît!\n");
        sleep(2);
      }
      map[player->posX][player->posY].scavenged = 1;
    }
}
