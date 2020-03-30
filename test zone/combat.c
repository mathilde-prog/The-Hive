#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct perso_s {
  int pv; // Points de vie
  int pe; // Points d'énergie
  int pa; // Points d'action
	int posX;
	int posY;
	int turns; //nb tours

  skill_t competence; // Compétence spéciale

  item_t inventory[INVENTORY_CAPACITY];
  int nb_items_inventory;

  item_t * left_hand; 	/* Pointeur sur item main gauche */
  item_t * right_hand; 	/* Pointeur sur item main droite */
  item_t * body; 				/* Pointeur sur item corps */
  item_t * head;				/* Pointeur sur item tête */

} perso_t;

typedef struct stat_s{ // structure to manage battlefield
	int posA; // position of player
	int posB; // position of bot
	int coverA;
	int coverB;
	int distance; // distance between A and B;
}stat_t;

typedef struct item_s{
	char name[10];
	int attack;
	int type;
}item_t;

void swap(int a, int b, item_t inventory[10]){
	item_t x=inventory[a];
	item_t y=inventory[b];
	item_t z=x;
	x=y;
	y=z;
}

void main(){
  int i;

item_t tab[5];
strcpy(tab[0].name, "PEPEHANDS");
tab[0].attack=3;
tab[0].type=3;


strcpy(tab[1].name, "PEPECLAP");
tab[1].attack=1;
tab[1].type=1;

printf("\nName = %s, ", tab[0].name);
printf("Attack = %d, ", tab[0].attack);
printf("Type = %d\n", tab[0].type);

printf("\nName = %s, ", tab[1].name);
printf("Attack = %d, ", tab[1].attack);
printf("Type = %d\n", tab[1].type);


swap(0,1,tab);
printf("\nName = %s, ", tab[0].name);
printf("Attack = %d, ", tab[0].attack);
printf("Type = %d\n", tab[0].type);
printf("\nName = %s, ", tab[1].name);
printf("Attack = %d, ", tab[1].attack);
printf("Type = %d\n", tab[1].type);


}

void turn_npc(npc_t mr, stat_t field){
	field.coverB=0;
	if(mr.weapon=shotgun){
			if(distance > 3){
				field.posB--;
			}else if(field.distance == 1){
				if(rng(60) || field.posB > 7){
					field.posB++;
				}else if(rng(30)){
					field.coverB=1;
				}else{
					damage_calculator(&enemy, &player); // TO CODE
				}
			}else if(field.distance == 2){
				if(mr.hp)
			}
		}
	}else if(mr.weapon=pistol){

	}else{

	}
}
