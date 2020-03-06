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

void scavenge(){
  printf("\nok\n");
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

void save(){
  printf("\nok\n");
}

int main(){

  int turns=15;
  int choise;
  clrscr();
  map_init(map);
  creation_tab_item(Tab_Items, &nb_items_available);
  while(turns!=0 || exit_ok()){
    printf("Character info:\nPV: %d/100\nPA: %d/5\nEnergie: %d/100\n\nYou currently have %d turns left befoe it is too late to escape.\n\nAvailable actions:\n1 - Look around\n2 - Scavenge\n3 - Inventory\n4 - Move to another place\n5 - Check the map (map needed)\n6 - Rest and heal\n0 - End turn\n66 - Save the game and exit\n13 - Help\n\nWhat you plan to do? ",player.pv, player.pa, player.pe, turns);
    jump:
    scanf("%d",&choise);
    switch(choise){
      case 1: clrscr(); look_around(player.posY, player.posX, map); break;
      case 2: clrscr(); items_generer(Tab_Items, nb_items_available, militaire); break;
      case 3: clrscr(); display_inventory(player); break;
      case 4: clrscr(); move(); break;
      case 5: clrscr(); display_TEXT(player.posY, player.posX ,map); break;
      case 6: clrscr(); heal(); break;
      case 0: clrscr(); next_turn(); break;
      case 13: clrscr(); help(); break;
      case 66: clrscr(); save(); break;
      case -1: exit(1); break;
      default: printf("Command not found. Try again: "); goto jump; break;
    }
  }
}
