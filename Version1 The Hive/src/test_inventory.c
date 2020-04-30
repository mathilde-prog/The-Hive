#include <stdio.h>
#include <stdlib.h>
#include "lib/structure.h"

/* Fichier test pour la gestion de l'inventaire */

void test_suivant(){
  int rep;

  do {
    printf("Passer au test suivant (1) : ");
    scanf("%d", &rep);
  } while (rep != 1);
  clrscr();
}

int main(){
  // Déclarations
  perso_t player;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;

  if(creation_tab_item(Tab_Items, &nb_items_available)){
    init_player(&player);

    printf(">>> Début du test\n\n");

    printf ("\033[34;01m[TEST N°1 - Inventaire vide]\033[00m\n");
    display_inventory(player);
    test_suivant();

    printf ("\033[34;01m[TEST N°2 - AJOUT QUELQUES ITEMS DANS INVENTAIRE]\033[00m\n");
    add_item_to_inventory(&player, Tab_Items[17]); //bottle_water
    add_item_to_inventory(&player, Tab_Items[0]);  //pistol
    add_item_to_inventory(&player, Tab_Items[10]); //rope
    add_item_to_inventory(&player, Tab_Items[2]);  //shotgun
    add_item_to_inventory(&player, Tab_Items[7]);  //helmet
    add_item_to_inventory(&player, Tab_Items[8]);  //fishing_rod
    add_item_to_inventory(&player, Tab_Items[4]);  //bow_arrows
    add_item_to_inventory(&player, Tab_Items[12]); //map
    add_item_to_inventory(&player, Tab_Items[14]); //fish
    add_item_to_inventory(&player, Tab_Items[0]);  //pistol
    printf("\n");
    display_inventory(player);
    test_suivant();

    printf ("\033[34;01m[TEST N°3 - too much of the same item (pistol)]\033[00m\n");
    add_item_to_inventory(&player, Tab_Items[0]);  //pistol
    test_suivant();

    printf ("\033[34;01m[TEST N°4- échange d'un item]\033[00m\n");
    printf("SUPPRIMEZ MAP POUR CE TEST ! \n");
    add_item_to_inventory(&player, Tab_Items[6]); //knife
    display_inventory(player);
    test_suivant();

    printf ("\033[34;01m[TEST N°5- suppression d'un item seule sans échange]\033[00m\n");
    display_inventory(player);
    printf("On supprime %s de l'inventaire.\n", player.inventory[5].name);
    delete_item_in_inventory(&player, player.inventory[5]); // fishing_rod
    display_inventory(player);
    test_suivant();

    printf ("\033[34;01m[TEST N°6- échange avec gestion équipement]\033[00m\n");
    add_item_to_inventory(&player, Tab_Items[8]); // fishing rod
    printf("Ajout équipement\n");
    player.head = &player.inventory[4];       //helmet
    player.right_hand = &player.inventory[1]; //pistol
    player.left_hand = &player.inventory[3];  // shotgun
    display_equipment_player(player);
    add_item_to_inventory(&player,Tab_Items[15]);
    display_inventory(player);
    test_suivant();


    printf(">>> Fin des tests\n");
  }
  else {
    printf("ECHEC récupération des données items\n");
  }
  return EXIT_SUCCESS;
}
