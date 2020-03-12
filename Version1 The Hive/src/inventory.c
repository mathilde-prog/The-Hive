//inventory.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/* map_in_inventory: returns 1 if the player has a map in his inventory (0 otherwise). */
int map_in_inventory(perso_t player){
	int i;

	for(i = 0; (i < player.nb_items_inventory) && strcmp(player.inventory[i].name,"map"); i++);
	return (i < player.nb_items_inventory);
}

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

/* display_inventory: displays the content of the inventory of the player */
void display_inventory (perso_t player){
	int i, cpt;

	if(player.nb_items_inventory == 0){
		printf("Empty inventory (no item)\n");
	}

	else {
		/* display items from the inventory */
		if(player.nb_items_inventory > 1){
			printf("========== INVENTORY (%d items) ==========\n\n", player.nb_items_inventory);
		}
		else {
			printf("========== INVENTORY (%d item) ==========\n\n", player.nb_items_inventory);
		}

		printf("\t\t[ WEAPONS ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory ; i++){
			if(player.inventory[i].type == weapon){
				printf("N°%2d\t%20s\t", i, player.inventory[i].name);
				is_equipped(player,player.inventory[i]) ? printf("equipped\n") : printf("\n");
				cpt++;
			}
		}

		if(cpt == 0){
			printf("\t  No weapon in stock\n");
		}

		printf("\n\t\t[ ARMORS ]\n");

		for(i = 0, cpt = 0; i < player.nb_items_inventory ; i++){
			if(player.inventory[i].type == armor){
				printf("N°%2d\t%20s\t", i, player.inventory[i].name);
				is_equipped(player,player.inventory[i]) ? printf("equipped\n") : printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t   No armor in stock\n");
		}

		printf("\n\t\t[ MISCS ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory; i++){
			if(player.inventory[i].type == misc){
				printf("N°%2d\t%20s\t", i, player.inventory[i].name);
				printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t    No misc in stock\n");
		}

		printf("\n\t\t[ FOOD ]\n");
		for(i = 0, cpt = 0; i < player.nb_items_inventory; i++){
			if(player.inventory[i].type == food){
				printf("N°%2d\t%20s\t", i, player.inventory[i].name);
				printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t    No food in stock\n");
		}

		printf("\n==========================================\n\n");
	}
}

/* delete_item_in_inventory: deletes an item from the inventory */
void delete_item_in_inventory(perso_t * player, item_t item){
	int ind = item.index;
	int i, eq_lh, eq_rh, eq_b, eq_h;

 	if(ind != -1){ // Si item est présent dans l'inventaire du joueur
		if(is_equipped(*player,item)){
			switch(is_equipped(*player,item)){
				case LEFT_HAND: player->left_hand = NULL; break;
				case RIGHT_HAND: player->right_hand = NULL; break;
				case BODY: player->body = NULL; break;
				case HEAD: player->head = NULL; break;
				default: break;
			}
			printf("%s has been removed from your inventory and equipment.\n",item.name);
		}
		else {
			printf("%s has been removed from your inventory\n",item.name);
		}

		// Update des pointeurs équipement
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

		// On supprime l'item de l'inventaire
		(player->nb_items_inventory)--;
		i = ind;
		while(i < (player->nb_items_inventory)){
			player->inventory[i] = player->inventory[i+1];
			player->inventory[i].index--;
 			i++;
		}
	}
 	else {
 		printf("%s isn't in your inventory.\n",item.name);
 	}
}

/* add_item_to_inventory: adds an item to the inventory. If full inventory, proposes an exchange  */
int add_item_to_inventory(perso_t * player, item_t item){
	int answer, nb;

	if(!too_much_of_the_same_item(* player, item)){

		if(player->nb_items_inventory < INVENTORY_CAPACITY){

			// Changement car il rentre dans l'inventaire
			item.index = player->nb_items_inventory;

			player->inventory[player->nb_items_inventory] = item;
			(player->nb_items_inventory)++;
			printf("\n%s added to your inventory.\n", item.name);
			return 1;
		}

	 	else {
			do {
				printf("Would you like to keep this item and give up one of your inventory? (YES: 1, NO: 0)\n");
		 		scanf("%d",&answer);
				if(answer < 0 || answer > 1){
					printf("Input error. Please re-enter\n");
				}
			} while (answer < 0 || answer > 1);

	 		if(answer){
				do {
					display_inventory(*player);
					printf("Which item do you want to exchange ? (-1 to cancel) N°");
		 			scanf("%d", &nb);
					if((nb != -1) && (nb < 0 || nb > player->nb_items_inventory - 1)){
						printf("Wrong number... This item isn't in your inventory!\n");
					}
				}while((nb != -1) && (nb < 0 || nb > player->nb_items_inventory - 1));

				if(nb != -1){
					printf("%s has been replaced by %s.\n", player->inventory[nb].name, item.name);
					delete_item_in_inventory(player,player->inventory[nb]);
					nb = player->nb_items_inventory-1;
					// Changement car il rentre dans l'inventaire
					item.index = nb;
					player->inventory[nb] = item;
					return 1;
				}
	 		}
			return 0;
		}
	}
	else {
			printf("You can't take another %s with you, you already have two!\n", item.name);
			return 0;
	}
}

/* manage_inventory: menu inventory */
void manage_inventory(perso_t * player){
	int nb, choise;

	if(!player->nb_items_inventory){
		display_inventory(*player);
		printf("There's nothing you can do...\n");
		sleep(3);
	}
	else {
		do {
			// Menu management inventory
			display_inventory(*player);
			if(player->nb_items_inventory){
				do {
					printf("What do you want to do ?\n");
					printf("1. Get rid of an item\n");
					printf("2. Eat or drink an item\n");
					printf("3. Know more about an item\n");
					printf("Exit inventory: -1\n\n");
					printf("N°");
					scanf("%d", &choise);
					if((choise != -1) && (choise < 1 && choise > 2)){
						printf("Incorrect value. Please re-enter\n");
					}
				} while ((choise != -1) && (choise < 1 && choise > 2));
			}
			else {
				printf("Exit inventory: -1\n\n");
				do {
					printf("N°");
					scanf("%d", &choise);
					if(choise != -1){
						printf("Type -1 to return to the inventory menu\n");
					}
				} while (choise != -1);
			}

			if(choise != -1){
				switch(choise){
					// Get rid of an item
					case 1: do {
										printf("\nWhich item do you want to delete ? (-1 to cancel) N°");
										scanf("%d", &nb);
										if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
											printf("Wrong number... This item isn't in your inventory!\n");
										}
									} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));
									if(nb != -1){
											delete_item_in_inventory(player,player->inventory[nb]);
											sleep(2);
									}
									break;
					//Eat or drink an item
					case 2: do {
										printf("\nWhich item do you want to eat or drink ? (-1 to cancel) N°");
										scanf("%d", &nb);
										if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
											printf("Wrong number... This item isn't in your inventory!\n");
										}
									} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));
									if(nb != -1){
										eat_or_drink(player,player->inventory[nb]);
										sleep(3);
									}
									break;
					//Know more about an item
					case 3: do {
										printf("\nOn which item would you like more information? (-1 to cancel) N°");
										scanf("%d", &nb);
										if((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1))){
											printf("Wrong number... This item isn't in your inventory!\n");
										}
									} while((nb != -1) && (nb < 0 || nb > (player->nb_items_inventory - 1)));
									if(nb != -1){
										display_item(player->inventory[nb]);
										do {
											printf("Back to the menu (1) : ");
											scanf("%d",&nb);
											if(nb != 1){
												printf("Type 1 to return to the inventory menu\n");
											}
										} while (nb != 1);
									}
									break;
					default: break;
				}
				clrscr();
			}
		} while (choise != -1);
	}
}
