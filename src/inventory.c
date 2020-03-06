//inventory.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

/* indice: search if the item passed in parameter is present in the player's inventory. Returns the index if present, -1 if absent.*/
int indice(perso_t player, item_t item){
	int i;

	for(i = 0; (i < player.nb_items_inventory) && strcmp(player.inventory[i].name,item.name); i++);
	if(i > player.nb_items_inventory){
		return -1;
	}
	else {
		return i;
	}
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
		printf("Empty inventory (no item)\n\n");
	}

	else {
		/* display items from the inventory */
		printf("======== INVENTORY (%d items) ========\n\n", player.nb_items_inventory);
		int val;

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
				is_equipped(player,player.inventory[i]) ? printf("equipped\n") : printf("\n");
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
				is_equipped(player,player.inventory[i]) ? printf("equipped\n") : printf("\n");
				cpt++;
			}
		}

		if(!cpt){
			printf("\t    No food in stock\n");
		}

		printf("\n====================================\n\n");
	}
}

/* delete_item_in_inventory: deletes an item from the inventory */
void delete_item_in_inventory(perso_t * player, item_t item){
	int ind = indice(*player, item);
	int i, eq_lh, eq_rh, eq_b, eq_h;

 	if(ind != -1){
		if(is_equipped(*player,item)){
				switch(is_equipped(*player,item)){
				case LEFT_HAND: player->left_hand = NULL; break;
				case RIGHT_HAND: player->right_hand = NULL; break;
				case BODY: player->body = NULL; break;
				case HEAD: player->head = NULL; break;
				default: break;
			}
			printf("%s has been removed from your equipment.\n",item.name);
		}
		(player->nb_items_inventory)--;
		i = ind;
		while(i < (player->nb_items_inventory)){
			player->inventory[ind] = player->inventory[i+1];
 			i++;
		}
		printf("%s has been removed from your inventory\n",item.name);

		if(player->left_hand != NULL){
			eq_lh = indice(*player,*player->left_hand);
			if(eq_lh > ind){
				player->left_hand = &player->inventory[eq_lh-1];
			}
		}
		if(player->right_hand != NULL){
			eq_rh = indice(*player,*player->right_hand);
			if(eq_rh > ind){
				player->right_hand = &player->inventory[eq_rh-1];
			}
		}
		if(player->body != NULL){
			eq_b = indice(*player,*player->body);
			if(eq_b > ind){
				player->body = &player->inventory[eq_b-1];
			}
		}
		if(player->head != NULL){
			eq_h = indice(*player,*player->head);
			if(eq_h > ind){
				player->head = &player->inventory[eq_h-1];
			}
		}
	}
 	else {
 		printf("%s isn't in your inventory.\n",item.name);
 	}
}

/* add_item_to_inventory: adds an item to the inventory. If full inventory, proposes an exchange  */
void add_item_to_inventory(perso_t * player, item_t item){
	int answer, nb;

	if(!too_much_of_the_same_item(* player, item)){

		if(player->nb_items_inventory < INVENTORY_CAPACITY){
			player->inventory[player->nb_items_inventory] = item;
			(player->nb_items_inventory)++;
			printf("%s added to your inventory.\n", item.name);
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
					printf("%s has been replaced by ", player->inventory[nb].name);
					player->inventory[nb] = item;
					printf("%s!\n",player->inventory[nb].name);
				}
	 		}
		}
	}
	else {
			printf("You can't take another %s with you, you already have two!\n", item.name);
	}
}
