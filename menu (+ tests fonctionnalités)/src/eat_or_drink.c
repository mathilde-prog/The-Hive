//eat_or_drink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void eat_or_drink (perso_t * player, item_t item){
  if(item.type == food){
    if(!strcmp(item.name,"fruits")){
      player->pe += 10;
    }
    else if(!strcmp(item.name,"fish")){
      player->pe += 15;
    }
    else if (!strcmp(item.name,"can_food")){
      player->pe += 50;
    }
    else if(!strcmp(item.name,"energy_drink")){
      player->pa += 1;
      player->pe += 20;
    }
    else if(!strcmp(item.name,"bottle_water")){
      player->pe += 10;
    }
    delete_item_in_inventory(player, item);
  }
  else {
    printf("You can't eat or drink it!\n");
  }
}
