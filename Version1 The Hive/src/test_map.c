#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

void display_hex(cell_t map[D][D], int l, int c){
  switch(map[l][c].type){
    case prairie   : printf("prairie "); break;
    case foret     : printf("forêt ");    break;
    case ville     : printf("ville ");    break;
    case lac       : printf("lac ");     break;
    case camp_mil  : printf("camp militaire ");  break;
    case camp_ban  : printf("camp des bandits ");     break;
    case market    : printf("marché ");   break;
    case favella   : printf("favella ");   break;
    case montagne  : printf("montagne ");     break;
    case frontiere : printf("frontière ");      break;
    case mer       : printf("mer ");   break;
    case wasteland : printf("wasteland ");    break;
  }
  switch(map[l][c].categ){
    case other   : printf("[AUTRE]\n"); break;
    case nature  : printf("[NATURE]\n"); break;
    case urbain  : printf("[URBAIN]\n"); break;
    case militaire : printf("[MILITAIRE]\n");  break;
  }
}

int main(){
  srand(time(NULL));
  cell_t map[D][D];
  int quest_map[6][2];
  perso_t player;
  init_player(&player);
  int l, c;
  map_init(map,quest_map,player);

  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if((map[l][c].type == prairie) && (map[l][c].categ != nature)){
        printf("Problème prairie >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == foret) && (map[l][c].categ != nature)){
        printf("Problème foret >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == ville) && (map[l][c].categ != urbain)){
        printf("Problème ville >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == lac) && (map[l][c].categ != nature)){
        printf("Problème lac >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == camp_mil) && (map[l][c].categ != militaire)){
        printf("Problème camp_mil >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == camp_ban) && (map[l][c].categ != other)){
        printf("Problème camp_ban >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == market) && (map[l][c].categ != urbain)){
        printf("Problème market >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == favella) && (map[l][c].categ != urbain)){
        printf("Problème favella >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == montagne) && (map[l][c].categ != nature)){
        printf("Problème montagne >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == frontiere) && (map[l][c].categ != other)){
        printf("Problème frontiere >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == mer) && (map[l][c].categ != nature)){
        printf("Problème mer >>> ");
        display_hex(map,l,c);
      }
      if((map[l][c].type == wasteland) && (map[l][c].categ != other)){
        printf("Problème wasteland >>> ");
        display_hex(map,l,c);
      }
      /* Ajout de ce if car le problème semble ne concerner que les villes */
      if((map[l][c].type == ville) && (map[l][c].categ == urbain)){
        display_hex(map,l,c);
      }
    }
  }
}
