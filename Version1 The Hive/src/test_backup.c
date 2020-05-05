#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

void save_test (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete){
  int l, c, i;
  FILE * fic = fopen("../sauv/sauv_test.csv","w");
  fprintf(fic,"%s\n\n\n","Test Sauvegarde");

  /*
   * Sauvegarde informations joueur
   */

   fprintf(fic,"\n\npv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n\n", player.pv, player.pe, player.pa, player.posX, player.posY, player.turns);

  /*
   * Sauvegarde inventaire
   */

  fprintf(fic,"%d\n",player.nb_items_inventory);
  for(i = 0; i < player.nb_items_inventory; i++){
    fprintf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%s\n",player.inventory[i].type, player.inventory[i].attack[0], player.inventory[i].attack[1],player.inventory[i].attack[2], player.inventory[i].hitchance[0], player.inventory[i].hitchance[1],player.inventory[i].hitchance[2],player.inventory[i].defense, player.inventory[i].equipable, player.inventory[i].pc_nature, player.inventory[i].pc_urban, player.inventory[i].pc_military, player.inventory[i].name);
  }

  /*
   * Sauvegarde équipement
   */

  (player.head != NULL) ? fprintf(fic, "\nhead;%d\n", player.head->index) : fprintf(fic, "\nhead;-1\n");
  (player.left_hand != NULL) ? fprintf(fic, "left hand;%d\n", player.left_hand->index) : fprintf(fic, "left hand;-1\n");
  (player.right_hand != NULL) ? fprintf(fic, "right hand;%d\n", player.right_hand->index) : fprintf(fic, "right hand;-1\n");
  (player.body != NULL) ? fprintf(fic, "body;%d\n\n", player.body->index) : fprintf(fic, "body;-1\n\n");

  /*
   * Sauvegarde carte
   */

  // type
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].type);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // categ
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].categ);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // encounter
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].encounter);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // quest_id
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].quest_id);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // scavenged
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic, "%2d;", map[l][c].scavenged);
    }
    fprintf(fic,"\n");
  }

  fprintf(fic,"\n");

  /*
   * Sauvegarde quêtes
   */

   // Sauvegarde int quest_map[6][2]
   for(l = 0; l < 6; l++){
    for(c = 0; c < 2; c++){
      fprintf(fic,"%d;",quest_map[l][c]);
    }
    fprintf(fic,"\n");
  }

  // Sauvegarde quete_t quete
  fprintf(fic,"\n%d;%d;%d;%d;%d;%d;%d;%d;%d\n",quete.soin,quete.recherche.situation,quete.recherche.trouve,quete.recherche.bunkerX,quete.recherche.bunkerY,quete.bunker,quete.montagne,quete.frontiere,quete.bandits);
  fprintf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%s\n",quete.recherche.wanted.type, quete.recherche.wanted.attack[0], quete.recherche.wanted.attack[1],quete.recherche.wanted.attack[2], quete.recherche.wanted.hitchance[0], quete.recherche.wanted.hitchance[1],quete.recherche.wanted.hitchance[2],quete.recherche.wanted.defense, quete.recherche.wanted.equipable, quete.recherche.wanted.pc_nature, quete.recherche.wanted.pc_urban, quete.recherche.wanted.pc_military, quete.recherche.wanted.name);

  fclose(fic);
}


void details_map(cell_t map[D][D]){
  int l, c;

  printf("\033[34;01m   Type\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].type);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01mCateg\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].categ);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Encounter\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].encounter);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Quest ID\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].quest_id);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Scavenged\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].scavenged);
    }
    printf("\n");
  }
  printf("\n\n");
}

void info_quetes(int quest_map[6][2], quete_t quete){
  int l, c;

  printf ("\033[34;01m\n\n\n   [Affichage matrice quest_map]\033[00m\n\n");

  for(l = 0; l < 6; l++){
    for(c = 0; c < 2; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ",quest_map[l][c]);
    }
      printf("\n");
  }

  printf ("\033[34;01m\n   [Affichage quete_t quete]\033[00m\n\n");
  printf("   soin : %d\n", quete.soin);
  printf("   recherche :\n      situation : %d\n      trouve : %d\n      bunkerX : %d\n      bunkerY : %d\n", quete.recherche.situation, quete.recherche.trouve, quete.recherche.bunkerX, quete.recherche.bunkerY);
  display_item(quete.recherche.wanted);
  printf("\n   bunker : %d\n", quete.bunker);
  printf("   montagne : %d\n", quete.montagne);
  printf("   frontiere : %d\n", quete.frontiere);
  printf("   bandits : %d\n\n", quete.bandits);
}

