//backup_and_load.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/******************** BACK_UP *************************/

void save (perso_t player, int map[D][D]){
  save_inventory(player);
  save_info_player(player);
  save_equipment(player);
  save_map(map);
}

void save_inventory (perso_t player){
  int i;

  FILE * fic = fopen("txt/save_inventory.txt","w");
  for(i = 0; i < player.nb_items_inventory; i++){
    fprintf(fic,"%s %d\n%d %d %d\n%d %d %d\n\n",player.inventory[i].name, player.inventory[i].type, player.inventory[i].attack, player.inventory[i].defense, player.inventory[i].equipable, player.inventory[i].pc_nature, player.inventory[i].pc_urban, player.inventory[i].pc_military);
  }
  printf("save_inventory.txt - Successfully backed up!\n");
  fclose(fic);
}

void save_info_player (perso_t player){
  FILE * fic = fopen("txt/save_info_player.txt","w");
  fprintf(fic,"pv = %d\npe = %d\npa = %d\n", player.pv, player.pe, player.pa);
  fprintf(fic,"posX = %d\nposY = %d\n", player.posX, player.posY);
  fprintf(fic,"competence = %d\n", player.competence);
  fprintf(fic,"turns = %d\n", player.turns);

  printf("save_info_player.txt - Successfully backed up!\n");
  fclose(fic);
}

void save_equipment (perso_t player){
  FILE * fic = fopen("txt/save_equipment.txt","w");

  (player.head != NULL) ? fprintf(fic, "head = %d\n", indice(player,*player.head)) : fprintf(fic, "head = -1\n");
  (player.left_hand != NULL) ? fprintf(fic, "left_hand = %d\n", indice(player,*player.left_hand)) : fprintf(fic, "left hand = -1\n");
  (player.right_hand != NULL) ? fprintf(fic, "right_hand = %d\n", indice(player,*player.right_hand)) : fprintf(fic, "right hand = -1\n");
  (player.body != NULL) ? fprintf(fic, "body = %d\n", indice(player,*player.body)) : fprintf(fic, "body = -1\n");

  printf("save_equipment.txt - Successfully backed up!\n");
  fclose(fic);
}

void save_map (int map[D][D]){
  int l, c;
  FILE * fic = fopen("txt/save_map.txt","w");

  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic, "%2d ", map[l][c]);
    }
      fprintf(fic, "\n");
  }

  printf("save_map.txt - Successfully backed up!\n");
  fclose(fic);
}

/******************************************************/

/******************** LOAD ****************************/

int load (perso_t * player, int map[D][D]){
  if(!load_inventory (player)){
    printf("Echec chargement inventaire\n");
    return 0;
  }
  if(!load_info_player (player)){
    printf("Echec chargement info joueur\n");
    return 0;
  }
  if(!load_equipment (player)){
    printf("Echec chargement equipement\n");
    return 0;
  }
  if(!load_map(map)){
    printf("Echec chargment carte\n");
    return 0;
  }
  return 1;
}

int load_inventory (perso_t * player){
  FILE * fic = fopen("txt/save_inventory.txt","r");
  player->nb_items_inventory = 0;
  if(fic){
    fscanf(fic,"%s%d%d%d%d%d%d%d",player->inventory[player->nb_items_inventory].name, &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack, &player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military);
    while(!feof(fic)){
      (player->nb_items_inventory)++;
      fscanf(fic,"%s%d%d%d%d%d%d%d",player->inventory[player->nb_items_inventory].name, &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack, &player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military);
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_inventory.txt' not found...\n");
    return 0;
  }
}

int load_info_player (perso_t * player){
  FILE * fic = fopen("txt/save_info_player.txt","r");
  if(fic){
    fscanf(fic,"pv = %d\npe = %d\npa = %d\nposX = %d\nposY = %d\ncompetence = %d\nturns = %d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->competence, &player->turns);
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_info_player.txt' not found...\n");
    return 0;
  }
}

int load_equipment (perso_t * player){
  FILE * fic = fopen("txt/save_equipment.txt","r");
  int ind_head, ind_lh, ind_rh, ind_body;

  if(fic){
    fscanf(fic,"head = %d\nleft_hand = %d\nright_hand = %d\nbody = %d\n", &ind_head, &ind_lh, &ind_rh, &ind_body);

    (ind_head != -1) ? (player->head = &player->inventory[ind_head]) : (player->head = NULL);
    (ind_lh != -1) ? (player->left_hand = &player->inventory[ind_lh]) : (player->left_hand = NULL);
    (ind_rh != -1) ? (player->right_hand = &player->inventory[ind_rh]) : (player->right_hand = NULL);
    (ind_body != -1) ? (player->body = &player->inventory[ind_body]) : (player->body = NULL);

    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_equipment.txt' not found...\n");
    return 0;
  }
}

int load_map (int map[D][D]){
  int l, c;
  FILE * fic = fopen("txt/save_map.txt","r");

  if(fic){
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d",&map[l][c]);
      }
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_map.txt' not found...\n");
    return 0;
  }
}

/*****************************************************/
