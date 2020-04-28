#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/**
 * \file backup_and_load.c
 * \brief Sauvegarde et chargement d'une partie
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/******************** BACK_UP *************************/

/**
 * \fn void save (perso_t player, cell_t map[D][D])
 * \brief Sauvegarde les informations sur le joueur, son inventaire, son équipement et la carte
 * \param perso_t player
 * \param cell_t map[D][D]
 * \return Rien
*/
/* save: save information about the character, his inventory, his equipment and the map. */
void save (perso_t player, cell_t map[D][D]){
  save_info_player(player);
  save_inventory(player);
  save_equipment(player);
  save_map(map);
  printf("Sauvegarde réussie\n");
}

/**
 * \fn void save_inventory (perso_t player)
 * \brief Sauvegarde l'inventaire du joueur dans un fichier 'save_inventory.csv'
 * \param perso_t player
 * \return Rien
*/
/* save_inventory: saves the player's inventory */
void save_inventory (perso_t player){
  int i;

  FILE * fic = fopen("../sauv/save_inventory.csv","w");
  for(i = 0; i < player.nb_items_inventory; i++){
    fprintf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%s",player.inventory[i].type, player.inventory[i].attack[0], player.inventory[i].attack[1],player.inventory[i].attack[2], player.inventory[i].hitchance[0], player.inventory[i].hitchance[1],player.inventory[i].hitchance[2],player.inventory[i].defense, player.inventory[i].equipable, player.inventory[i].pc_nature, player.inventory[i].pc_urban, player.inventory[i].pc_military, player.inventory[i].name);
    fprintf(fic,"\n");
  }
  fclose(fic);
}

/**
 * \fn void save_info_player (perso_t player)
 * \brief Sauvegarde les informations du joueur dans un fichier 'save_info_player.'
 * \param perso_t player
 * \return Rien
*/
/* save_info_player: saves player information */
void save_info_player (perso_t player){
  FILE * fic = fopen("../sauv/save_info_player.csv","w");
  fprintf(fic,"pv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n", player.pv, player.pe, player.pa, player.posX, player.posY, player.turns);

  /* No special competence for version 1 */
  //fprintf(fic,"competence = %d\n", player.competence);

  fclose(fic);
}

/**
 * \fn void save_equipment (perso_t player)
 * \brief Sauvegarde l'équipement du joueur dans un fichier 'save_equipment.csv'
 * \param perso_t player
 * \return Rien
*/
/* save_equipment: saves the player's equipment */
void save_equipment (perso_t player){
  FILE * fic = fopen("../sauv/save_equipment.csv","w");

  (player.head != NULL) ? fprintf(fic, "head;%d\n", player.head->index) : fprintf(fic, "head;-1\n");
  (player.left_hand != NULL) ? fprintf(fic, "left hand;%d\n", player.left_hand->index) : fprintf(fic, "left hand;-1\n");
  (player.right_hand != NULL) ? fprintf(fic, "right hand;%d\n", player.right_hand->index) : fprintf(fic, "right hand;-1\n");
  (player.body != NULL) ? fprintf(fic, "body;%d\n", player.body->index) : fprintf(fic, "body;-1\n");

  fclose(fic);
}

/**
 * \fn void save_map (cell_t map[D][D])
 * \brief Sauvegarde la carte dans un fichier 'save_map.csv'
 * \param cell_t map[D][D]
 * \return Rien
*/
/* save_map: save the map of the game */
void save_map (cell_t map[D][D]){
  int l, c;
  FILE * fic = fopen("../sauv/save_map.csv","w");

  // type
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].type);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");
  //categ
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].categ);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");
  //encounter
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].encounter);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");
  //quest_id
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].quest_id);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");
  //scavenged
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic, "%2d;", map[l][c].scavenged);
    }
    fprintf(fic,"\n");
  }

  fclose(fic);
}

/******************************************************/

/******************** LOAD ****************************/
/**
 * \fn int load (perso_t * player, cell_t map[D][D])
 * \brief Charge les informations sur le joueur, son inventaire, son équipement et la carte
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Un \a int : 1 si succès complet du chargement. 0 si problème lors du chargement.
*/
/* load: load information about the character, his inventory, his equipment and the map. */
int load (perso_t * player, cell_t map[D][D]){
  if(!load_inventory (player)){
    printf("Echec chargement inventaire\n");
    return 0;
  }
  if(!load_info_player (player)){
    printf("Echec chargement des données du joueur\n");
    return 0;
  }
  if(!load_map(map)){
    printf("Echec chargement de la carte\n");
    return 0;
  }
  if(!load_equipment (player)){
    printf("Echec chargement équipement\n");
    return 0;
  }

  return 1;
}

/**
 * \fn int load_inventory (perso_t * player)
 * \brief Charge l'inventaire du joueur à partir du fichier 'save_inventory.csv'
 * \param perso_t * player
 * \return Un \a int : 1 si chargement réussi. 0 si échec du chargement.
*/
/* load_inventory: loads the player's inventory */
int load_inventory (perso_t * player){
  FILE * fic = fopen("../sauv/save_inventory.csv","r");
  player->nb_items_inventory = 0;
  if(fic){
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack[0], &player->inventory[player->nb_items_inventory].attack[1],&player->inventory[player->nb_items_inventory].attack[2], &player->inventory[player->nb_items_inventory].hitchance[0], &player->inventory[player->nb_items_inventory].hitchance[1],&player->inventory[player->nb_items_inventory].hitchance[2],&player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military, player->inventory[player->nb_items_inventory].name);
    while(!feof(fic)){
      player->inventory[player->nb_items_inventory].index = player->nb_items_inventory;
      (player->nb_items_inventory)++;
      fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack[0], &player->inventory[player->nb_items_inventory].attack[1],&player->inventory[player->nb_items_inventory].attack[2], &player->inventory[player->nb_items_inventory].hitchance[0], &player->inventory[player->nb_items_inventory].hitchance[1],&player->inventory[player->nb_items_inventory].hitchance[2],&player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military, player->inventory[player->nb_items_inventory].name);
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Erreur : 'save_inventory.csv' introuvable\n");
    return 0;
  }
}