int main(){
  srand(time(NULL));

  int nb;
  perso_t player;
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  creation_tab_item(Tab_Items, &nb_items_available);

  init_player(&player);
  map_init(map,quest_map,player);
  init_quete(&quete,quest_map,Tab_Items,nb_items_available);

  player.nb_items_inventory = 0; /* Le joueur commence le jeu avec un inventaire vide. */
  player.pv = rand()%101;
  player.pe = rand()%101;
  player.pa = rand()%6;
  player.turns = rand()%16;

/* Pas de compétence spéciale en version 1
    do {
      printf("Which skill do you want for your character? (normal = 0, sprinter = 1, metabolism = 2, luck = 3, scout = 4)\n");
      scanf("%d",&comp);
      if(comp < 0 || comp > 4){
        printf("Incorrect value (value must be between 0 and 4)\n");
      }
    } while(comp < 0 || comp > 4);
    player.competence = comp;
*/

  item_t * pistol = creer_item("pistol",weapon,5,25,15,30,85,60,0,1,0,20,60);
  item_t * shotgun = creer_item("shotgun",weapon,10,40,30,40,85,60,0,1,0,15,50);
  item_t * bow_and_arrows = creer_item("bow and arrows",weapon,0,0,0,0,0,0,0,1,30,0,0);
  item_t * bulletproof_vest = creer_item("bulletproof vest",armor,0,0,0,0,0,0,0.7,2,0,10,70);
  item_t * helmet = creer_item("helmet",armor,0,0,0,0,0,0,0.6,3,0,0,0);
  item_t * fishing_rod = creer_item("fishing rod",misc,0,0,0,0,0,0,0,0,0,40,0);
  item_t * rope = creer_item("rope",misc,0,0,0,0,0,0,0,0,0,40,50);
  item_t * map_item = creer_item("map",misc,0,0,0,0,0,0,0,0,0,20,70);
  item_t * fish = creer_item("fish",food,0,0,0,0,0,0,0,0,0,0,0);
  item_t * bottle_water = creer_item("bottle water",food,0,0,0,0,0,0,0,0,0,50,50);

  add_item_to_inventory(&player,*pistol);
  add_item_to_inventory(&player,*shotgun);
  add_item_to_inventory(&player,*bow_and_arrows);
  add_item_to_inventory(&player,*bulletproof_vest);
  add_item_to_inventory(&player,*helmet);
  add_item_to_inventory(&player,*fishing_rod);
  add_item_to_inventory(&player,*rope);
  add_item_to_inventory(&player,*map_item);
  add_item_to_inventory(&player,*fish);
  add_item_to_inventory(&player,*bottle_water);

  player.head = &player.inventory[4];       //helmet
  player.right_hand = &player.inventory[0]; //pistol
  player.left_hand = &player.inventory[1];  // shotgun

  save_test(player,map,quest_map,quete);

  do {
    menu:
    clrscr();
    printf ("\033[34;01m\n\n\n   Menu test_backup.c\033[00m\n");
    printf("   1. Afficher les caractéristiques du joueur\n");
    printf("   2. Affiche l'inventaire\n");
    printf("   3. Afficher l'équipement\n");
    printf("   4. Afficher la carte\n");
    printf("   5. Afficher détails map\n");
    printf("   6. Afficher les infos sur les quêtes\n");
    printf("\n   Quitter -1\n\n");
    printf("   N°");
    scanf("%d",&nb);
    if(nb != -1){
      switch(nb){
        case 1: clrscr(); display_player_characteristics(map, player); entree_pour_continuer(); break;
        case 2: clrscr(); display_inventory(player); entree_pour_continuer(); break;
        case 3: clrscr(); display_equipment_player(player); entree_pour_continuer(); break;
        case 4: clrscr();
                display_TEXT(player.posY,player.posX,map);
                count(map);
                printf("\n");
                break;
        case 5: clrscr(); details_map(map); entree_pour_continuer(); break;
        case 6: clrscr(); info_quetes(quest_map, quete); entree_pour_continuer(); break;
        default: printf("   Command not found\n"); sleep(1); goto menu; break;
      }
    }
  } while (nb != -1);

  free(pistol);
  free(shotgun);
  free(bow_and_arrows);
  free(bulletproof_vest);
  free(helmet);
  free(fishing_rod);
  free(rope);
  free(map_item);
  free(fish);
  free(bottle_water);
  free(Tab_Items);
  clrscr();

  return EXIT_SUCCESS;
}
