#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/commun.h"

/**
 * \file test_load.c
 * \brief Fichier TEST - Charger une partie
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void load_test (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete)
 * \brief Charge les informations sur le joueur, son inventaire, son équipement ainsi que les informations sur la carte et les quêtes d'une partie test.
 * \details Informations sur le joueur : points de vie, points d'énergie, points d'action, position sur la carte, nombre de tours restants
 * \details Informations sur la carte : pour chaque case de la matrice map, on récupère son type, sa catégorie, s'il y a un combat, si le joueur a déjà fouillé la case et si une quête y est positionnée.
 * \details Informations sur les quêtes : on récupère les coordonnées de chaque quête ainsi que leurs états.
 * \details Fonction TEST
 * \param player Pointeur sur un objet de type perso_t correspondant au joueur
 * \param map[D][D] Matrice de la carte
 * \param quest_map[6][2] Matrice des coordonnées des quêtes
 * \param quete Pointeur sur un objet de type quete_t correspondant à l'état des quêtes
 * \return Rien
*/
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
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", (int *)(&player->inventory[i].type), &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense, (int *)(&player->inventory[i].equipable), &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
    while(i < player->nb_items_inventory){
      player->inventory[i].index = i;
      i++;
      fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]",(int *)(&player->inventory[i].type), &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense,(int *)(&player->inventory[i].equipable), &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
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
        fscanf(fic,"%d;",(int *)(&map[l][c].type));
      }
    }

    // categ
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",(int *)(&map[l][c].categ));
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
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%d;%d",&quete->soin,&quete->recherche.situation,&quete->recherche.trouve,&quete->recherche.bunkerX,&quete->recherche.bunkerY,&quete->bunker,&quete->montagne,&quete->frontiere,&quete->bandits);
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]",(int *)(&quete->recherche.wanted.type),&quete->recherche.wanted.attack[0],&quete->recherche.wanted.attack[1],&quete->recherche.wanted.attack[2],&quete->recherche.wanted.hitchance[0],&quete->recherche.wanted.hitchance[1],&quete->recherche.wanted.hitchance[2],&quete->recherche.wanted.defense,(int *)(&quete->recherche.wanted.equipable),&quete->recherche.wanted.pc_nature,&quete->recherche.wanted.pc_urban,&quete->recherche.wanted.pc_military,quete->recherche.wanted.name);

    fclose(fic);
  }
  else {
    printf("   Erreur lors du chargement des données sauvegardées.\n");
  }
}

/**
 * \void int main()
 * \brief Programme principal pour tester le système de chargement
 * \details Charge la sauvegarde d'une partie test
 * \details
   Menu test_backup:
    1. Afficher les caractéristiques du joueur
    2. Affiche l'inventaire
    3. Afficher l'équipement
    4. Afficher la carte
    5. Afficher les détails de la carte
    6. Afficher les informations sur les quêtes
 * \details Ce menu permet de comparer avec le résultat obtenu au test de sauvegarde (test_backup.c)
*/
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
        printf("   1. Afficher les caractéristiques du joueur\n");
        printf("   2. Affiche l'inventaire\n");
        printf("   3. Afficher l'équipement\n");
        printf("   4. Afficher la carte\n");
        printf("   5. Afficher les détails de la carte\n");
        printf("   6. Afficher les infos sur les quêtes\n");
        printf("\n\tQuitter -1\n\n");
        printf("\tN°");
        scanf("%d",&nb);

        if(nb != -1){
          switch(nb){
            case 1: clrscr(); display_player_characteristics(map, player); entree_pour_continuer(); break;
            case 2: clrscr(); display_inventory(player); entree_pour_continuer(); break;
            case 3: clrscr(); display_equipment_player(player); entree_pour_continuer(); break;
            case 4: clrscr(); display_TEXT(player.posY,player.posX,map); entree_pour_continuer();  break;
            case 5: clrscr(); informations_map(map); entree_pour_continuer(); break;
            case 6: clrscr(); informations_quetes(map,quest_map,quete); entree_pour_continuer(); break;
            default: printf("\tCommand not found\n"); sleep(1); goto menu; break;
          }
        }
      } while (nb != -1);

  }

  clrscr();
  return EXIT_SUCCESS;
}
