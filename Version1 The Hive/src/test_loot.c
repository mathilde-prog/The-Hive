#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

// Parler du pb claws avec Moustapha
void retrieve_enemy_items(item_t * Tab_Items, int nb_items_available, perso_t * player){
  int i, choise, nb, taille = rand()%4;  // Maximum 3 items trouvés
  int ind_items_found[taille];


  for(i = 0; i < taille; i++){
    ind_items_found[i] = -1;
  }

  for(i = 0; i < taille; i++){
      ind_items_found[i] = rand()%nb_items_available;
  }

  // Si items générés
  if (taille != 0){
    // Cas 1 item
    if(taille == 1){
      do {
        printf("\nIl a %s sur lui. Souhaitez-vous le récupérer ? (Oui: 1  Non: 0) \n", Tab_Items[ind_items_found[0]].name);
        scanf("%d",&choise);
        if (choise < 0 || choise > 1){
          printf("Valeur incorrecte. Veuillez resaissir.\n");
        }
      } while(choise < 0 || choise > 1);

      if(choise){
        add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
        sleep(2);
      }
    }
    // Plusieurs items trouvés
    else {
      printf("%d items!\n", taille);

      do{
        // Affichage des items trouvés
        printf("====== SAC A DOS ENNEMI ======\n");
        for(i = 0; i < taille; i++){
          printf("N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
        }
        printf("==============================\n");

        do {
          (taille == 1) ? printf("1. Ajouter cet item dans votre inventaire\n") : printf("1. Ajouter un de ces items dans votre inventaire\n");
          printf("2. Rien récupérer\n");
          scanf("%d",&choise);
          if (choise < 1 || choise > 2){
            printf("Valeur incorrecte. Veuillez resaissir.\n");
          }
        } while(choise < 1 || choise > 2);

        if(choise == 1){
            do {
              printf("Quel item souhaitez-vous récupérer? N°");
              scanf("%d",&nb);
              if (nb < 0 || nb > taille-1){
                printf("Valeur incorrecte. Veuillez resaissir.\n");
              }
            } while(nb < 0 || nb > taille-1);

            if(add_item_to_inventory(player,Tab_Items[ind_items_found[nb]])){
              // Cet item a été ajouté à l'inventaire donc on l'enlève des items trouvés sur cet hexagone
              // Empèche qu'on puisse en ajouter plusieurs!
              i = nb;
              while(i < taille){
                ind_items_found[i] = ind_items_found[i+1];
                i++;
              }
              taille--;
              sleep(2);
              clrscr();
            }
        }
        else {
          (taille == 1) ? printf("Vous ne prenez pas cet item.\n") : printf("Vous ne prenez pas ces items.\n");
          sleep(1);
        }
      } while((choise != 2) && (taille > 0));
    }
  }
  else{
      printf("Son sac est vide.\n");
      sleep(1);
  }
}

void loot_enemy (item_t * Tab_Items, int nb_items_available, npc_t * enemy, perso_t * player){
  int answer;

  printf("Voyons voir ce que l'ennemi a dans son sac à dos... ");
  retrieve_enemy_items(Tab_Items,nb_items_available,player);
  clrscr();

  if(enemy->weapon == NULL && enemy->armor == NULL){
    printf("L'ennemi ne porte aucune arme ou armure.\n");
    sleep(2);
  }
  else {
    if(enemy->weapon != NULL){
      do {
        printf("Souhaitez-vous prendre son arme (%s) ? (Oui: 1  Non: 0)\n",enemy->weapon->name);
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("Valeur incorrecte. Veuillez ressaisir.\n");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->weapon)){
          enemy->weapon = NULL;
          sleep(2);
        }
      }
    }
    else {
      printf("L'ennemi ne porte pas d'arme.\n");
      sleep(2);
    }

    clrscr();

    if(enemy->armor != NULL){
      do {
        printf("Souhaitez-vous prendre son armure (%s) ? (Oui: 1  Non: 0)\n",enemy->armor->name);
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("Valeur incorrecte. Veuillez ressaisir\n");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->armor)){
          enemy->armor = NULL;
          sleep(2);
        }
      }
    }
    else {
      printf("L'ennemi ne porte pas d'armure.\n");
      sleep(2);
    }
  }
  clrscr();
}

int main(){
  srand(time(NULL));

  perso_t player;
  cell_t map[D][D];
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  npc_t enemy1;
  int quest_map[6][2];
  quete_t quete;
  int chance_weapon = rand()%2, chance_armor = rand()%2;

  if(creation_tab_item(Tab_Items, &nb_items_available)){
      init_player(&player);
      map_init(map,quest_map,player);
      init_quete(&quete,quest_map);
      clrscr();
      chance_weapon ? (enemy1.weapon = &Tab_Items[0]) : (enemy1.weapon = NULL); //pistol ou NULL
      chance_armor ? (enemy1.armor = &Tab_Items[7]) : (enemy1.armor = NULL);    // helmet ou NULL
      loot_enemy(Tab_Items, nb_items_available, &enemy1, &player);
      display_inventory(player);
      free(Tab_Items);
    }


  return EXIT_SUCCESS;
}
