#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file combat.c
 * \brief Combat
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void retrieve_enemy_items(item_t * Tab_Items, int nb_items_available, perso_t * player)
 * \brief Génère aléatoirement 0 à 3 items (correspondant au sac à dos de l'ennemi) que le joueur peut récupérer s'il le souhaite.
 * \details Cette fonction est appelée uniquement si le joueur gagne au combat.
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \param perso_t * player
 * \return Rien
*/
void retrieve_enemy_items(item_t * Tab_Items, int nb_items_available, perso_t * player){
  int i, choise, nb, taille = rand()%4;  // Maximum 3 items trouvés
  int ind_items_found[taille];

   // Initialisation du tableau ind_items_found à -1
  for(i = 0; i < taille; i++){
    ind_items_found[i] = -1;
  }

  // Le tableau ind_items_found contient les indices des items trouvés dans le tableau Tab_Items
  for(i = 0; i < taille; i++){
      ind_items_found[i] = rand()%nb_items_available;
  }

  // Si item(s) généré(s)
  if (taille != 0){
    // Cas 1 item généré
    if(taille == 1){
      // Choix : récupérer ou non l'item ?
      printf("Il a %s sur lui.\n\n   Souhaitez-vous le récupérer ? (Oui: 1  Non: 0) \n", Tab_Items[ind_items_found[0]].name);
      printf("   Votre réponse : ");
      do {
        scanf("%d",&choise);
        if (choise < 0 || choise > 1){
          printf("   Valeur incorrecte. Veuillez ressaisir : ");
        }
      } while(choise < 0 || choise > 1);

      if(choise){
        // Ajout de l'item à l'inventaire du joueur
        add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
        entree_pour_continuer();
      }
    }
    // Plusieurs items générés
    else {
      printf(" %d items!\n", taille);

      do{
        // Affichage des items générés
        printf("\n   ====== SAC A DOS ENNEMI ======\n");
        for(i = 0; i < taille; i++){
          printf("   N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
        }
        printf("   ==============================\n");

        // Choix : récupérer ou non les items ?
        (taille == 1) ? printf("\n   1. Ajouter cet item dans votre inventaire\n") : printf("\n   1. Ajouter un de ces items dans votre inventaire\n");
        printf("   2. Rien récupérer\n");
        printf("\n   Votre réponse : ");
        do {
          scanf("%d",&choise);
          if (choise < 1 || choise > 2){
            printf("   Valeur incorrecte. Veuillez ressaisir : ");
          }
        } while(choise < 1 || choise > 2);

        if(choise == 1){
            printf("\n   Quel item souhaitez-vous récupérer? N°");
            do {
              scanf("%d",&nb);
              if (nb < 0 || nb > taille-1){
                printf("   Valeur incorrecte. Veuillez ressaisir : ");
              }
            } while(nb < 0 || nb > taille-1);

            if(add_item_to_inventory(player,Tab_Items[ind_items_found[nb]])){
              // L'item choisi a été ajouté à l'inventaire donc on le retire des items trouvés sur cet hexagone
              // Cela empêche qu'on puisse ajouter plusieurs fois le même item!
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
          // Le joueur refuse de récupérer l'/les item(s)
          (taille == 1) ? printf("\n   Vous ne prenez pas cet item.\n\n") : printf("\n   Vous ne prenez pas ces items.\n\n");
          entree_pour_continuer();
        }
      } while((choise != 2) && (taille > 0));
    }
  }
  // Aucun item généré
  else{
      printf("\n   Son sac est vide.\n\n");
      entree_pour_continuer();
  }
}

/**
 * \fn void loot_enemy (item_t * Tab_Items, int nb_items_available, npc_t * enemy, perso_t * player)
 * \brief Propose au joueur de récupérer l'arme et/ou l'armure et/ou les items de l'ennemi.
 * \details Cette fonction est appelée uniquement si le joueur gagne au combat.
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \param npc_t * enemy
 * \param perso_t * player
 * \return Rien
*/
void loot_enemy (item_t * Tab_Items, int nb_items_available, npc_t * enemy, perso_t * player){
  int answer;

  // Si l'ennemi ne portait aucune arme ou armure
  if(enemy->weapon == NULL && enemy->armor == NULL){
    printf("\n   L'ennemi ne portait aucune arme ou armure.\n\n");
    entree_pour_continuer();
  }
  else {
    // Si l'ennemi portait une arme
    if(enemy->weapon != NULL) {
      // Choix : récupérer l'arme ou non ?
      printf("\n   L'ennemi portait une arme : %s. Souhaitez-vous la prendre ? (Oui: 1  Non: 0)\n",enemy->weapon->name);
      printf("   Votre réponse : ");
      do {
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("   Valeur incorrecte. Veuillez ressaisir : ");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->weapon)){
          enemy->weapon = NULL;
          entree_pour_continuer();
        }
      }
    }
    clrscr();

    // Si l'ennemi portait une armure
    if (enemy->armor != NULL) {
      // Choix : récupérer l'armure ou non ?
      printf("\n   L'ennemi portait une armure : %s. Souhaitez-vous la prendre ? (Oui: 1  Non: 0)\n",enemy->armor->name);
      printf("   Votre réponse : ");
      do {
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("   Valeur incorrecte. Veuillez ressaisir : ");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->armor)){
          enemy->armor = NULL;
          entree_pour_continuer();
        }
      }
    }

  }

  clrscr();

  // Fouiller le sac à dos de l'ennemi (items)
  printf("\n   Voyons voir ce que l'ennemi a dans son sac à dos... ");
  retrieve_enemy_items(Tab_Items,nb_items_available,player);
}


