#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

/* init_player: initializes the player's settings when he starts the game */
void init_player(perso_t * player){
  player->turns = 15;
  player->nb_items_inventory = 0; /* The player starts the game with an empty inventory. */
  player->posX = rand()%D;
  player->posY = rand()%D;
  player->pv = 100;
  player->pe = 100;
  player->pa = 5;
  player->left_hand = NULL;
  player->right_hand = NULL;
  player->body = NULL;
  player->head = NULL;

  /* No special competence for version 1 */
  /*
  do {
    printf("Which skill do you want for your character? (normal = 0, sprinter = 1, metabolism = 2, luck = 3, scout = 4)\n");
    scanf("%d",&comp);
    if(comp < 0 || comp > 4){
      printf("Incorrect value (value must be between 0 and 4)\n");
    }
  } while(comp < 0 || comp > 4);
  player->competence = comp;
  */
}

/* display_player_characteristics: displays the player parameters (pv,pe,pa,location,turns) */
void display_player_characteristics(cell_t map[D][D], perso_t player){
  printf("========================= INFO PLAYER ============================\n");
  printf("PV = %3d  PE = %3d  PA = %3d\n",player.pv,player.pe,player.pa);
  printf("Position player:  x = %d  y = %d  ",player.posX,player.posY);
  switch(map[player.posX][player.posY].type){
    case prairie   : printf("prairie "); break;
    case foret     : printf("foret ");    break;
    case ville     : printf("ville ");    break;
    case lac       : printf("lac ");     break;
    case camp_mil  : printf("camp_mil ");  break;
    case camp_ban  : printf("camp_ban ");     break;
    case market    : printf("market ");   break;
    case favella   : printf("favella ");   break;
    case montagne  : printf("montagne ");     break;
    case frontiere : printf("frontiere ");      break;
    case mer       : printf("mer ");   break;
    case wasteland : printf("wasteland ");    break;     
  }
  switch(map[player.posX][player.posY].categ){
    case other   : printf("[OTHER]\n"); break;
    case nature  : printf("[NATURE]\n"); break;
    case urbain  : printf("[URBAIN]\n"); break;
    case militaire : printf("[MILITAIRE]\n");  break;
  }

  /* No special competence for version 1 */
  /*
  printf("Competence: ");
  switch(player.competence){
    case normal: printf("normal\n"); break;
    case sprinter: printf("sprinter\n"); break;
    case metabolism: printf("metabolism\n"); break;
    case luck: printf("luck\n"); break;
    case scout: printf("scout\n"); break;
    default: printf("unrecognized\n"); break;
  }
  */
  printf("You currently have %d turns left before it is too late to escape.\n", player.turns);
  printf("==================================================================\n\n");
}
