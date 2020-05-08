#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file inventory.c
 * \brief Gestion de l'inventaire du joueur
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void check_the_map(perso_t player, cell_t map[D][D])
 * \brief Affiche la carte, si le joueur en possède une dans son inventaire
 * \param perso_t player
 * \param cell_t map[D][D]
 * \return Rien
*/
void check_the_map(perso_t player, cell_t map[D][D]){
	// vérifie si le joueur possède une carte dans son inventaire
	if(item_in_inventory(player,"carte") != -1){
		display_TEXT(player.posY, player.posX ,map);
	}
	else {
		printf("\n   Pour voir la carte, vous avez besoin d'en avoir une dans votre inventaire. \n");
		printf("   Pour plus d'informations, allez jeter un oeil à l'aide au menu principal! \n\n");
		entree_pour_continuer();
	}
}

/**
 * \fn int item_in_inventory(perso_t player, char * nom_item)
 * \brief Recherche si l'item dont le nom est passé en paramètre est présent ou non dans l'inventaire
 * \param perso_t player
 * \param char * nom_item
 * \return Un \a int : position de l'item dans l'inventaire si présent, -1 si absent
*/
int item_in_inventory(perso_t player, char * nom_item){
	int i;
	for(i = 0; (i < player.nb_items_inventory) && strcmp(player.inventory[i].name, nom_item); i++);
	if(i < player.nb_items_inventory){
		return player.inventory[i].index;
	}
	else {
		return -1;
	}
}

/**
 * \fn int food_in_inventory(perso_t player)
 * \brief Calcule le nombre d'items food dans l'inventaire du joueur
 * \param perso_t player
 * \return Un \a int : nombre d'items food dans l'inventaire du joueur
*/
int food_in_inventory(perso_t player){
	int i, cpt;
	for(i = 0; i < player.nb_items_inventory; i++){
		if(player.inventory[i].type == food){
			cpt++;
		}
	}
	return cpt;
}


/**
 * \fn int too_much_of_the_same_item(perso_t player, item_t item)
 * \brief Indique si l'item passé en paramètre apparaît 2 fois ou plus dans l'inventaire du joueur
 * \details Remarque : Un item peut figurer au maximum 2 fois dans l'inventaire du joueur
 * \param perso_t player
 * \param item_t item
 * \return Un \a int : retourne 1 si l'item est présent 2 fois ou plus dans l'inventaire. 0 sinon.
*/
/* too_much_of_the_same_item: returns 1 if an item is present 2 times or more in the inventory.*/
int too_much_of_the_same_item(perso_t player, item_t item){
	int i, occ = 0;

	for(i = 0; (i < player.nb_items_inventory); i++){
		if(!strcmp(player.inventory[i].name,item.name)){
			occ++;
		}
	}

	return (occ >= 2);
}

