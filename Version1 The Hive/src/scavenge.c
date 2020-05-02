#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "lib/structure.h"

/**
 * \file scavenge.c
 * \brief Fonctionnalité : fouiller l'hexagone pour récupérer des items
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ)
 * \brief Génère aléatoirement 0 à 5 items en prenant en compte le pourcentage de chance des items d'apparaître dans un type d'hexagone en particulier.
 * \details Propose au joueur de récupérer les items générés
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \param perso_t * player
 * \param categ_hexa categ
 * \return Rien
*/
/* generate_items: generates 0 to 5 items randomly according to the type of hexagon
and the percentage of chance of items appearing on this type of hexagon */
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ){
    int i, ind, present, cpt = 0, choise, nb;
    // Remarque: cpt correspond au nombre d'items qui apparaissent sur l'hexagone

    int ind_items_found[ITEMS_MAX]; // tableau contenant les indices des items trouvés (à quels indices ils sont dans TabItems!)
    // On initialise tout le tableau à -1 (Pourquoi -1 ? Signifie non-présent dans Tab_Items)
    for(i = 0; i < ITEMS_MAX; i++){
      ind_items_found[i] = -1;
    }

    // Génération aléatoire de 0 à ITEMS_MAX items
    for(i = 0; i < ITEMS_MAX; i++){
        ind = rand()%nb_items_available;
        switch(categ){
          case nature:    present = rng(Tab_Items[ind].pc_nature);   break;
          case urbain:    present = rng(Tab_Items[ind].pc_urban);    break;
          case militaire: present = rng(Tab_Items[ind].pc_military); break;
          default: present = 0; break;
        }
        if (present == 1){
          ind_items_found[cpt] = ind;
          cpt++;
        }
    }

    // Si items générés
    if (cpt != 0){
      // Cas 1 item
      if(cpt == 1){
        printf("\n   Félicitation, vous avez trouvé un item : %s\n", Tab_Items[ind_items_found[0]].name);
        printf("   Souhaitez-vous ajouter %s à votre inventaire ? (Oui = 1, Non = 0)\n", Tab_Items[ind_items_found[0]].name);
        printf("   Réponse : ");
        do {
          scanf("%d",&choise);
          if (choise < 0 || choise > 1){
            printf("   Valeur incorrecte. Veuillez ressaisir : ");
          }
        } while(choise < 0 || choise > 1);

        if(choise){
          add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
          sleep(2);
        }
      }
      // Plusieurs items trouvés
      else {
        printf("\n   Félicitation, vous avez trouvé %d items!\n", cpt);

        do{
          // Affichage des items trouvés
          printf("\n   ===== VOUS AVEZ TROUVE ====\n");
          for(i = 0; i < cpt; i++){
            printf("   N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
          }
          printf("   =========================\n\n");

          printf("   1. Ajouter un item trouvé dans votre inventaire\n");
          printf("   2. Rien récupérer\n");
          printf("   Réponse : ");
          do {
            scanf("%d",&choise);
            if (choise < 1 || choise > 2){
              printf("   Valeur incorrecte. Veuillez ressaisir : ");
            }
          } while(choise < 1 || choise > 2);

          if(choise == 1){
            printf("   Quel item souhaitez-vous ajouter votre inventaire? N°");
            do {
              scanf("%d",&nb);
              if (nb < 0 || nb > cpt-1){
                printf("   Valeur incorrecte. Veuillez ressaisir : ");
              }
            } while(nb < 0 || nb > cpt-1);

            if(add_item_to_inventory(player,Tab_Items[ind_items_found[nb]])){
              // Cet item a été ajouté à l'inventaire donc on l'enlève des items trouvés sur cet hexagone
              // Empèche qu'on puisse en ajouter plusieurs!
              i = nb;
              while(i < cpt){
                ind_items_found[i] = ind_items_found[i+1];
                i++;
              }
              cpt--;
              sleep(2);
              clrscr();
            }
          }
          else {
            (cpt == 1) ? printf("   Vous ne prenez pas cet item.\n") : printf("   Vous ne prenez pas ces items.\n");
            sleep(1);
          }
        } while((choise != 2) && (cpt > 0));
      }
    }
    else{
        printf("\n   Il n'y a rien à récupérer ici...\n");
        sleep(1);
    }
}

/**
 * \fn void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available)
 * \brief Permet au joueur de fouiller l'hexagone sur lequel il se trouve pour récupérer des items
 * \param cell_t map[D][D]
 * \param perso_t * player
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Rien
*/
/* Recherche des items */
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available){
    categ_hexa categ = map[player->posX][player->posY].categ;

    // Si le joueur n'a pas déjà scavengé l'hexagone où il est
    if(map[player->posX][player->posY].scavenged == 1){
      printf("\n   Vous êtes déjà passé par là!\n");
      sleep(2);
    }
    else {
      if(categ != other){
        generate_items(Tab_Items, nb_items_available, player, categ);
      }
      else { // Aucun item généré
        printf("\n   Rien n'apparaît!\n");
        sleep(2);
      }
      map[player->posX][player->posY].scavenged = 1;
    }
}
