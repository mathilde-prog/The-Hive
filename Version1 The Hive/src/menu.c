#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

perso_t player;
int map[D][D]={{0}};
item_t Tab_Items[20];
int nb_items_available = 0;

void next_turn(perso_t * player){
  player->pa = 5; //Récupère ses 5 points d'actions
  player->turns--;
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

int main(){
  int choise;
  srand(time(NULL));
  clrscr();

  // Creation items
  if(creation_tab_item(Tab_Items, &nb_items_available)){

    // Start a new game or continue if saved game
    if(init_or_load_game(&player,map)){
      clrscr();

      while(player.turns != 0 && player.pv != 0){

        display_player_characteristics(map, player);

        printf("Available actions:\n");
        printf("1 - Scavenge\n");
        printf("2 - Inventory\n");
        printf("3 - Equipment\n");
        printf("4 - Move to another place\n");
        printf("5 - Check the map (map needed)\n");
        printf("6 - Rest and heal\n");
        printf("7 - End turn\n");
        printf("8 - Save the game and exit\n");
        printf("9 - Help\n");
        printf("Exit: -1\n");
        printf("\nWhat you plan to do? ");

        jump:
        scanf("%d",&choise);
        switch(choise){
          case 1: clrscr(); scavenge(map,&player,Tab_Items,nb_items_available); clrscr(); break;
          case 2: clrscr(); manage_inventory(&player); clrscr(); break;
          case 3: clrscr(); manage_equipment(&player); clrscr(); break;
          case 4: clrscr(); move(&player, map); clrscr(); break;
          case 5: clrscr(); if(map_in_inventory(player)){
                              display_TEXT(player.posX, player.posY ,map);
                            }
                            else {
                              printf("You need to have a map in your inventory.\n");
                              sleep(2);
                            }
                            clrscr(); break;
          case 6: clrscr(); rest_and_heal(&player); clrscr(); break;
          case 7: clrscr(); next_turn(&player); break;
          case 8: clrscr(); save(player,map); exit(1);break;
          case 9: clrscr(); help(&player); clrscr(); break;
          case -1: exit(1); break;
          default: printf("Command not found. Try again: "); goto jump; break;
        }
      }

      if(!player.turns){
        printf("You didn't have time to go out...\n");
      }
      if(!player.pv){
        printf("You're dead.\n");
      }
      sleep(2);
      clrscr();
    }
  }
}
