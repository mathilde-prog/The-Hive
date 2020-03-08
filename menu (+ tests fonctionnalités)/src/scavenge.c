#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

/*************************************** SCAVENGE **********************************************/

// category_hexagon: returns the category of a hexagon. The map and hexagon coordinates are passed in parameters.
categ_hexa category_hexagon (int map[D][D], int x, int y){
  hex_t hexagone = map[x][y];
  categ_hexa categ;

  switch(hexagone){
      case prairie   : categ = nature;    break;     //prairie
      case foret     : categ = nature;    break;     //foret
      case ville     : categ = urbain;    break;     //ville
      case lac       : categ = nature;    break;     //lac
      case camp_mil  : categ = militaire; break;     //camp mil
      case camp_ban  : categ = other;     break;     //camp_ban
      case market    : categ = urbain;    break;     //market
      case favella   : categ = urbain;    break;     //favella
      case montagne  : categ = nature;    break;     //montagne
      case frontiere : categ = other;     break;     //frontiere
      case mer       : categ = nature;    break;     //mer
      case wasteland : categ = nature;    break;     //wasteland
      default : break;
  }

  return categ;
}

/* generate_items: generates 0 to 5 items randomly according to the type of hexagon
and the percentage of chance of items appearing on this type of hexagon */
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ){
    int i, ind, present, cpt = 0, choise;
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
        printf("Congratulations, you found %d item : %s\n", cpt, Tab_Items[ind_items_found[0]].name);

        do {
          printf("Do you want to add %s to your inventory ? (Yes = 1, No = 0)\n", Tab_Items[ind_items_found[0]].name);
          scanf("%d",&choise);
          if (choise < 0 || choise > 1){
            printf("Incorrect value. Please re-enter.\n");
          }
        } while(choise < 0 || choise > 1);

        if(choise){
          add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
        }
      }
      // Plusieurs items trouvés
      else {
        printf("Congratulations, you just found %d items!\n", cpt);

        do{
          // Affichage des items trouvés
          printf("===== ITEMS FOUND ====\n");
          for(i = 0; i < cpt; i++){
            printf("N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
          }
          printf("======================\n");

          do {
            printf("1. Add an item to my inventory\n");
            printf("2. Retrieve no items\n");
            scanf("%d",&choise);
            if (choise < 1 || choise > 2){
              printf("Incorrect value. Please re-enter.\n");
            }
          } while(choise < 1 || choise > 2);

          if(choise == 1){
              do {
                printf("Which item do you want to add to your inventory? N°");
                scanf("%d",&choise);
                if (choise < 0 || choise > cpt-1){
                  printf("Incorrect value. Please re-enter.\n");
                }
              } while(choise < 0 || choise > cpt-1);

              if(add_item_to_inventory(player,Tab_Items[ind_items_found[choise]])){
                // Cet item a été ajouté à l'inventaire donc on l'enlève des items trouvés sur cet hexagone
                // Empêche qu'on puisse en ajouter plusieurs!
                i = choise;
                while(i < cpt){
                  ind_items_found[i] = ind_items_found[i+1];
                  i++;
                }
                cpt--;
              }
          }
          else {
            printf("You don't retrieve any items\n");
          }

        } while((choise != 2) && (cpt > 0));
      }
    }
    else{
        printf("There's nothing to pick up here...\n");
    }
}

/* scavenge */
void scavenge(int map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available){
    categ_hexa categ = category_hexagon(map, player->posX, player->posY);

    if(categ != other){
      generate_items(Tab_Items, nb_items_available, player, categ);
    }
    else { // Aucun item généré si frontière ou
      printf("Nothing appears!\n");
    }
}

/***********************************************************************************************/