/**
 * \fn void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int cover, int scenario)
 * \brief Calcule les dommages causés par l'attaquant (scénario 1 : ennemi, scénario 2 : joueur)
 * \param item_t * weapon
 * \param item_t * armor
 * \param int * hp
 * \param int distance
 * \param int cover
 * \param int scenario
 * \return Rien
*/
void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int cover, int scenario){
  float damage;
  /*
   * Attaquant ?
   * - Scénario 1 : ennemi
   * - Scénario 2 : joueur
   */
  // Calcul chance que l'attaquant touche sa cible selon la distance qui les sépare et la couverture de sa cible
  if(distance <= 2){
    if(rng(weapon->hitchance[distance]-(15*cover))){
      if(armor==NULL){
        damage=weapon->attack[distance];
      }
      else{ // Si la cible a une armure, prise en compte de sa valeur de défense dans le calcul des dommages causés
        damage=weapon->attack[distance]*(armor->defense);
      }
      *(hp)=*(hp)-damage; // PV de la cible mis à jour en fonction des dommages causés

      switch(scenario){
        case 1: printf("   L'ennemi vous attaque avec %s et vous inflige %d points de dommage !\n", weapon->name, (int)(damage)); break;
        case 2: printf("   Vous infligez %d points de dommage à l'ennemi !\n", (int)(damage)); break;
        default: break;
      }
    }else{
      switch(scenario){
        case 1: printf("   L'ennemi a essayé de vous attaquer mais a échoué lamentablement.\n"); break;
        case 2: printf("   Vous avez raté. Quelle déception.\n"); break;
        default: break;
      }
    }
  }
  else{
    switch(scenario){
      case 1: printf("   L'ennemi a essayé de vous attaquer mais a échoué lamentablement.\n"); break;
      case 2: printf("   Vous avez raté. Quelle déception.\n"); break;
      default: break;
    }
  }
}

/**
 * \fn npc_t * init_npc(item_t * Tab_Items)
 * \brief Initialise un non-player character (NPC) ennemi (nom,arme,armure et points de vie)
 * \param item_t * Tab_Items
 * \return Pointeur sur npc_t
*/
npc_t * init_npc(item_t * Tab_Items){
  npc_t * enemy;
  enemy = malloc(sizeof(npc_t));

  strcpy(enemy->name,"maraudeur");
  enemy->weapon=NULL;
  enemy->armor=NULL;
  enemy->pv=0;

  if(rng(65)){ // 65% de chance que ce maraudeur soit de classe "léger"
    enemy->pv=40;
    if(rng(70)){ // 70% de chance qu'il ait une batte de baseball
      enemy->weapon=&Tab_Items[5];
    }else{ // 30% qu'il ait un couteau
      enemy->weapon=&Tab_Items[3];
    }
  }else if(rng(30)){ // 30% de chance que ce maraudeur soit de classe "moyen"
    enemy->pv=80;
    if(rng(30)){ // 30% de chance qu'il ait un pistolet
      enemy->weapon=&Tab_Items[0];
    }else{ // 70% qu'il ait une batte de baseball et un gilet pare-balles
      enemy->weapon=&Tab_Items[5];
      enemy->armor=&Tab_Items[6];
    }
  }else{ // 5% de chance que ce maraudeur soit de classe "lourd"
    enemy->pv=120;
    // L'ennemi a un gilet pare-balles
    enemy->armor=&Tab_Items[6];
    if(rng(5)){ //5% de chance qu'il ait un fusil
      enemy->weapon=&Tab_Items[2];
    }else if(rng(40)){ // 40% de chance qu'il ait un pistolet
      enemy->weapon=&Tab_Items[0];
    }else{ // 55% de chance qu'il ait une batte de baseball
      enemy->weapon=&Tab_Items[5];
    }
  }

  return enemy;
}

