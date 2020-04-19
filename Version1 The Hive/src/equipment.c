#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file equipment.c
 * \brief Gestion de l'équipement du joueur
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void display_equipment_player(perso_t player)
 * \brief Affiche l'équipement du joueur
 * \details Si la tête, la main gauche, la main droite ou le corps du joueur sont équipés, indique avec quels items en précisant leurs positions dans l'inventaire.
 * \param perso_t player
 * \return Rien
*/
void display_equipment_player(perso_t player){
	printf("=============== EQUIPEMENT ================\n");

	printf("Tête : ");
	(player.head != NULL) ? (printf("%s\t\t(N°%2d)\n", player.head->name, player.head->index)) : (printf("pas d'équipement\n"));

	printf("Main gauche : ");
	(player.left_hand != NULL) ? (printf("%s\t(N°%2d)\n", player.left_hand->name, player.left_hand->index)) : (printf("pas d'équipement\n"));

	printf("Main droite : ");
	(player.right_hand != NULL) ? (printf("%s\t(N°%2d)\n", player.right_hand->name, player.right_hand->index)) : (printf("pas d'équipement\n"));

	printf("Corps : ");
	(player.body != NULL) ? (printf("%s\t(N°%2d)\n", player.body->name, player.body->index)) : (printf("pas d'équipement\n"));

	printf("==========================================\n\n");
}

/**
 * \fn int is_equipped(perso_t player, item_t item)
 * \brief Indique si le joueur est équipé de l'item passé en paramètre
 * \param perso_t player
 * \param item_t item
 * \return Un \a int : si le joueur n'est pas équipé de l'item retourne 0 (NOT_EQUIPPED), sinon retourne où l'item est équipé sur le joueur (LEFT_HAND = 1, RIGHT_HAND = 2, BODY = 3, HEAD = 4)
*/

