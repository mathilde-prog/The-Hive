//equipment.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structure.h"

/*	display_equipment_player : displays the equipment of the player */
void display_equipment_player(perso_t player){
	printf("=============== EQUIPMENT ================\n");

	printf("Head : ");
	(player.head != NULL) ? (printf("%s\t\t(N°%2d)\n", player.head->name, player.head->index)) : (printf("no equipment\n"));

	printf("Left hand : ");
	(player.left_hand != NULL) ? (printf("%s\t(N°%2d)\n", player.left_hand->name, player.left_hand->index)) : (printf("no equipment\n"));

	printf("Right hand : ");
	(player.right_hand != NULL) ? (printf("%s\t(N°%2d)\n", player.right_hand->name, player.right_hand->index)) : (printf("no equipment\n"));

	printf("Body : ");
	(player.body != NULL) ? (printf("%s\t(N°%2d)\n", player.body->name, player.body->index)) : (printf("no equipment\n"));

	printf("==========================================\n\n");
}

/*	is_equipped : - indicates if the player is equipped with the item passed in parameter.
	 							 	- if the player is equipped with the item, return where it is equipped (LEFT_HAND = 1, RIGHT_HAND = 2, BODY = 3, HEAD = 4)(cf. structure.h)
								 	- if the player isn't equipped with the item, return NOT_EQUIPPED = 0 (cf. structure.h)
*/
int is_equipped(perso_t player, item_t item){
	switch(item.equipable){
		case none : return 0;
		case hand : if(player.left_hand != NULL){
									if(player.left_hand->index == item.index){
										return LEFT_HAND;
									}
								}
								if (player.right_hand != NULL){
									if(player.right_hand->index == item.index){
										return RIGHT_HAND;
									}
								}
								return NOT_EQUIPPED;

		case body:  if(player.body != NULL){
									if(player.body->index == item.index){
										return BODY;
									}
								}
								return NOT_EQUIPPED;
		case head:  if(player.head != NULL){
									if (player.head->index == item.index){
										return HEAD;
									}
								}
								return NOT_EQUIPPED;
		default: return NOT_EQUIPPED;
	}
}

/*	swap_equipment_player: exchange of items on the player's equipment */
void swap_equipment_player(perso_t * player, item_t item){
	int num = 0;

	printf("You'll have to exchange %s with another item you're already wearing if you want to equip it!\n",item.name);

	switch(item.equipable){
		case hand: 	printf("1. %s (left_hand)\n",player->left_hand->name);
								printf("2. %s (right_hand)\n",player->right_hand->name);
								printf("Cancel : -1\n");
								do{
									printf("With which one do you want to swap %s ? N°", item.name);
									scanf("%d",&num);
									if((num != -1) && (num < 1 || num > 2)){
										printf("Input error. Please re-enter\n");
									}
								} while((num != -1) && (num < 1 || num > 2));

								if(num != -1){
									if(num == 1){
										player->left_hand = &player->inventory[item.index];
									}
									else if (num == 2){
										player->right_hand = &player->inventory[item.index];
									}
									printf("You are now equipped with %s.\n", item.name);
								}

								break;
		case body:	do {
									printf("Are you sure you want to swap %s with %s ? (YES = 1, NO = 0)",player->body->name,item.name);
		 							scanf("%d", &num);
									if(num < 0 || num > 1){
										printf("Input error. Please re-enter\n");
									}
								} while (num < 0 || num > 1);

								if(num){
									player->body = &player->inventory[item.index];
									printf("You are now equipped with %s.\n", item.name);
								}
								break;
		case head: do {
									printf("Are you sure you want to swap %s with %s ? (YES = 1, NO = 0)",player->head->name,item.name);
		 							scanf("%d", &num);
									if(num < 0 || num > 1){
										printf("Input error. Please re-enter\n");
									}
								} while (num < 0 || num > 1);

								if(num){
									player->head = &player->inventory[item.index];
									printf("You are now equipped with %s.\n", item.name);
								}
								break;
		default: break;
	}
}

/*	equip_player: equip the player with an item (which must be equippable) that he has in his inventory. Equip it in the right place. */
void equip_player(perso_t * player){
	int num;

	if(player->nb_items_inventory != 0){
		display_inventory(*player);
		do {
			printf("Which item of your inventory do you want to equip ? N°");
			scanf("%d",&num);
			if(num > player->nb_items_inventory){
				printf("Wrong number... This item isn't in your inventory!\n");
			}
		} while(num > player->nb_items_inventory);

		if(!is_equipped(*player,player->inventory[num])){

			switch(player->inventory[num].equipable){
				case none : printf("You can't equip this item!\n"); break;
				case hand :	if(player->left_hand == NULL){
											player->left_hand = &player->inventory[num];
											printf("You are now equipped with %s.\n", player->inventory[num].name);

										}
										else if (player->right_hand == NULL){
											player->right_hand = &player->inventory[num];
											printf("You are now equipped with %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]);
										}
										break;
				case body : if(player->body == NULL){
											player->body = &player->inventory[num];
											printf("You are now equipped with %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]);
										}
										break;
				case head : if(player->head == NULL){
											player->head = &player->inventory[num];
											printf("You are now equipped with %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]);
										}
										break;
				default : break;
			}

		}
		else {
			printf("You're already equipped of %s!\n\n",player->inventory[num].name);
		}
	}
	else {
		printf("You don't have any items in your inventory. So you can't equip yourself!\n");
	}
}

/*	remove_equipment_player: removes an item from the player's equipment */
void remove_equipment_player(perso_t * player){
	int num;

	do{
		printf("\nWhich equipment do you want to remove ? (-1 to cancel) N°");
		scanf("%d",&num);
		if(!is_equipped(*player,player->inventory[num]) && num != -1){
			printf("Wrong number... This item isn't equipped!\n");
		}
	} while(!is_equipped(*player,player->inventory[num]) && num != -1);

	switch(is_equipped(*player,player->inventory[num])){
		case LEFT_HAND: player->left_hand = NULL; break;
		case RIGHT_HAND: player->right_hand = NULL; break;
		case BODY: player->body = NULL; break;
		case HEAD: player->head = NULL; break;
		default: break;
	}

	if(num != -1){
		printf("%s has been removed from your equipment.\n",player->inventory[num].name);
		sleep(2);
	}
}

/* manage_equipment: equipment menu */
void manage_equipment(perso_t * player){
	int choise;

	jump:
	display_equipment_player(* player);
	printf("What do you want to do ?\n");
	do {
		printf("1. Equip an item from your inventory\n");
		printf("2. Remove an item from your equipment\n");
		printf("Exit equipment: -1\n\n");
		printf("N°");
		scanf("%d",&choise);
		if((choise != -1) && (choise < 1 || choise > 2)){
			printf("Incorrect value. Please re-enter\n");
		}
	} while ((choise != -1) && (choise < 1 || choise > 2));

	if(choise != -1){
		switch(choise){
			case 1: printf("\n"); equip_player(player); sleep(2); break;
			case 2: remove_equipment_player(player); break;
			default: break;
		}
		clrscr();
		goto jump;
	}
}