/**
 * \fn void display_inventory (perso_t player)
 * \brief Affiche l'inventaire du joueur
 * \details Affichage des items de l'inventaire avec leurs positions, par catégorie (armes, armures, divers, nourriture). Indique si item équipé pour les armes et armures.
 * \param perso_t player
 * \return Rien
*/
void display_inventory (perso_t player){
	int i, cpt;

	if(player.nb_items_inventory == 0){
		printf("\n   Votre inventaire est vide. Vous ne pouvez rien faire ici sans item.\n\n");
		entree_pour_continuer();
	}
	else {
		/* display items from the inventory */
		if(player.nb_items_inventory > 1){
			printf("\n   ========== INVENTAIRE (%d items) ==========\n\n", player.nb_items_inventory);
		}
		else {
			printf("\n   ========== INVENTAIRE (%d item) ==========\n\n", player.nb_items_inventory);
		}

		printf("\t\t   [ ARMES ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory ; i++){
			if(player.inventory[i].type == weapon){
				printf("   N°%2d\t%20s\t", player.inventory[i].index, player.inventory[i].name);
				is_equipped(player,player.inventory[i]) ? printf("équipé\n") : printf("\n");
				cpt++;
			}
		}

		if(cpt == 0){
			printf("\t     Aucune arme en stock\n");
		}

		printf("\n\t\t   [ ARMURES ]\n");

		for(i = 0, cpt = 0; i < player.nb_items_inventory ; i++){
			if(player.inventory[i].type == armor){
				printf("   N°%2d\t%20s\t", player.inventory[i].index, player.inventory[i].name);
				is_equipped(player,player.inventory[i]) ? printf("équipé\n") : printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t      Aucune armure en stock\n");
		}

		printf("\n\t\t   [ DIVERS ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory; i++){
			if(player.inventory[i].type == misc){
				printf("   N°%2d\t%20s\t", player.inventory[i].index, player.inventory[i].name);
				printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t     Aucun item divers en stock\n");
		}

		printf("\n\t\t   [ NOURRITURE ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory; i++){
			if(player.inventory[i].type == food){
				printf("   N°%2d\t%20s\t", player.inventory[i].index, player.inventory[i].name);
				printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t     Aucune nourriture en stock\n");
		}

		printf("\n   ==========================================\n\n");
	}
}

/**
 * \fn void delete_item_in_inventory(perso_t * player, item_t item)
 * \brief Retire l'item passé en paramètre de l'inventaire (et de l'équipement si besoin) du joueur
 * \param perso_t * player
 * \param item_t item
 * \return Rien
*/
void delete_item_in_inventory(perso_t * player, item_t item){
	int i, eq_lh, eq_rh, eq_b, eq_h, ind = item.index;

 	if(ind != -1){ // Si item est présent dans l'inventaire du joueur
		if(is_equipped(*player,item)){
			switch(is_equipped(*player,item)){
				case LEFT_HAND: 	player->left_hand = NULL; 	break;
				case RIGHT_HAND: 	player->right_hand = NULL;	break;
				case BODY: 				player->body = NULL; 				break;
				case HEAD: 				player->head = NULL; 				break;
				default: break;
			}
			printf("   %s a été retiré de votre inventaire et équipement.\n",item.name);
		}
		else {
			printf("   %s a été retiré de votre inventaire.\n",item.name);
		}

		// On supprime l'item de l'inventaire
		(player->nb_items_inventory)--;
		for(i = ind; i < player->nb_items_inventory; i++){
			player->inventory[i] = player->inventory[i+1];
			player->inventory[i].index--;
		}

		// Mise à jour des pointeurs pour l'équipement
		if(player->left_hand != NULL){
			eq_lh = player->left_hand->index;
			if(eq_lh > ind){
				player->left_hand = &player->inventory[eq_lh-1];
			}
		}

		if(player->right_hand != NULL){
			eq_rh =  player->right_hand->index;
			if(eq_rh > ind){
				player->right_hand = &player->inventory[eq_rh-1];
			}
		}

		if(player->body != NULL){
			eq_b =  player->body->index;
			if(eq_b > ind){
				player->body = &player->inventory[eq_b-1];
			}
		}

		if(player->head != NULL){
			eq_h =  player->head->index;
			if(eq_h > ind){
				player->head = &player->inventory[eq_h-1];
			}
		}
	}
 	else {
 		printf("   %s n'est pas dans votre inventaire.\n",item.name);
 	}
}

/**
 * \fn int add_item_to_inventory(perso_t * player, item_t item)
 * \brief Ajoute un item à l'inventaire du joueur. Si son inventaire est plein, propose un échange.
 * \param perso_t * player
 * \param item_t item
 * \return Un \a int : 1 si ajout effectué. 0 sinon.
*/
int add_item_to_inventory(perso_t * player, item_t item){
	int rep, num; // variables pour choix du joueur

	// vérifie si l'item n'est pas déjà trop présent
	if(!too_much_of_the_same_item(*player, item)){

		// si on peut ajouter l'item directement dans l'inventaire
		if(player->nb_items_inventory < INVENTORY_CAPACITY){
			item.index = player->nb_items_inventory;
			player->inventory[item.index] = item;
			(player->nb_items_inventory)++;
			printf("\n   %s ajouté à votre inventaire.\n", item.name);
			return 1; // ajout effectué
		}
		// si inventaire déjà plein, on propose de faire un échange pour ajouter l'item
	 	else {
			printf("   Souhaitez-vous garder cet item en échange d'un de votre inventaire ? (Oui: 1, Non: 0)\n");
			printf("   Votre réponse : ");
			do {
		 		scanf("%d",&rep);
				if(rep < 0 || rep > 1){
					printf("   Valeur incorrecte. Veuillez ressaisir : ");
				}
			} while (rep < 0 || rep > 1);

	 		if(rep){
				display_inventory(*player);
				printf("   Quel item souhaitez-vous échanger ? (-1 pour annuler) N°");
				do {
					scanf("%d", &num);
					if((num != -1) && ((num < 0) || (num > (player->nb_items_inventory-1)))){
						printf("   Valeur incorrecte... Cet item ne figure pas dans votre inventaire! Veuillez ressaisir : ");
					}
				}while((num != -1) && ((num < 0) || (num > (player->nb_items_inventory-1))));

				// si échange accepté
				if(num != -1){
					printf("   %s a été remplacé par %s.\n", player->inventory[num].name, item.name);
					delete_item_in_inventory(player,player->inventory[num]);

					// Changement car il rentre dans l'inventaire
					item.index = player->nb_items_inventory;
					player->inventory[item.index] = item;
					(player->nb_items_inventory)++;
					return 1;
				}
	 		}
			return 0;
		}
	}
	else {
			printf("   Vous ne pouvez pas prendre %s avec vous, vous en avez déjà deux!\n", item.name);
			return 0;
	}
}

/**
 * \fn void manage_inventory(perso_t * player)
 * \brief Fonction centrale du fichier inventory.c permettant au joueur de gérer son inventaire
 * \details Menu inventaire : Possibilité pour le joueur d'en savoir plus sur un de ses items, de se débarasser d'un item, de manger/boire un item, d'utiliser son kit médical (s'il en possède un)
 * \param perso_t * player
 * \return Rien
*/
/* manage_inventory: menu inventory */
void manage_inventory(perso_t * player){
	int nb, choise, ind_food, ind_mk, choix_max, val;

	do {
			display_inventory(*player);

			if(!player->nb_items_inventory){
				return;
			}

			ind_food = food_in_inventory(*player);
			ind_mk = item_in_inventory(*player,"kit medical");
			if((ind_mk != -1) && ind_food){
				choix_max = 4;
			}
			else if(ind_food || (ind_mk != -1)){
				choix_max = 3;
			}
			else {
				choix_max = 2;
			}

			// Menu management inventory
			printf("   Que souhaitez-vous faire ?\n");
			printf("   1. En savoir plus sur un item\n");
			printf("   2. Se débarasser d'un item\n");

			if((choix_max == 4) || ((choix_max == 3) && ind_food)){
				printf("   3. Manger ou boire un item\n");
			}
			else if((choix_max == 3) && !ind_food){
				printf("   3. Utiliser votre kit médical\n");
			}

			if(choix_max == 4){
				printf("   4. Utiliser votre kit médical\n");
			}

			printf("\n   Retour menu principal : -1\n\n");
			printf("   Votre choix : ");
			do {
				scanf("%d", &choise);
				if((choise != -1) && (choise < 1 || choise > choix_max)){
					printf("   Valeur incorrecte. Veuillez ressaisir : ");
				}
			} while ((choise != -1) && (choise < 1 || choise > choix_max));

			if(choise != -1){
				// En savoir plus sur un item
				if(choise == 1){
					printf("\n   A propos de quel item souhaitez-vous en savoir plus ? (-1 pour annuler) N°");
					do {
						scanf("%d", &nb);
						if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
							printf("   Valeur incorrecte... Cet item ne figure pas dans votre inventaire! Veuillez ressaisir : ");
						}
					} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));

					if(nb != -1){
						clrscr();
						display_item(player->inventory[nb]);
						entree_pour_continuer();
					}
				}
				// Se débarasser d'un item
				else if (choise == 2){
					printf("\n   De quel item souhaitez-vous vous débarrasser ? (-1 pour annuler) N°");
					do {
						scanf("%d", &nb);
						if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
							printf("   Valeur incorrecte... Cet item ne figure pas dans votre inventaire! Veuillez ressaisir : ");
						}
					} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));
					if(nb != -1){
						delete_item_in_inventory(player,player->inventory[nb]);
						sleep(2);
					}
				}
				// Manger ou boire un item
				else if (choise == 3 && ind_food) {
					printf("\n   Quel item souhaitez-vous manger ou boire ? (-1 pour annuler) N°");
					do {
						scanf("%d", &nb);
						if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
							printf("   Valeur incorrecte... Cet item ne figure pas dans votre inventaire! Veuillez ressaisir : ");
						}
					} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));
					if(nb != -1){
						eat_or_drink(player,player->inventory[nb]);
						entree_pour_continuer();
					}
				}
				// Utiliser kit médical
				else if((choise == 4) || ((choise == 3) && (ind_mk != -1))){
					val = 30;
					if((player->pv + val) > 100){
				    val = (100 - player->pv);
				  }

				  if(val != 0){
				    player->pv += val;
						printf("   Kit médical utilisé... PV+%d\n",val);
						delete_item_in_inventory(player,player->inventory[ind_mk]);
				  }

					else {
						printf("\n   Vous n'avez pas besoin de soins.\n");
					}
					sleep(2);
				}
			}
			clrscr();
	} while (choise != -1);
}
