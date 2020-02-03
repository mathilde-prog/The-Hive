#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define ARMOR 0
#define WEAPON 1
#define MISC 2
#define FOOD 3

/* Displays all the characteristics of an item (name,type,value of attack, value of defense, equipped or not) */
void display_item (item_t item){
	printf("Item : %s\n",item.name);

	printf("Type : ");
	switch(item.type){
		case 0: printf("armor\n"); break;
		case 1: printf("weapon\n"); break;
		case 2: printf("misc\n"); break;
		case 3: printf("food\n"); break;
		default: printf("unrecognized\n"); break;
	}

	printf("Attack : %d\n",item.attack);
	printf("Defense : %d\n",item.defense);

	item.equipped ? printf("Equipped!\n") : printf("Not equipped\n");

	printf("\n");
}

/* Displays the content of the inventory of the player */
void display_inventory (item_t * inventory, int nb_items){
	int i, cpt;

	if(!nb_items){
		printf("Your inventory is empty (no item)\n");
	}

	else {
		printf("==================== MY INVENTORY (%d items) ====================\n\n", nb_items);
		/* display items from the inventory */
		printf("=== MY WEAPONS ===\n");
		for(i = 0, cpt = 0; i < nb_items; i++){
			if(inventory[i].type == WEAPON){
				printf("Item %d: %10s\n", i, inventory[i].name);
				cpt++;
			}
		}

		if(!cpt){
			printf("No weapon in stock\n");
		}

		printf("\n");

		printf("=== MY ARMORS ===\n");
		for(i = 0, cpt = 0; i < nb_items; i++){
			if(inventory[i].type == ARMOR){
				printf("Item %d: %10s\n", i, inventory[i].name);
				cpt++;
			}
		}

		if(!cpt){
			printf("No armor in stock\n");
		}

		printf("\n");

		printf("=== MY MISCS ===\n");
		for(i = 0, cpt = 0; i < nb_items; i++){
			if(inventory[i].type == MISC){
				printf("Item %d: %10s\n", i, inventory[i].name);
				cpt++;
			}
		}

		if(!cpt){
			printf("No misc in stock\n");
		}

		printf("\n");

		printf("=== MY FOOD ===\n");
		for(i = 0, cpt = 0; i < nb_items; i++){
			if(inventory[i].type == FOOD){
				printf("Item %d: %10s\n", i, inventory[i].name);
				cpt++;
			}
		}

		if(!cpt){
			printf("No food in stock\n");
		}

		printf("\n");
		printf("======================================================\n\n");
	}
}

/* Deletes an item from the inventory */
void delete_item_in_inventory(item_t * inventory, int * nb_items, item_t item){
	int i;

	/* Find out whether the item that the player wants to delete exists in the inventory */
	for(i = 0; (i < *nb_items) && strcmp(inventory[i].name,item.name); i++);

	if(!strcmp(inventory[i].name,item.name)){
		inventory[i].equipped = 0;
		(*nb_items)--;
		while(i < *nb_items){
			strcpy(inventory[i].name,inventory[i+1].name);
			inventory[i].type = inventory[i+1].type;
			inventory[i].attack = inventory[i+1].attack;
			inventory[i].defense = inventory[i+1].defense;
			inventory[i].equipped = inventory[i+1].equipped;

			i++;
		}
	}
	else {
		printf("%s isn't in your inventory.\n",item.name);
	}
}

/* Inventory menu for the player  */
void menu_inventory(item_t * inventory, int * nb_items){
	int nb, choice;

	display_inventory(inventory, *nb_items);

	if(nb_items > 0){

		do{
				do{
					printf("What do you want to do ? \n");
					printf("1. Know more about an item \n");
					printf("2. Delete an item\n");
					printf("3. Exit\n");
					scanf("%d",&choice);

					if(choice < 1 || choice > 3){
							printf("Entry error\n");
					}
				} while (choice < 1 || choice > 3);

				if(choice == 1){
						printf("==== KNOW MORE ABOUT AN ITEM ====\n");
						do{
							printf("About which item do you want to know more ? Give its number: \n");
							scanf("%d", &nb);

							if(nb < 0 || nb >= *nb_items){
								printf("Entry error\n");
							}
						} while(nb < 0 || nb >= *nb_items);

						display_item(inventory[nb]);

						do {
							do {
								printf("Do you want to know more about an another item ? (YES: 1, NO: 0)\n");
								scanf("%d", &choice);

								if(choice < 0 || choice > 1){
									printf("Entry error\n");
								}
							} while (choice < 0 || choice > 1);

							if(choice == 1){
								do{
									display_inventory(inventory, *nb_items);
									printf("Give me its number: \n");
									scanf("%d", &nb);

									if(nb < 0 || nb >= *nb_items){
										printf("Entry error\n");
									}
								} while(nb < 0 || nb >= *nb_items);

								display_item(inventory[nb]);
							}
						} while (choice == 1);
				}

				else if (choice == 2) {
					display_inventory(inventory,*nb_items);
					do{
						printf("Which item do you want to delete ? Give me its number: \n");
						scanf("%d", &nb);
						if(nb > *nb_items){
							printf("Entry error\n");
						}
					} while(nb >= *nb_items);
					delete_item_in_inventory(inventory,nb_items,inventory[nb]);
					printf("Deleted! Check your new inventory!\n");
					display_inventory(inventory,*nb_items);
				}
			} while (choice != 3 && *nb_items > 0);
		}

	else {
		printf("Your inventory is empty... there is not much to do!\n");
	}

}

