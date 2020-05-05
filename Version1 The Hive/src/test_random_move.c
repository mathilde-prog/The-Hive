#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));
  cell_t map[D][D];
  int quest_map[6][2];
  perso_t player;

  init_player(&player);
  map_init(map,quest_map,player);

  printf("Avant random_move : \n");
  printf("player.posY = %d\nplayer.posY = %d", player.posX, player.posY);

  random_move(&player,map);

  printf("\nAprès random move : \n");
  printf("player.posX = %d\nplayer.posY = %d\n", player.posX, player.posY);
}
