#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void init_player(perso_t * player){
  int comp;
  
  player->turns = 15;
  player->nb_items_inventory = 0; /* The player starts the game with an empty inventory. */
  player->posX = 0; /* A voir */
  player->posY = 0; /* A voir */
  player->pv = 100;
  player->pe = 100;
  player->pa = 3;
  player->left_hand = NULL;
  player->right_hand = NULL;
  player->body = NULL;
  player->head = NULL;

  do {
    printf("Which skill do you want for your character? (normal = 0, sprinter = 1, metabolism = 2, luck = 3, scout = 4)\n");
    scanf("%d",&comp);
    if(comp < 0 || comp > 4){
      printf("Incorrect value (value must be between 0 and 4)\n");
    }
  } while(comp < 0 || comp > 4);
  player->competence = comp;
}

void display_player_characteristics(perso_t player){
  printf("\n======== INFO PLAYER ========\n");
  printf("PV = %3d  PE = %3d  PA = %3d\n",player.pv,player.pe,player.pa);
  printf("Position joueur:  x = %d  y = %d\n",player.posX,player.posY);
  printf("Compétence: ");
  switch(player.competence){
    case normal: printf("normal\n"); break;
    case sprinter: printf("sprinter\n"); break;
    case metabolism: printf("metabolism\n"); break;
    case luck: printf("luck\n"); break;
    case scout: printf("scout\n"); break;
    default: printf("unrecognized\n"); break;
  }
  printf("=============================\n\n");

}