/* Replaces one item (item1) with another (item2) in the inventory */
void swap_items (item_t * inventory, int nb_items, item_t * item1, item_t * item2){
	int i, j, cpt = 0;

	/* Find out whether the item that the player wants to swap exists in the inventory */
	for(i = 0; (i < nb_items) && strcmp(inventory[i].name, item1->name); i++);

	if(i >= nb_items){
		printf("%s isn't in your inventory.\n",item1->name);
	}
	else{
		item2->equipped = 1;
		inventory[i] = *item2;
		for(j = 0; j < nb_items; j++){
			if(!strcmp(inventory[j].name,item1->name) && (i != j)){
				cpt++;
			}
		}
		if(!cpt){
			item1->equipped = 0;
		}
		printf("%s has been replaced by %s!\n",item1->name, item2->name);
	}
}

/* Adds an item to the inventory */
void add_item_to_inventory(item_t * inventory, int * nb_items, item_t item){
	int answer, nb;

	if(*nb_items < 10){
		item.equipped = 1;
		inventory[*nb_items] = item;
		(*nb_items)++;
		printf("Item added to your inventory!\n");
	}
	else {
		printf("Would you like to keep this item and give up one of your inventory? (YES: 1, NO: 0)\n");
		scanf("%d",&answer);
		if(answer){
			display_inventory(inventory,*nb_items);
			printf("Which item do you want to exchange ? ");
			scanf("%d", &nb);
			swap_items(inventory, *nb_items, &inventory[nb], &item);
		}
	}
}

int main(){
	/* DECLARATION INVENTORY */
	item_t inventory[10]; // inventory - 10 items maximum (version 1)
	int nb_items = 0;

	/* DECLARATION AND CHARACTERISTICS OF THE ITEMS */

	/* WEAPONS */
	// lance
	item_t lance;
	strcpy(lance.name, "lance");
	lance.type = weapon;
	lance.attack = 0;
	lance.defense = 0;
	lance.equipped = 0;

	// pistol
	item_t pistol;
	strcpy(pistol.name, "pistol");
	pistol.type = weapon;
	pistol.attack = 0;
	pistol.defense = 0;
	pistol.equipped = 0;

	// shotgun
	item_t shotgun;
	strcpy(shotgun.name, "shotgun");
	shotgun.type = weapon;
	shotgun.attack = 0;
	shotgun.defense = 0;
	shotgun.equipped = 0;

	// knife
	item_t knife;
	strcpy(knife.name, "knife");
	knife.type = weapon;
	knife.attack = 0;
	knife.defense = 0;
	knife.equipped = 0;

	// bow + arrows
	item_t bow_arrows;
	strcpy(bow_arrows.name,"bow_arrows");
	bow_arrows.type = weapon;
	bow_arrows.attack = 0;
	bow_arrows.defense = 0;
	bow_arrows.equipped = 0;

	// baseball bat
	item_t baseball_bat;
	strcpy(baseball_bat.name,"baseball_bat");
	baseball_bat.type = weapon;
	baseball_bat.attack = 0;
	baseball_bat.defense = 0;
	baseball_bat.equipped = 0;

	// bulletproof_vest
	item_t bulletproof_vest;
	strcpy(bulletproof_vest.name,"bulletproof_vest");
	bulletproof_vest.type = armor;
	bulletproof_vest.attack = 0;
	bulletproof_vest.defense = 0;
	bulletproof_vest.equipped = 0;

	// helmet
	item_t helmet;
	strcpy(helmet.name,"helmet");
	helmet.type = armor;
	helmet.attack = 0;
	helmet.defense = 0;
	helmet.equipped = 0;

	/* MISC */
	// fishing_rod
	item_t fishing_rod;
	strcpy(fishing_rod.name,"fishing_rod");
	fishing_rod.type = misc;
	fishing_rod.attack = 0;
	fishing_rod.defense = 0;
	fishing_rod.equipped = 0;

	// medical_kit
	item_t medical_kit;
	strcpy(medical_kit.name,"medical_kit");
	medical_kit.type = misc;
	medical_kit.attack = 0;
	medical_kit.defense = 0;
	medical_kit.equipped = 0;

	// rope
	item_t rope;
	strcpy(rope.name,"rope");
	rope.type = misc;
	rope.attack = 0;
	rope.defense = 0;
	rope.equipped = 0;

	// walking stick
	item_t walking_stick;
	strcpy(walking_stick.name,"walking_stick");
	walking_stick.type = misc;
	walking_stick.attack = 0;
	walking_stick.defense = 0;
	walking_stick.equipped = 0;

	/* SIMULATIONS TO TEST FUNCTIONS */

	printf("Beginning of your adventure!\n");
	display_inventory(inventory, nb_items);
	printf("\n");

	printf("Oh! Here is a ROPE, let's add it to your inventory!\n");
	add_item_to_inventory(inventory,&nb_items,rope);

	printf("Oh! Here is a HELMET, let's add it to your inventory!\n");
	add_item_to_inventory(inventory,&nb_items,helmet);

	printf("============== CHECKPOINT 1 ================ \n");
	menu_inventory(inventory,&nb_items);

 	swap_items(inventory, nb_items, &shotgun, &rope);
	swap_items(inventory, nb_items, &helmet, &lance);

	printf("============== CHECKPOINT 2 ================ \n");
	menu_inventory(inventory,&nb_items);

	return EXIT_SUCCESS;
}
