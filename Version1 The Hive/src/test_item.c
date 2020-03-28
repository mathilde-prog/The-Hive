// test_item.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

#define NB_SIMULATIONS 10

void display_position (cell_t map[D][D],perso_t player){
  printf("\n=== Où suis-je ? ===\n");
  printf("posX = %d\nposY = %d\n", player.posX, player.posY);
  printf("hex_t : ");
  switch(map[player.posX][player.posY].type){
    case prairie:     printf("prairie ");  break;
    case foret:       printf("foret ");    break;
    case ville:       printf("ville ");    break;
    case lac:         printf("lac ");      break;
    case camp_mil:    printf("camp_mil "); break;
    case camp_ban:    printf("camp_ban "); break;
    case market:      printf("market ");   break;
    case favella:     printf("favella ");  break;
    case montagne:    printf("montagne "); break;
    case frontiere:   printf("frontiere ");break;
    case mer:         printf("mer ");      break;
    case wasteland:   printf("wasteland ");break;
    default: break;
  }
  printf("\ncateg_hexa : ");
  switch(map[player.posX][player.posY].categ){
    case other:     printf("other\n");     break;
    case nature:    printf("nature\n");    break;
    case urbain:    printf("urbain\n");    break;
    case militaire: printf("militaire\n"); break;
    default: break;
  }
  printf("====================\n\n");
}

void simulation_suivante(){
  int rep;

  do {
    printf("Passer à la simulation suivante (1) : ");
    scanf("%d", &rep);
  } while (rep != 1);
}

int main(){
  srand(time(NULL));

  /* DECLARATIONS */
  int i, nb_items_available = 0;
  perso_t player;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  cell_t map[D][D];

  clrscr();

  // Creation des items
  if(creation_tab_item(Tab_Items, &nb_items_available)){
    init_player(&player);
    map_init(map);

    //display_TEXT(player.posX,player.posY, map);

    // SIMULATIONS
    for(i = 0; i < NB_SIMULATIONS; i++){
      player.posX = rand()%D;
      player.posY = rand()%D;

      printf("=== Simulation n°%d === \n", i+1);
      display_position(map,player);
      scavenge(map, &player, Tab_Items, nb_items_available);
      printf("\n");
      display_inventory(player);
      printf("\n");
      simulation_suivante();
      clrscr();
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

  free(Tab_Items);

  printf(">>> Fin du test\n");
  return EXIT_SUCCESS;
}
