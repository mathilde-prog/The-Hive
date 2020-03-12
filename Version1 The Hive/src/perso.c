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
void display_player_characteristics(int map[D][D], perso_t player){
  printf("========================= INFO PLAYER ============================\n");
  printf("PV = %3d  PE = %3d  PA = %3d\n",player.pv,player.pe,player.pa);
  printf("Position player:  x = %d  y = %d  ",player.posX,player.posY);
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