/*	is_equipped : - indicates if the player is equipped with the item passed in parameter.
	 							 	- if the player is equipped with the item, return where it is equipped (LEFT_HAND = 1, RIGHT_HAND = 2, BODY = 3, HEAD = 4)(cf. structure.h)
								 	- if the player isn't equipped with the item, return NOT_EQUIPPED = 0 (cf. structure.h)
*/
int is_equipped(perso_t player, item_t item){
	/* On commence par vérifier si l'item passé en paramètre est équipable.
		 Si oui (hand, body ou head) :
		 		Si la zone où l'item est équipable est équipée de cet item (on vérifie par l'index), on retourne LEFT_HAND (1), RIGHT_HAND(2), BODY(3), HEAD(4) selon le cas correspondant.
		 		Si la zone où l'item est équipable N'EST PAS équipée de cet item, on retourne NOT_EQUIPPED (0)
		 Si non (none) : retourne NOT_EQUIPPED (0)
	*/
	switch(item.equipable){
		case none : return NOT_EQUIPPED;
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

/**
 * \fn void swap_equipment_player(perso_t * player, item_t item)
 * \brief Echange l'item passé en paramètre avec un item choisi par le joueur figurant dans son équipement
 * \details Cette fonction est appelée lorsque le joueur souhaite s'équiper d'un item sur une zone de son corps déjà équipée.
 * \param perso_t * player
 * \param item_t item
 * \return Rien
*/

/*	swap_equipment_player: exchange of items on the player's equipment */
void swap_equipment_player(perso_t * player, item_t item){
	int num = 0; // variable pour le choix du joueur

	printf("Si vous souhaitez porter cet équipement, vous devez échanger %s avec un autre item\n",item.name);

	switch(item.equipable){
		case hand: 	printf("1. %s (main gauche)\n",player->left_hand->name);
								printf("2. %s (main droite)\n",player->right_hand->name);
								printf("Annuler : -1\n");
								do{
									printf("Avec quel item souhaitez-vous échanger %s ? N°", item.name);
									scanf("%d",&num);
									if((num != -1) && (num < 1 || num > 2)){
										printf("Valeur incorrecte. Veuillez ressaisir.\n");
									}
								} while((num != -1) && (num < 1 || num > 2));

								if(num != -1){
									if(num == 1){
										player->left_hand = &player->inventory[item.index];
									}
									else if (num == 2){
										player->right_hand = &player->inventory[item.index];
									}
									printf("Vous êtes maintenant équipé de %s.\n", item.name);
								}
								break;
		case body:	do {
									printf("Êtes-vous sûr de vouloir échanger %s avec %s ? (Oui = 1, Non = 0)",player->body->name,item.name);
		 							scanf("%d", &num);
									if(num < 0 || num > 1){
										printf("Valeur incorrecte. Veuillez ressaisir.\n");
									}
								} while (num < 0 || num > 1);

								if(num){
									player->body = &player->inventory[item.index];
									printf("Vous êtes maintenant équipé de %s.\n", item.name);
								}
								break;
		case head: do {
									printf("Êtes-vous sûr de vouloir échanger %s avec %s ? (Oui = 1, Non = 0)",player->head->name,item.name);
		 							scanf("%d", &num);
									if(num < 0 || num > 1){
										printf("Valeur incorrecte. Veuillez ressaisir.\n");
									}
								} while (num < 0 || num > 1);

								if(num){
									player->head = &player->inventory[item.index];
									printf("Vous êtes maintenant équipé de %s.\n", item.name);
								}
								break;
		default: break;
	}
}

/**
 * \fn void equip_player(perso_t * player)
 * \brief Equipe le joueur, au bon endroit, avec un item de son inventaire qu'il choisit. L'item doit être équipable.
 * \param perso_t * player
 * \return Rien
*/
/*	equip_player: equip the player with an item (which must be equippable) that he has in his inventory. Equip it in the right place. */
void equip_player(perso_t * player){
	int num; // variable pour le choix du joueur

	// vérifie si item(s) dans l'inventaire pour équiper le joueur
	if(player->nb_items_inventory != 0){
		display_inventory(*player); // affichage de l'inventaire pour permettre au joueur de faire son choix
		do {
			printf("De quel item souhaitez-vous vous équiper ? N°");
			scanf("%d",&num);
			if(num > player->nb_items_inventory){
				printf("Valeur incorrecte... Cet item ne figure pas dans votre inventaire!\n");
			}
		} while(num > player->nb_items_inventory);

		// si l'item n'est pas déjà équipé
		if(!is_equipped(*player,player->inventory[num])){
			switch(player->inventory[num].equipable){
				case none : printf("Vous ne pouvez pas vous équiper de cet item!\n"); break;
				case hand :	if(player->left_hand == NULL){
											player->left_hand = &player->inventory[num];
											printf("Vous êtes maintenant équipé de %s.\n", player->inventory[num].name);
										}
										else if (player->right_hand == NULL){
											player->right_hand = &player->inventory[num];
											printf("Vous êtes maintenant équipé de %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]); // Joueur déjà équipé dans cette zone, on lui propose d'échanger l'item porté avec celui choisi
										}
										break;
				case body : if(player->body == NULL){
											player->body = &player->inventory[num];
											printf("Vous êtes maintenant équipé de %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]);
										}
										break;
				case head : if(player->head == NULL){
											player->head = &player->inventory[num];
											printf("Vous êtes maintenant équipé de %s.\n", player->inventory[num].name);
										}
										else {
											swap_equipment_player(player,player->inventory[num]);
										}
										break;
				default : break;
			}

		}
		else {
			printf("Vous êtes déjà équipé de %s!\n\n",player->inventory[num].name);
		}
	}
	else {
		printf("Vous n'avez aucun item dans votre inventaire. Donc, rien pour vous équiper!\n");
	}
}

/**
 * \fn void remove_equipment_player(perso_t * player)
 * \brief Retire un item choisi par le joueur de son équipement
 * \param perso_t * player
 * \return Rien
*/
/*	remove_equipment_player: removes an item from the player's equipment */
void remove_equipment_player(perso_t * player){
	int num; // variable pour le choix du joueur

	do{
		printf("\nQuel équipement souhaitez-vous retirer ? (-1 pour annuler) N°");
		scanf("%d",&num);
		if(!is_equipped(*player,player->inventory[num]) && num != -1){
			printf("Valeur incorrecte... Vous n'êtes pas équipé de cet item!\n");
		}
	} while(!is_equipped(*player,player->inventory[num]) && num != -1);

	if(num != -1){
		switch(is_equipped(*player,player->inventory[num])){
			case LEFT_HAND: player->left_hand = NULL; break;
			case RIGHT_HAND: player->right_hand = NULL; break;
			case BODY: player->body = NULL; break;
			case HEAD: player->head = NULL; break;
			default: break;
		}
		printf("%s a été retiré de votre équipement.\n",player->inventory[num].name);
		sleep(2);
	}
}

/**
 * \fn void manage_equipment(perso_t * player)
 * \brief Fonction centrale du fichier equipment.c permettant au joueur de gérer son équipement
 * \details Menu équipement : Possibilité pour le joueur de s'équiper d'un item de son inventaire, de retirer un item de son équipement.
 * \param perso_t * player
 * \return Rien
*/
/* manage_equipment: equipment menu */
void manage_equipment(perso_t * player){
	int choise; // variable pour le choix du joueur

	jump:
	display_equipment_player(* player);
	printf("Que souhaitez-vous faire ?\n");
	do {
		printf("1. S'équiper d'un item de votre inventaire\n");
		printf("2. Retirer un item de votre équipement\n");
		printf("Quitter gestion équipement: -1\n\n");
		printf("N°");
		scanf("%d",&choise);
		if((choise != -1) && (choise < 1 || choise > 2)){
			printf("Valeur incorrecte. Veuillez ressaisir.\n");
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