/**
 * \fn int load_info_player (perso_t * player)
 * \brief Charge les informations du joueur à partir du fichier 'save_info_player.csv'
 * \param perso_t * player
 * \return Un \a int : 1 si chargement réussi. 0 si échec du chargement.
*/
/* load_info_player: loads player information */
int load_info_player (perso_t * player){
  FILE * fic = fopen("../sauv/save_info_player.csv","r");
  if(fic){
    // Version avec compétence spéciale (pas en version1)
    // fscanf(fic,"pv = %d\npe = %d\npa = %d\nposX = %d\nposY = %d\ncompetence = %d\nturns = %d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->competence, &player->turns);
    fscanf(fic,"pv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->turns);
    fclose(fic);
    return 1;
  }
  else {
    printf("Erreur : 'save_info_player.csv' introuvable\n");
    return 0;
  }
}

/**
 * \fn int load_equipment (perso_t * player)
 * \brief Charge l'équipement du joueur à partir du fichier 'save_equipment.csv'
 * \param perso_t * player
 * \return Un \a int : 1 si chargement réussi. 0 si échec du chargement.
*/
/* load_equipment: loads the player's equipment */
int load_equipment (perso_t * player){
  FILE * fic = fopen("../sauv/save_equipment.csv","r");
  int ind_head = 0, ind_lh = 0, ind_rh = 0, ind_body = 0;

  if(fic){
    fscanf(fic,"head;%d\nleft hand;%d\nright hand;%d\nbody;%d\n", &ind_head, &ind_lh, &ind_rh, &ind_body);
    (ind_head != -1) ? (player->head = &player->inventory[ind_head]) : (player->head = NULL);
    (ind_lh != -1) ? (player->left_hand = &player->inventory[ind_lh]) : (player->left_hand = NULL);
    (ind_rh != -1) ? (player->right_hand = &player->inventory[ind_rh]) : (player->right_hand = NULL);
    (ind_body != -1) ? (player->body = &player->inventory[ind_body]) : (player->body = NULL);

    fclose(fic);
    return 1;
  }
  else {
    printf("Erreur : 'save_equipment.csv' introuvable\n");
    return 0;
  }
}

/**
 * \fn int load_map (cell_t map[D][D])
 * \brief Charge la carte à partir du fichier 'save_map.csv'
 * \param cell_t map[D][D]
 * \return Un \a int : 1 si chargement réussi. 0 si échec du chargement.
*/
/* load_map: loads the map of the game */
int load_map (cell_t map[D][D]){
  int l, c;
  FILE * fic = fopen("../sauv/save_map.csv","r");

  if(fic){
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].type);
      }
    }
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].categ);
      }
    }
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].encounter);
      }
    }
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].quest_id);
      }
    }
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].scavenged);
      }
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Erreur : 'save_map.csv' introuvable\n");
    return 0;
  }
}

/*****************************************************/
/**
 * \fn int backup_exists ()
 * \brief Vérifie si une sauvegarde complète du jeu existe
 * \return Un \a int : 1 si sauvegarde existante. 0 sinon.
*/
/* backup_exists: returns 1 if a backup exists and 0 if there is none */
int backup_exists (){
  FILE * fic1, * fic2, * fic3, * fic4;
  fic1 = fopen("../sauv/save_inventory.csv","r");
  fic2 = fopen("../sauv/save_equipment.csv","r");
  fic3 = fopen("../sauv/save_info_player.csv","r");
  fic4 = fopen("../sauv/save_map.csv","r");

  if(fic1){
    fclose(fic1);
    if(fic2){
      fclose(fic2);
      if(fic3){
        fclose(fic3);
        if(fic4){
          fclose(fic4);
          return 1;
        }
      }
    }
  }
  return 0;
}

/* init_or_load_game:
   If a backup of the game exists, offers the player to continue the game or start a new one.
   Loads the game if saved, otherwise uses functions to initialize the player and the map.
*/
/**
 * \fn int init_or_load_game(perso_t * player, cell_t map[D][D])
 * \brief Si une sauvegarde du jeu existe, propose au joueur de continuer la partie ou d'en commencer une nouvelle.
    Si aucune sauvegarde, initialise une nouvelle partie.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Un \a int : 1 si initialisation / chargement réussi. 0 si échec.
*/
int init_or_load_game(perso_t * player, cell_t map[D][D]){
  int num;

  if(backup_exists()){
    printf("1. Continuer la partie (sauvegarde)\n");
    printf("2. Nouvelle partie\n");
    printf("Quitter: -1\n\n");

    do {
      printf("N°");
      scanf("%d",&num);
      if((num != -1) && (num < 1 || num > 2)){
        printf("Valeur incorrecte. Veuillez ressaisir\n");
      }
    } while ((num != -1) && (num < 1 || num >2));

    if(num != -1){
      switch (num){
        case 1: return load(player, map); break;
        case 2: init_player(player);
                map_init(map);
                return 1;
                break;
        default: break;
      }
    }
  }
  else {
      init_player(player);
      map_init(map);
      return 1;
  }
  return 0;
}
