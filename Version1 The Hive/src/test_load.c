#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

void load_test (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete){
  int l, c, ind_rh, ind_lh, ind_head, ind_body, i = 0;
  FILE * fic = fopen("../sauv/sauv_test.csv","r");
  char nomPartie[20];

  if(fic){

    fscanf(fic," %[^\n]\n\n\n",nomPartie);
    printf("\n\t>>> Chargement Partie %s\n",nomPartie); sleep(2);

    /*
     * Chargement informations joueur
     */

    fscanf(fic,"pv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->turns);

    /*
     * Chargement inventaire
     */

    fscanf(fic,"%d\n",&player->nb_items_inventory);
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[i].type, &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense, &player->inventory[i].equipable, &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
    while(i < player->nb_items_inventory){
      player->inventory[i].index = i;
      i++;
      fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[i].type, &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense, &player->inventory[i].equipable, &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
    }

    /*
     * Chargement équipement
     */

    fscanf(fic,"head;%d\nleft hand;%d\nright hand;%d\nbody;%d\n", &ind_head, &ind_lh, &ind_rh, &ind_body);
    (ind_head != -1) ? (player->head = &player->inventory[ind_head]) : (player->head = NULL);
    (ind_lh != -1) ? (player->left_hand = &player->inventory[ind_lh]) : (player->left_hand = NULL);
    (ind_rh != -1) ? (player->right_hand = &player->inventory[ind_rh]) : (player->right_hand = NULL);
    (ind_body != -1) ? (player->body = &player->inventory[ind_body]) : (player->body = NULL);

    /*
     * Chargement map
     */

    // type
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].type);
      }
    }

    // categ
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].categ);
      }
    }

    // encounter
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].encounter);
      }
    }

    // quest_id
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].quest_id);
      }
    }

    // scavenged
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].scavenged);
      }
    }

    /*
     * Chargement quêtes
     */

    // Chargement int quest_map[6][2]
    for(l = 0; l < 6; l++){
      for(c = 0; c < 2; c++){
        fscanf(fic,"%d;",&quest_map[l][c]);
      }
    }

    // Chargement quete_t quete
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%d",&quete->soin,&quete->recherche.situation,&quete->recherche.butX,&quete->recherche.butY,&quete->bunker,&quete->montagne,&quete->frontiere,&quete->bandits);

    fclose(fic);
  }
  else {
    printf("Erreur lors du chargement des données sauvegardées.\n");
  }
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
  printf("   recherche : %d %d %d\n", quete.recherche.situation, quete.recherche.butX, quete.recherche.butY);
  printf("   bunker : %d\n", quete.bunker);
  printf("   montagne : %d\n", quete.montagne);
  printf("   frontiere : %d\n", quete.frontiere);
  printf("   bandits : %d\n\n", quete.bandits);
}

int main(){
  int nb;
  item_t Tab_Items[20];
  int nb_items_available = 0;
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;
  perso_t player;

  if(creation_tab_item(Tab_Items, &nb_items_available)) {
    load_test(&player,map,quest_map,&quete);
      do {
        menu:
        clrscr();
        printf ("\033[34;01m\n\n\n\tMenu test_load.c\033[00m\n");
        printf("\t1. Afficher les caractéristiques du joueur\n");
        printf("\t2. Afficher l'inventaire\n");
        printf("\t3. Afficher l'équipement\n");
        printf("\t4. Afficher la carte\n");
        printf("\t5. Détails carte\n");
        printf("\t6. Détails quêtes\n");
        printf("\n\tQuitter -1\n\n");
        printf("\tN°");
        scanf("%d",&nb);

        if(nb != -1){
          switch(nb){
            case 1: clrscr(); display_player_characteristics(map, player); entree_pour_continuer(); break;
            case 2: clrscr(); display_inventory(player); entree_pour_continuer(); break;
            case 3: clrscr(); display_equipment_player(player); entree_pour_continuer(); break;
            case 4: clrscr(); display_TEXT(player.posX,player.posY,map);
                    count(map);
                    printf("\n");
                    break;
            case 5: clrscr(); details_map(map); entree_pour_continuer(); break;
            case 6: clrscr(); info_quetes(quest_map,quete); entree_pour_continuer(); break;
            default: printf("\tCommand not found\n"); sleep(1); goto menu; break;
          }
        }
      } while (nb != -1);

  }

  clrscr();
  return EXIT_SUCCESS;
}
