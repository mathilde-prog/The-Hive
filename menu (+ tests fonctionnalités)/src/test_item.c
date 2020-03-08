// test_item.c 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

#define NB_SIMULATIONS 10

void display_position (int map[D][D],perso_t player){
  printf("\n=== Where am I ? ===\n");
  printf("posX = %d\nposY = %d\n", player.posX, player.posY);
  printf("Type hexagone: ");
  switch(map[player.posX][player.posY]){
    case prairie   : printf("prairie [NATURE]\n"); break;     //prairie
    case foret     : printf("foret [NATURE]\n");    break;     //foret
    case ville     : printf("ville [URBAIN]\n");    break;     //ville
    case lac       : printf("lac [NATURE]\n");     break;     //lac
    case camp_mil  : printf("camp_mil [MILITAIRE]\n");  break;     //camp mil
    case camp_ban  : printf("camp_ban [OTHER]\n");     break;     //camp_ban
    case market    : printf("market [URBAIN]\n");   break;     //market
    case favella   : printf("favella [URBAIN]\n");   break;     //favella
    case montagne  : printf("montagne [NATURE]\n");     break;     //montagne
    case frontiere : printf("frontiere [OTHER]\n");      break;     //frontiere
    case mer       : printf("mer [NATURE]\n");   break;     //mer
    case wasteland : printf("wasteland [NATURE]\n");    break;     //wasteland
  }
  printf("====================\n\n");
}

int main(){
  srand(time(NULL));

  /* DECLARATIONS */
  perso_t player;
  /* INITIALISATION JOUEUR (DANS MAIN POUR SIMULATION) */
  player.turns = 15;
  player.nb_items_inventory = 0; /* The player starts the game with an empty inventory. */
  player.posX = 0;
  player.posY = 0;
  player.pv = 100;
  player.pe = 100;
  player.pa = 3;
  player.left_hand = NULL;
  player.right_hand = NULL;
  player.body = NULL;
  player.head = NULL;
  player.competence  = 0;

  int map[D][D]={{0}};
  item_t Tab_Items[20];
  int i, nb_items_available = 0;

  clrscr();
  printf("=== WELCOME - THE HIVE! ===\n");

  // Creation des items
  if(creation_tab_item(Tab_Items, &nb_items_available)){
    map_init(map);
    display_TEXT(player.posX,player.posY, map);

    // SIMULATIONS
    for(i = 0; i < NB_SIMULATIONS; i++){
      player.posX = rand()%D;
      player.posY = rand()%D;
      display_position(map,player);

      printf("=== SIMULATION N°%d === \n", i+1);
      scavenge(map, &player, Tab_Items, nb_items_available);
      printf("\n");
      display_inventory(player);
      printf("\n");
    }
  }

  /* Free memory */
  player.left_hand = NULL;
  player.right_hand = NULL;
  player.body = NULL;
  player.head = NULL;

  free(player.left_hand);
  free(player.right_hand);
  free(player.body);
  free(player.head);

  printf("See you next time!\n");
  return EXIT_SUCCESS;
}
