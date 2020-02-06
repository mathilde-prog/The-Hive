#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
