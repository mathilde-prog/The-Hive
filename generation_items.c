#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"inventory.h"

#define D 15
#define NB_ITEMS 17
#define NB_CATEG 3
#define ITEMS_MAX 10

typedef enum{prairie=1,foret,ville,lac,camp_mil,camp_ban,market,favella,montagne,frontiere,mer,wasteland}hex_t;

typedef enum{nature=0,urbain,militaire}categ_hexa;

//Revoie le nombre de d'items qu'on peut trouver sur l'hexagone
int nb_items_hexagone(int x, int y, int map[D][D], int items_hexagone[3][NB_ITEMS]){
    int nb_item_possible=0, i=0;
    categ_hexa categ;
    hex_t hexagone;

    //??? Création fonction vérifiant si les coordonnées sont OK ?

    hexagone = map[x][y];
    switch(hexagone){
        case 1 : categ = 0; break;   //prairie
        case 2 : categ = 0; break;   //foret
        case 3 : categ = 1; break;   //ville
        case 4 : categ = 0; break;   //lac
        case 5 : categ = 2; break;   //camp mil
        /* -> Absence de l'hexagone camp bandits car ils attaquent immédiatement le joueur */
        case 7 : categ = 1; break;   //market
        case 8 : categ = 1; break;   //favella
        case 9 : categ = 0; break;   //montagne
        /* -> Absence de l'hexagone frontière */
        case 11 : categ = 0; break;  //mer
        case 12 : categ = 0; break;  //wasteland
        default : return 0;
    }
    /* Nombre d'items que l'on peut trouver dans la zone */
    for (i=0; i<NB_ITEMS; i++){
        if (items_hexagone[categ][i]!=0)
            nb_item_possible++;
    }
    return nb_item_possible;
}

int rng(int prob){ // returns 0 or 1 with a given chance
  int tab[100]={0};
  int i,r;
  if(prob>100){
    prob=100;
  }
  for(i=0;i<prob;i++){
    tab[i]=1;
  }
  r=rand()%100;
  return tab[r];
}

//Génère les items de façon aléatoires
void items_generer(int item_hexa[NB_CATEG][NB_ITEMS], categ_hexa categ){
    int i, r, cpt=1;
    char tab_items[17]={'p','l','g','k','a','b','v','h','f','m','r','w','c','f','p','n','d'};

    //A revoir peut-etre random et non i++
    for(i=0; (i<NB_ITEMS)&&(cpt<=ITEMS_MAX); i++){
        if(item_hexa[categ][i]!=0){
            r = rng(item_hexa[categ][i]);
            if (r==1){
                printf("Item %d : %c\n", cpt, tab_items[i]);
                cpt++;
            }
        }
    }
    if (cpt!=0)
        printf("Felicitations, vous venez de trouver %d items !\n", cpt);
    else
        printf("Désole, il n'y a rien à recuperer ici...");
}


int main(){
    /* Tableau représentant pour chaque item le pourcentage d'apparition dans le type d'hexagone correspondant.
    Ordre des items : pistol, lance, shotgun, knife, bow_arrows, baseball_bat, bulletproof_vest, helmet, fishing_rod,
    medical_kit, rope, walking_stick, map, fruits, fish, can_food, drink */
    int item_hexa[NB_CATEG][NB_ITEMS] = {{0,50,0,0,30,0,0,0,0,0,0,70,0,75,50,0,0},      //Type Nature
                                  {50,0,40,70,0,40,35,40,40,70,60,30,75,90,60,85,90},   //Type Urbain
                                  {90,0,75,60,0,50,85,75,0,80,60,0,70,50,30,75,50}};    //Type Militaire

    int x=2, y=3, x1=10, y1=5, nb;
    int map[D][D];

    map[x][y] = prairie;
    map[x1][y1] = camp_mil;
    nb = nb_items_hexagone(x, y, map, item_hexa);
    if (nb == 0)
        printf ("ERREUR : nb_items_hexagones = 0");
    else {
        printf("Prairie : %d items possibles (5)\n", nb);
    }
    nb = nb_items_hexagone(x1, y1, map, item_hexa);
    if (nb == 0)
        printf ("ERREUR : nb_items_hexagones = 0");
    else {
        printf("Camp bandits : %d items possibles (13)\n", nb);
    }

    if(nb == 5){  //Type Nature
        items_generer(item_hexa, nature);
    }
    else{
        if(nb == 15){  //Type Urbain
            items_generer(item_hexa, urbain);
        }
        else{  //Type Militaire
            items_generer(item_hexa, militaire);
        }
    }
    display_inventory(); //A COMPLETER
    return 0;
}
