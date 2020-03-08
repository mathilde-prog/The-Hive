#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

perso_t player;
int map[D][D]={{0}};
item_t Tab_Items[20];
int nb_items_available = 0;

int exit_ok(){
  return 0;
}

void move(){
  printf("\nok\n");
}

void heal(){
  printf("\nok\n");
}

void next_turn(){
  printf("\nok\n");
}

void help(){
  printf("\nok\n");
}

int main(){
  int choise;
  srand(time(NULL));
  clrscr();

  // Creation items
  if(creation_tab_item(Tab_Items, &nb_items_available)){

    // Start a new game or continue if saved game
    if(init_or_load_game(&player,map)){
      while(player.turns !=0 || exit_ok()){

        display_player_characteristics(map, player);

        printf("Available actions:\n");
        printf("1 - Look around\n");
        printf("2 - Scavenge\n");
        printf("3 - Inventory\n");
        printf("4 - Equipment\n");
        printf("5 - Move to another place\n");
        printf("6 - Check the map (map needed)\n");
        printf("7 - Rest and heal\n");
        printf("8 - End turn\n");
        printf("9 - Save the game and exit\n");
        printf("10 - Help\n");
        printf("Exit: -1\n");
        printf("\nWhat you plan to do? ");

        jump:
        scanf("%d",&choise);
        switch(choise){
          case 1: clrscr(); look_around(player.posY, player.posX, map); break;
          case 2: clrscr(); scavenge(map,&player,Tab_Items,nb_items_available); break;
          case 3: clrscr(); manage_inventory(&player); break;
          case 4: clrscr(); manage_equipment(&player); break;
          case 5: clrscr(); move(); break;
          case 6: clrscr(); display_TEXT(player.posX, player.posY ,map); break;
          case 7: clrscr(); heal(); break;
          case 8: clrscr(); next_turn(); break;
          case 9: clrscr(); save(player,map); exit(1);break;
          case 10: clrscr(); help(); break;
          case -1: exit(1); break;
          default: printf("Command not found. Try again: "); goto jump; break;
        }
      }
    }
  }
}
