#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));
  clrscr();

  int choix;
  perso_t player;
  quete_t quete;
  cell_t map[D][D];
  int quest_map[6][2];
  int sortie = 0;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  creation_tab_item(Tab_Items,&nb_items_available);

  item_t * fruits = creer_item("fruits",food,0,0,0,0,0,0,0,0,60,10,50);
  item_t * fish = creer_item("fish",food,0,0,0,0,0,0,0,0,0,0,0);
  item_t * canned_food = creer_item("canned food",food,0,0,0,0,0,0,0,0,0,60,75);
  item_t * medical_kit = creer_item("medical kit",misc,0,0,0,0,0,0,0,0,0,60,80);
  item_t * rope = creer_item("rope",misc,0,0,0,0,0,0,0,0,0,40,50);
  item_t * map_item = creer_item("map",misc,0,0,0,0,0,0,0,0,0,20,70);
  item_t * pistol = creer_item("pistol",weapon,5,25,15,30,85,60,0,1,0,20,60);
  item_t * shotgun = creer_item("shotgun",weapon,10,40,30,40,85,60,0,1,0,15,50);
  item_t * bulletproof_vest = creer_item("bulletproof vest",armor,0,0,0,0,0,0,0.7,2,0,10,70);
  item_t * helmet = creer_item("helmet",armor,0,0,0,0,0,0,0.6,3,0,0,0);

  init_player(&player);
  map_init(map,quest_map,player);
  init_quete(&quete,quest_map,Tab_Items,nb_items_available);

  printf ("\033[34;01m\n   Menu test quête soin\033[00m\n");
  printf("   1. Inventaire vide \n");
  printf("   2. Inventaire : inclus 1 item food \n");
  printf("   3. Inventaire : inclus 3 items food dans l'inventaire\n");
  printf("   4. Inventaire : inclus 1 medical kit\n");
  printf("   5. Inventaire : inclus 1 medical kit + 1 item food\n");
  printf("   6. Inventaire plein (inclus 1 medical kit + items food)\n");
  printf("\n   Votre réponse : ");
  do {
    scanf("%d",&choix);
    if(choix < 1 || choix > 6){
       printf("   Veuillez ressaisir : ");
    }
  } while(choix < 1 || choix > 6);

  if(choix == 2){
    add_item_to_inventory(&player,*fruits);
    add_item_to_inventory(&player,*map_item);
    add_item_to_inventory(&player,*pistol);
    add_item_to_inventory(&player,*helmet);
  }
  else if(choix == 3){
    add_item_to_inventory(&player,*fruits);
    add_item_to_inventory(&player,*canned_food);
    add_item_to_inventory(&player,*map_item);
    add_item_to_inventory(&player,*pistol);
    add_item_to_inventory(&player,*helmet);
    add_item_to_inventory(&player,*fish);
  }
  else if (choix == 4){
    add_item_to_inventory(&player,*map_item);
    add_item_to_inventory(&player,*medical_kit);
    add_item_to_inventory(&player,*pistol);
    add_item_to_inventory(&player,*helmet);
  }
  else if(choix == 5){
    add_item_to_inventory(&player,*fruits);
    add_item_to_inventory(&player,*shotgun);
    add_item_to_inventory(&player,*canned_food);
    add_item_to_inventory(&player,*bulletproof_vest);
    add_item_to_inventory(&player,*rope);
    add_item_to_inventory(&player,*medical_kit);
  }
  else if (choix == 6){
    add_item_to_inventory(&player,*fruits);
    add_item_to_inventory(&player,*medical_kit);
    add_item_to_inventory(&player,*fish);
    add_item_to_inventory(&player,*rope);
    add_item_to_inventory(&player,*map_item);
    add_item_to_inventory(&player,*pistol);
    add_item_to_inventory(&player,*shotgun);
    add_item_to_inventory(&player,*canned_food);
    add_item_to_inventory(&player,*bulletproof_vest);
    add_item_to_inventory(&player,*helmet);
  }

  clrscr();
  if(creation_tab_item(Tab_Items, &nb_items_available)){
    sortie = quete_soin(&player,&quete,Tab_Items);
    switch(sortie){
      case 0: printf("\n   Le jeu continue!\n"); break;
      case 1: printf("\n   Fin du jeu\n"); break;
      case -1: printf("\n   Pb dans la quête\n"); break;
      default: break;
    }
  }
  else {
    printf("   Problème lors de la récupération des items.\n");
  }

  free(fruits);
  free(fish);
  free(canned_food);
  free(medical_kit);
  free(rope);
  free(map_item);
  free(pistol);
  free(shotgun);
  free(bulletproof_vest);
  free(helmet);
  free(Tab_Items); 
}
