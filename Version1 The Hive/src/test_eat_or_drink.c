#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/commun.h"

/**
 * \file test_eat_or_drink.c
 * \brief Fichier TEST - Manger ou boire un item
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \brief Programme principal pour tester le calcul des points d'énergie lorsque le joueur veut manger/boire un item
 * \details Objectif : Tester les fonctions #eat_or_drink et #gain_energie.
*/
int main(){
  perso_t player;
  cell_t map[D][D];
  init_player(&player,map);

  /*
    * Tests fruits - Gain énergie théorique : 10
  */
  printf ("\033[34;01m   >>> Test FRUITS\033[00m\n\n");
  item_t * fruits = creer_item("fruits",food,0,0,0,0,0,0,0,0,60,10,50);

  player.pe = 90;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fruits);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 50;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fruits);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 60) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 95;
  printf("   PE Joueur = %d [+5 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fruits);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 100;
  printf("   PE Joueur = %d [+0 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fruits);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  free(fruits);

  /*
    * Tests fish - Gain énergie théorique : 15
  */
  printf ("\033[34;01m   >>> Test POISSON\033[00m\n\n");
  item_t * fish = creer_item("poisson",food,0,0,0,0,0,0,0,0,0,0,0);
  player.pe = 85;
  printf("   PE Joueur = %d [+15 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fish);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 50;
  printf("   PE Joueur = %d [+15 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fish);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 65) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 95;
  printf("   PE Joueur = %d [+5 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fish);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 100;
  printf("   PE Joueur = %d [+0 PE attendus]",player.pe);
  add_item_to_inventory(&player,*fish);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  free(fish);

  /*
    * Tests canned food - Gain énergie théorique : 50
  */
  printf ("\033[34;01m   >>> Test BOITE DE CONSERVE\033[00m\n\n");
  item_t * canned_food = creer_item("boite de conserve",food,0,0,0,0,0,0,0,0,0,60,75);
  player.pe = 50;
  printf("   PE Joueur = %d [+50 PE attendus]",player.pe);
  add_item_to_inventory(&player,*canned_food);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 40;
  printf("   PE Joueur = %d [+50 PE attendus]",player.pe);
  add_item_to_inventory(&player,*canned_food);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 90) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 80;
  printf("   PE Joueur = %d [+20 PE attendus]",player.pe);
  add_item_to_inventory(&player,*canned_food);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 100;
  printf("   PE Joueur = %d [+0 PE attendus]",player.pe);
  add_item_to_inventory(&player,*canned_food);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  free(canned_food);
  /*
    * Tests soda - Gain énergie théorique : 12
  */
  printf ("\033[34;01m   >>> Test SODA\033[00m\n\n");
  item_t * soda = creer_item("soda",food,0,0,0,0,0,0,0,0,0,60,50);
  player.pe = 88;
  printf("   PE Joueur = %d [+12 PE attendus]",player.pe);
  add_item_to_inventory(&player,*soda);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 50;
  printf("   PE Joueur = %d [+12 PE attendus]",player.pe);
  add_item_to_inventory(&player,*soda);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 62) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 90;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*soda);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 100;
  printf("   PE Joueur = %d [+0 PE attendus]",player.pe);
  add_item_to_inventory(&player,*soda);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  free(soda);
  /*
    * Tests energy drink - Gain énergie théorique : 20 (+1 PA)
  */
  printf ("\033[34;01m   >>> Test boisson énergie+\033[00m\n\n");
  item_t * energy_drink = creer_item("boisson energie+",food,0,0,0,0,0,0,0,0,0,60,20);
  player.pe = 80; player.pa = 4;
  printf("   PE Joueur = %d [+20 PE attendus]",player.pe);
  add_item_to_inventory(&player,*energy_drink);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> PE Test OK\n") : printf("   --> PE Test KO\n");
  (player.pa == 5) ? printf("   --> PA Test OK\n\n") : printf("   --> PA Test KO\n\n");

  player.pe = 50; player.pa = 2;
  printf("   PE Joueur = %d [+20 PE attendus]",player.pe);
  add_item_to_inventory(&player,*energy_drink);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 70) ? printf("   --> PE Test OK\n") : printf("   --> PE Test KO\n");
  (player.pa == 3) ? printf("   --> PA Test OK\n\n") : printf("   --> PA Test KO\n\n");

  player.pe = 90;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*energy_drink);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> PE Test OK\n\n") : printf("   --> PE Test KO\n\n");

  player.pe = 100; player.pa = 5;
  printf("   PE Joueur = %d [+0 PE et +0 PA attendus]",player.pe);
  add_item_to_inventory(&player,*energy_drink);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> PE Test OK\n") : printf("   --> PE Test KO\n");
  (player.pa == 5) ? printf("   --> PA Test OK\n\n") : printf("   --> PA Test KO\n\n");

  free(energy_drink);

  /*
    * Tests Bottle water - Gain énergie théorique : 10
  */
  printf ("\033[34;01m    >>> Test BOUTEILLE D'EAU\033[00m\n\n");
  item_t * bottle_water = creer_item("bouteille eau",food,0,0,0,0,0,0,0,0,0,50,50);
  player.pe = 90;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*bottle_water);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 50;
  printf("   PE Joueur = %d [+10 PE attendus]",player.pe);
  add_item_to_inventory(&player,*bottle_water);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 60) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 95;
  printf("   PE Joueur = %d [+5 PE attendus]",player.pe);
  add_item_to_inventory(&player,*bottle_water);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  player.pe = 100;
  printf("   PE Joueur = %d [+0 PE attendus]",player.pe);
  add_item_to_inventory(&player,*bottle_water);
  eat_or_drink(&player,player.inventory[0]);
  (player.pe == 100) ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");

  free(bottle_water);
  /*
    * Tests Pistol - Item type weapon
  */
  printf ("\033[34;01m   >>> Test PISTOLET\033[00m");
  item_t * pistol = creer_item("pistolet",weapon,5,25,15,30,85,60,0,1,0,20,60);
  add_item_to_inventory(&player,*pistol);
  eat_or_drink(&player,player.inventory[0]);
  player.nb_items_inventory == 1 ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");
  free(pistol);

  /*
    * Tests Helmet - Item type armor
  */
  printf ("\033[34;01m   >>> Test CASQUE\033[00m");
  item_t * helmet = creer_item("casque",armor,0,0,0,0,0,0,0.6,3,0,0,0);
  add_item_to_inventory(&player,*helmet);
  eat_or_drink(&player,player.inventory[1]);
  player.nb_items_inventory == 2 ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");
  free(helmet);

  /*
    * Tests Map - Item type misc
  */
  printf ("\033[34;01m   >>> Test CARTE\033[00m");
  item_t * map_item = creer_item("carte",misc,0,0,0,0,0,0,0,0,0,20,70);
  add_item_to_inventory(&player,*map_item);
  eat_or_drink(&player,player.inventory[2]);
  player.nb_items_inventory == 3 ? printf("   --> Test OK\n\n") : printf("   --> Test KO\n\n");
  free(map_item);
}
