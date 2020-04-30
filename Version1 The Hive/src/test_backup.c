#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

void info_quetes(int quest_map[6][2], quete_t quete){
  int l,c;

  clrscr();

  printf("\nAFFICHAGE MATRICE QUEST_MAP : \n");
  for(l = 0; l < 6; l++){
    for(c = 0; c < 2; c++){
      printf("%2d ",quest_map[l][c]);
    }
      printf("\n");
  }

  printf("\nAFFICHAGE STRUCTURE QUETE : \n");
  printf("soin : %d\n", quete.soin);
  printf("recherche : %d %d %d\n", quete.recherche.situation, quete.recherche.butX, quete.recherche.butY);
  printf("bunker : %d\n", quete.bunker);
  printf("montagne : %d\n", quete.montagne);
  printf("frontiere : %d\n", quete.frontiere);
  printf("bandits : %d\n\n", quete.bandits);
}

int main(){
  int nb;
  srand(time(NULL));

  /* Tab_Items Declaration (= table containing ALL the items available in the game) */
  item_t Tab_Items[20];
  int nb_items_available = 0;

  /* Map Declaration */
  cell_t map[D][D];

  int quest_map[6][2];
  quete_t quete;
  init_quete(&quete);

  if(creation_tab_item(Tab_Items, &nb_items_available)) {

    perso_t player;
    player.left_hand = NULL;
    player.right_hand = NULL;
    player.body = NULL;
    player.head = NULL;

    printf ("\033[34;01m[CREATION JOUEUR]\033[00m\n");
    player.nb_items_inventory = 0; /* The player starts the game with an empty inventory. */
    printf("posX ? ");
    scanf("%d", &player.posX);
    printf("posY ? ");
    scanf("%d", &player.posY);
    printf("pv ? ");
    scanf("%d", &player.pv);
    printf("pe ? ");
    scanf("%d", &player.pe);
    printf("pa ? ");
    scanf("%d", &player.pa);
    printf("turns ? ");
    scanf("%d", &player.turns);

/* Pas de compétence spéciale en version 1 */
/*
    do {
      printf("Which skill do you want for your character? (normal = 0, sprinter = 1, metabolism = 2, luck = 3, scout = 4)\n");
      scanf("%d",&comp);
      if(comp < 0 || comp > 4){
        printf("Incorrect value (value must be between 0 and 4)\n");
      }
    } while(comp < 0 || comp > 4);
    player.competence = comp;
*/
    printf("\n");

    printf ("\033[34;01m[ITEMS AJOUTES A L'INVENTAIRE]\033[00m\n");
    add_item_to_inventory(&player, Tab_Items[0]);  //pistol
    add_item_to_inventory(&player, Tab_Items[2]);  //shotgun
    add_item_to_inventory(&player, Tab_Items[4]);  //bow_arrows
    add_item_to_inventory(&player, Tab_Items[6]);  //bulletproof_vest
    add_item_to_inventory(&player, Tab_Items[7]);  //helmet
    add_item_to_inventory(&player, Tab_Items[8]);  //fishing_rod
    add_item_to_inventory(&player, Tab_Items[10]); //rope
    add_item_to_inventory(&player, Tab_Items[12]); //map
    add_item_to_inventory(&player, Tab_Items[14]); //fish
    add_item_to_inventory(&player, Tab_Items[17]); //bottle_water
    printf("\n");

    /* Equipment */
    player.head = &player.inventory[4];       //helmet
    player.right_hand = &player.inventory[0]; //pistol
    player.left_hand = &player.inventory[1];  // shotgun

    /* Map generation */
    map_init(map,quest_map);

    printf("\n");
    printf ("\033[34;01m[SAUVEGARDE]\033[00m\n");
    save(player,map,quest_map,quete);

    /* TESTS UNITAIRES */
    /*
    save_inventory(player);
    save_info_player(player);
    save_equipment(player);
    save_map (map);
    */

    printf("\n");

    do {
      printf("Menu test_back_up :\n");
      printf("1. Afficher les caractéristiques du joueur\n");
      printf("2. Affiche l'inventaire\n");
      printf("3. Afficher l'équipement\n");
      printf("4. Afficher la carte\n");
      printf("5. Afficher les infos sur les quêtes\n");
      printf("Quitter -1\n");
      do {
        printf("N°");
        scanf("%d",&nb);
        if((nb != -1) && (nb < 1 || nb > 5)){
          printf("Valeur incorrecte. Veuillez resaissir\n");
        }
      } while ((nb != -1) && (nb < 1 || nb > 5));

      if(nb != -1){
        switch(nb){
          case 1: display_player_characteristics(map, player); break;
          case 2: display_inventory(player); break;
          case 3: display_equipment_player(player); break;
          case 4: display_TEXT(player.posX,player.posY,map);
                  count(map);
                  printf("\n");
                  break;
          case 5: info_quetes(quest_map, quete); break;
          default: break;
        }
      }
    } while (nb != -1);


    /* Free memory */
    player.left_hand = NULL;
    player.right_hand = NULL;
    player.body = NULL;
    player.head = NULL;

    free(player.left_hand);
    free(player.right_hand);
    free(player.body);
    free(player.head);
  }

  return EXIT_SUCCESS;
}