/**
 * \fn stat_t * init_field()
 * \brief Initialise le champ de bataille du combat (positions et couvertures des adversaires, distance qui les sépare)
 * \return Pointeur sur stat_t
*/
stat_t * init_field(){
  stat_t * field;
  field=malloc(sizeof(stat_t));
  field->posA=1;
  field->posB=6;
  field->coverA=0;
  field->coverB=0;
  field->distance=(field->posB - field->posA) -1;
  return field;
}

/**
 * \fn void turn_npc(npc_t * enemy, stat_t * field, perso_t * player)
 * \brief Tour du non-player character (NPC) lors du combat
 * \param npc_t * enemy
 * \param stat_t * field
 * \param perso_t * player
 * \return Rien
*/
void turn_npc(npc_t * enemy, stat_t * field, perso_t * player){
	field->coverB=0;
  field->distance=field->posB-field->posA -1;
  /*
   * Si l'ennemi porte FUSIL
   */
	if(strcmp(enemy->weapon->name,"fusil") == 0){
      // Attitude NPC si distance > 2 : l'ennemi avance vers le joueur.
			if(field->distance > 2){
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   L'ennemi se dirige vers vous !\n");
			}
      // Attitude NPC si distance == 0
      else if(field->distance == 0){
				if(rng(60) && (field->posB < 6)){  // 60% de chance que l'ennemi s'éloigne du joueur si c'est possible
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   L'ennemi s'éloigne de vous !\n");
				}else if(rng(30)){  // 30% de chance que l'ennemi se mette à l'abri
					field->coverB=1;
          printf("   L'ennemi décide de se défendre.\n");
				}else{  // L'ennemi essaie d'attaquer
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
				}
			}
      // Attitude NPC si distance == 1
      else if(field->distance == 1){
				if(enemy->pv > 50){   // Si ses points de vie sont supérieurs à 50, l'ennemi essaie d'attaquer.
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }else{
          if(rng(50)){ // 50% de chance que l'ennemi se mette à l'abri.
            field->coverB=1;
            printf("   L'ennemi décide de se défendre.\n");
          }else{
            // L'ennemi essaie d'attaquer
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
          }
        }
			}
      // Attitude NPC si distance == 2
      else if(field->distance == 2){
        if(rng(40)){ // 40% de chance que l'ennemi avance vers le joueur
          field->posB-=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   L'ennemi se dirige vers vous !\n");
        }else if(rng(30)){ // 30% de chance que l'ennemi se mette à l'abri
          field->coverB=1;
          printf("   L'ennemi décide de se défendre.\n");
        }else{ // L'ennemi essaie d'attaquer
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }
		}
    /*
     * Si l'ennemi porte PISTOLET
     */
    else if(strcmp(enemy->weapon->name,"pistolet") == 0){
      // Attitude NPC si distance > 2 : l'ennemi avance vers le joueur
      if(field->distance > 2){
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   L'ennemi se dirige vers vous !\n");
			}
      // Attitude NPC si distance == 0
      else if(field->distance == 0){
				if(rng(80) && (field->posB < 6)){  // 80% de chance que l'ennemi s'éloigne du joueur si c'est possible
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   L'ennemi s'éloigne de vous !\n");
        }else if(rng(30)){  // 30% de chance que l'ennemi se mette à l'abri
					field->coverB=1;
          printf("   L'ennemi décide de se défendre.\n");
				}else{ // L'ennemi essaie d'attaquer
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
				}
			}
      // Attitude NPC si distance == 1
      else if(field->distance == 1){
        if(rng(40) && (field->posB < 6)){ // 40% de chance que l'ennemi s'éloigne du joueur si c'est possible
          field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   L'ennemi s'éloigne de vous !\n");
        }else if(rng(30)){ // 30% de chance que l'ennemi se mette à l'abri
          field->coverB=1;
          printf("   L'ennemi décide de se défendre.\n");
        }else{ // L'ennemi essaie d'attaquer.
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }
      // Attitude NPC si distance == 2
      else if(field->distance == 2){
				if(enemy->pv > 50){  // Si ses points de vie sont supérieurs à 50, l'ennemi essaie d'attaquer.
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
        else if(rng(50)){ // 50% de chance que l'ennemi se mette à l'abri
            field->coverB=1;
            printf("   L'ennemi décide de se défendre.\n");
        }else{ // L'ennemi essaie d'attaquer.
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
     }
	 }
   /*
    * Si l'ennemi porte une arme CORPS A CORPS
    */
   else{
     // Attitude NPC si distance > 0
      if(field->distance>0){
        if(rng(80)){ // 80% de chance que l'ennemi avance vers le joueur
          field->posB-=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   L'ennemi se dirige vers vous !\n");
        }else{ // 20% de chance que l'ennemi se mette à l'abri
          field->coverB=1;
          printf("   L'ennemi décide de se défendre.\n");
        }
      }
      // Attitude NPC si distance == 0 : l'ennemi essaie d'attaquer
      else if(field->distance==0){
        damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
      }
  }
}

/**
 * \fn int run_away(int position, int distance, cell_t map[D][D], perso_t * player)
 * \brief Détermine si le joueur réussit à fuir ou non (selon sa position et la distance qui le sépare de son ennemi)
 * \param int position
 * \param int distance
 * \return Un \a int : 1 si le joueur réussit à fuir. 0 s'il échoue.
*/
int run_away(int position, int distance, cell_t map[D][D], perso_t * player){
  if(position!=1){
    if(rng(20*distance)){
      printf("   Vous avez réussi à vous enfuir.\n\n");
      random_move(player,map);
      return 1;
    }else{
      printf("   Vous avez essayé de vous enfuir mais vous avez échoué.\n");
    }
  }else{
    if(rng(40*distance)){
      printf("   Vous avez réussi à vous enfuir.\n\n");
      random_move(player,map);
      return 1;
    }else{
      printf("   Vous avez essayé de vous enfuir mais vous avez échoué.\n");
    }
  }
  return 0;
}

/**
 * \fn void afficher_lettre(int chiffre, stat_t field)
 * \brief Affiche les lettres correspondant au joueur et à l'ennemi si le chiffre passé en paramètre correspond à leur position
 * \param int chiffre
 * \param stat_t field
 * \return Rien
*/
void afficher_lettre(int chiffre, stat_t field){
  if(field.posA == chiffre){
    printf("  J  ");
  }
  else if(field.posB == chiffre){
    printf("  E  ");
  }
  else {
    printf("     ");
  }
}

/**
 * \fn void show_field(stat_t field)
 * \brief Affiche le champ de bataille du combat en indiquant où se situent le joueur et l'ennemi
 * \param stat_t field
 * \return Rien
*/
void show_field(stat_t field){
  printf("\n    Champ de bataille :       +-----+-----+-----+-----+-----+-----+\n");
  printf("    J : Joueur                |");
  afficher_lettre(1,field);
  printf("|");
  afficher_lettre(2,field);
  printf("|");
  afficher_lettre(3,field);
  printf("|");
  afficher_lettre(4,field);
  printf("|");
  afficher_lettre(5,field);
  printf("|");
  afficher_lettre(6,field);
  printf("|");
  printf("\n    E : Ennemi                +-----+-----+-----+-----+-----+-----+\n");
}


/**
 * \fn void combat_info(int print_type, perso_t player, npc_t enemy, stat_t field)
 * \brief Affiche les informations sur le joueur et l'ennemi (pv, armes, armures, distance), le champ de bataille et les actions possibles lors du combat
 * \param int print_type
 * \param perso_t player
 * \param npc_t enemy
 * \param stat_t field
 * \return Rien
*/
void combat_info(int print_type, perso_t player, npc_t enemy, stat_t field){
  /*
   * Affichage des informations du combat
   */
  printf("\n   ======================= INFORMATIONS COMBAT =========================\n");
  printf("    Vos PV : %3d                    PV Ennemi : %3d\n",player.pv,enemy.pv);
  if((print_type == 2) || (print_type == 3)){
    switch(print_type){
      case 2: printf("    Arme : %-20s     Arme ennemi : %-20s\n",player.left_hand->name,enemy.weapon->name); break;
      case 3: printf("    Arme : %-20s     Arme ennemi : %-20s\n",player.right_hand->name,enemy.weapon->name); break;
      default: break;
    }
    if(player.body != NULL){
      printf("    Armure : %-20s",player.body->name);
      (enemy.armor != NULL) ? printf("   Armure ennemi : %-20s\n",enemy.armor->name) : printf("\n");
    }
    else{
      (enemy.armor != NULL) ? printf("    Pas d'armure                    Armure ennemi : %-20s\n",enemy.armor->name) : printf("    Pas d'armure\n");
    }
  }
  else {
    printf("    Arme 1 : %-20s   Arme ennemi : %-20s\n",player.left_hand->name,enemy.weapon->name);
    (enemy.armor != NULL) ? printf("    Arme 2 : %-20s   Armure ennemi : %-20s\n",player.right_hand->name,enemy.armor->name) : printf("    Arme 2 : %-20s\n",player.right_hand->name);
    (player.body != NULL) ? printf("    Armure : %-20s\n", player.body->name) : printf("    Pas d'armure\n");
  }

  printf("\n    Distance: %d",field.distance);
  (field.distance > 1) ? printf(" unités\n") : printf(" unité");
  show_field(field);
  printf("   =====================================================================\n");

  /*
   * Affichage menu combat
   */
  printf("\033[34;01m\n   Menu combat\033[00m\n");
  if(print_type==1){
    printf("   1. Se rapprocher de l'ennemi\n   2. S'éloigner de l'ennemi\n   3. Se défendre\n   4. Attaquer avec %s\n   5. Attaquer avec %s\n   6. Essayer de s'enfuir\n", player.left_hand->name, player.right_hand->name);
  }else if(print_type==2){
    printf("   1. Se rapprocher de l'ennemi\n   2. S'éloigner de l'ennemi\n   3. Se défendre\n   4. Attaquer avec %s\n   5. Essayer de s'enfuir\n", player.left_hand->name);
  }
  else if (print_type==3){
    printf("   1. Se rapprocher de l'ennemi\n   2. S'éloigner de l'ennemi\n   3. Se défendre\n   4. Attaquer avec %s\n   5. Essayer de s'enfuir\n", player.right_hand->name);
  }

  printf("\n   Votre choix : ");
}


/**
 * \fn void combat(perso_t * player, npc_t * enemy, stat_t * field, cell_t map[D][D], item_t * Tab_Items, int nb_items_available)
 * \brief Fonction principale du combat qui gère les actions du joueur et ennemi
 * \param perso_t * player
 * \param npc_t * enemy
 * \param stat_t * field
 * \cell_t map[D][D]
 * \item_t * Tab_Items
 * \int nb_items_available
 * \return Rien
*/
void combat(perso_t * player, npc_t * enemy, stat_t * field, cell_t map[D][D], item_t * Tab_Items, int nb_items_available){
  int choise, choise_max, print_type;

  // Détermine la configuration du joueur
  if(player->left_hand!=NULL && player->right_hand!=NULL){  // Le joueur a une arme dans chaque main
    print_type=1;
  }else if(player->left_hand!=NULL && player->right_hand==NULL){ // Le joueur a seulement une arme à la main gauche
    print_type=2;
  }else if(player->left_hand==NULL && player->right_hand!=NULL){ // Le joueur a seulement une arme à la main droite
    print_type=3;
  }else{
    printf("\n   N'ayant pas d'arme, vous n'avez d'autres choix que de prendre la fuite !\n\n");
    entree_pour_continuer();
    return;
  }

  choise_max = (print_type == 1) ? 6 : 5; // Nombre de choix proposés dans le menu suivant suivant la valeur de print_type

  while(player->pv>0 && enemy->pv>0){
    field->coverA=0;
    checkpoint:
    clrscr();
    combat_info(print_type,*player,*enemy,*field);
    // Choix par l'utilisateur (+ vérification)
    do {
      scanf("%d",&choise);
      if((choise < 1) || (choise > choise_max)){
        printf("   Commande inconnue. Veuillez ressaisir : ");
      }
    } while((choise < 1) || (choise > choise_max));

    clrscr();
    printf("\n   \033[1;32mVotre tour :\033[00m\n");
    /*
     * Se rapprocher de l'ennemi
     */
    if(choise==1){
      if((field->posA+1) < (field->posB)){
        field->posA+=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   Vous réussissez à vous rapprocher d'une unité de votre ennemi.");
      }else{
        printf("   Vous ne pouvez pas vous rapprocher plus de votre ennemi, sauf si vous avez la capacité de traverser la matière. Essayez autre chose.\n\n");
        entree_pour_continuer();
        goto checkpoint;
      }
    }
    /*
     * S'éloigner de l'ennemi
     */
    else if(choise==2){
      if(field->posA-1>0){
        field->posA-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   Vous réussissez à vous éloigner d'une unité de votre ennemi.\n");
      }else{
        printf("   Vous avez atteint la frontière du champ de bataille. Vous ne pouvez pas aller plus loin. Si vous voulez vous enfuir, choisissez cette option dans le menu.\n\n");
        entree_pour_continuer();
        goto checkpoint;
      }
    /*
     * Se défendre
     */
    }else if(choise==3){
      field->coverA=1; printf("   Vous réussissez à vous défendre.\n");
    }
    /*
     * print_type 1 = Attaquer avec arme (main gauche)
     * print_type 2 ET 3 = Attaquer avec arme
     */
    else if(choise==4){
      if(print_type == 1){ // Le joueur essaie d'attaquer avec son arme (main gauche)
        damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else if(print_type == 2){ // Le joueur essaie d'attaquer avec son arme (main gauche)
        damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else if(print_type == 3){ // Le joueur essaie d'attaquer avec son arme (main droite)
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
    }
    /*
     * print_type 1 : Attaquer avec arme (main droite)
     * print_type 2 ou 3 : Essayer de s'enfuir
     */
    else if(choise==5){
      if(print_type == 1){ // Le joueur essaie d'attaquer avec son arme (main droite)
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else {
        if(run_away(field->posA, field->distance,map,player)){ // Le joueur essaie de fuir
          entree_pour_continuer();
          return ;
        }
      }
    }
    /*
     * Essayer de s'enfuir (seulement pour print_type == 1)
     */
    else if(choise==6){
      if(run_away(field->posA, field->distance,map,player)){ // Le joueur essaie de fuir
        entree_pour_continuer();
        return;
      }
    }

    /*
     * Tour ennemi
     */
    printf("\n\n   \033[1;32mTour ennemi :\033[00m\n");
    turn_npc(enemy,field, player);
    printf("\n");
    entree_pour_continuer();
  }

  clrscr();

  // Si le joueur gagne le combat
  if(enemy->pv <= 0){
    printf("\n   Félicitations, vous avez réussi à tuer votre ennemi. Voulez-vous le piller ?\n   1 - Oui\n   2 - Non\n\n   Votre choix : ");
    do{
      scanf("%d", &choise);
      if(choise<1 || choise>2){
        printf("   Valeur incorrecte. Veuillez ressaisir : ");
      }
    } while (choise<1 || choise>2);

    if(choise==1){
      clrscr();
      loot_enemy(Tab_Items,nb_items_available,enemy,player);
      free(enemy);
      free(field);
    } else if(choise==2){
      clrscr();
      printf("\n   Très bien, continuez d'explorer les environs alors.\n\n");
      entree_pour_continuer();
    }
  }
  // Si le joueur perd le combat
  else if(player->pv <= 0){
    printf("\n   Vous vous êtes fait tuer. Vous aurez peut-être plus de chance la prochaine fois.\n");
    sleep(3);
    clrscr();
    exit(0);
  }
}
