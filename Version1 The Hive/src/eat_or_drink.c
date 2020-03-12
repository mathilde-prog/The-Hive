//eat_or_drink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/* eat_or_drink: allows the player to drink or eat an item (if type food) and to recover pe and pv when it's possible */
void eat_or_drink (perso_t * player, item_t item){
  if(item.type == food){
    printf("This %s was delicious! ",item.name);
    if(!strcmp(item.name,"fruits")){
      player->pe += 10;
      printf("You've gained 10 energy points!\n");
    }
    else if(!strcmp(item.name,"fish")){
      player->pe += 15;
      printf("You've gained 15 energy points!\n");
    }
    else if (!strcmp(item.name,"can_food")){
      player->pe += 50;
      printf("You've gained 50 energy points!\n");
    }
    else if(!strcmp(item.name,"energy_drink")){
      if(player->pa < 5){
        player->pa++;
        printf("You've gained 1 action point!\n");
      }
      player->pe += 20;
      printf("You've gained 20 energy points!\n");
    }
    else if(!strcmp(item.name,"bottle_water")){
      player->pe += 10;
      printf("You've gained 10 energy points!\n");
    }
    delete_item_in_inventory(player, item);
  }
  else {
    printf("You can't eat or drink it!\n\n");
  }
}
