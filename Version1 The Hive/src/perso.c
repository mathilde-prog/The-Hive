#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/structure.h"

/**
 * \file perso.c
 * \brief Fonctions relatives au joueur
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void init_player(perso_t * player, cell_t map[D][D])
 * \brief Initialise les paramètres du joueur quand il commence le jeu
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Rien
*/
void init_player(perso_t * player, cell_t map[D][D]){
  player->turns = 15;
  player->nb_items_inventory = 0; /* Le joueur commence la partie avec un inventaire vide. */

  // Impossible pour le joueur de commencer une partie par un combat ou une quête
  do{
    player->posY = rand()%D;
    player->posX = rand()%D;
  } while((map[player->posY][player->posX].encounter == 1) || (map[player->posY][player->posX].quest_id != 0));

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

/**
 * \fn void display_player_characteristics(cell_t map[D][D], perso_t player)
 * \brief Affiche les paramètres du joueur (points de vie, points d'énergie, points d'action, position sur la carte, nombre de tours restants)
 * \param cell_t map[D][D]
 * \param perso_t player
 * \return Rien
*/
void display_player_characteristics(cell_t map[D][D], perso_t player){
  printf("\n   ================================== INFO JOUEUR =====================================\n");
  printf("   PV = %3d  PE = %3d  PA = %3d\n",player.pv,player.pe,player.pa);
  printf("   Position joueur:  x = %d  y = %d  ",player.posX,player.posY);
  afficher_type_categ_hexa(map,player.posY,player.posX);

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
  printf("   Il vous reste actuellement %d tours avant qu'il ne soit trop tard pour vous enfuir.\n", player.turns);
  printf("   ====================================================================================\n\n");
}
