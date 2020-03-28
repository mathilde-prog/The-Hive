//eat_or_drink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/* eat_or_drink: allows the player to drink or eat an item (if type food) and to recover pe and pv when it's possible */
void eat_or_drink (perso_t * player, item_t item){
  if(item.type == food){
    if(!strcmp(item.name,"fruits")){
      player->pe += 10;
      printf("Vous gagnez 10 points d'énergie.\n");
    }
    else if(!strcmp(item.name,"fish")){
      player->pe += 15;
      printf("Vous gagnez 15 points d'énergie.\n");
    }
    else if (!strcmp(item.name,"can_food")){
      player->pe += 50;
      printf("Vous gagnez 50 points d'énergie.\n");
    }
    else if (!strcmp(item.name,"soda")){
      player->pe += 12;
      printf("Vous gagnez 12 points d'énergie.\n");
    }
    else if(!strcmp(item.name,"energy_drink")){
      if(player->pa < 5){
        player->pa++;
        printf("Vous gagnez 1 point d'action.\n");
      }
      player->pe += 20;
      printf("Vous gagnez 20 points d'énergie.\n");
    }
    else if(!strcmp(item.name,"bottle_water")){
      player->pe += 10;
      printf("Vous gagnez 10 points d'énergie.\n");
    }
    delete_item_in_inventory(player, item);
  }
  else {
    printf("Tu ne peux pas manger ou boire ça!\n\n");
  }
}
