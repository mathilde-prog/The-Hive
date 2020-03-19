#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

void clrscr(){ // fonction pour clear l'output de terminal
    system("clear");
}

int range(int a,int b){ // generates random number in range
  return (rand()%(b-a+1))+a;
}

int rng(int prob){ // returns 0 or 1 with a given chance
  return (rand()%100)<prob;
}

void init_border(int map[D][D]){ //spawns border of the map
  int i;
  int low=1;
  int high=4;
  int t = range(low,high);
  if(t==1){
    for(i=0; i<D;i++){
      map[D-1][i]=montagne;
      map[i][0]=frontiere;
      map[0][i]=mer;
      map[i][D-1]=wasteland;
    }
  }else if(t==2){
    for(i=0; i<D;i++){
      map[i][0]=montagne;
      map[0][i]=frontiere;
      map[i][D-1]=mer;
      map[D-1][i]=wasteland;
    }
  }else if(t==3){
    for(i=0; i<D;i++){
      map[0][i]=montagne;
      map[i][D-1]=frontiere;
      map[D-1][i]=mer;
      map[i][0]=wasteland;
    }
  }else if(t==4){
    for(i=0; i<D;i++){
      map[i][D-1]=montagne;
      map[D-1][i]=frontiere;
      map[i][0]=mer;
      map[0][i]=wasteland;
    }
  }
}

int bordercross(int i, int j, int map[D][D]){ // fonction to prevent favellas spawning on border
  return (map[i-1][j]>=9 || map[i-1][j-1]>=9 || map[i-1][j+1]>=9 || map[i][j-1]>=9 || map[i][j+1]>=9 || map[i+1][j-1]>=9 || map[i+1][j]>=9 || map[i+1][j+1]>=9);
}

void topup(int map[D][D]){ // spawns fixed amount of essential hexes on random coordinates
  int s,i,j;
  int low=1, high=13;

  i = range(low+1,high-1);
  j = range(low+1,high-1);
  map[i][j]=market;
  map[i-1][j]=favella;
  map[i-1][j-1]=favella;
  map[i-1][j+1]=favella;
  map[i][j-1]=favella;
  map[i][j+1]=favella;
  map[i+1][j-1]=favella;
  map[i+1][j]=favella;
  map[i+1][j+1]=favella;

  for(s=3; s!=0;s--){
    i = range(low,high);
    j = range(low,high);
    map[i][j]=ville;
  }

  while(map[i][j]!=prairie){
    i = range(low,high);
    j = range(low,high);
  }
  map[i][j]=camp_mil;

  while(map[i][j]!=prairie){
    i = range(low,high);
    j = range(low,high);
  }
  map[i][j]=camp_ban;

  for(s=5;s!=0;s--){
    while(map[i][j]!=prairie){
      i = range(low,high);
      j = range(low,high);
    }
    map[i][j]=lac;
  }
}

int spawntype(int l, int c, int map[D][D]){ // returns hex type that must be spawned on current matrix position
  int tab[3]={0}; // number of each type of hex around the current one
  int prob[3]={0}; // probability of each type of hex spawning (1 or 0)
  int t=1;

  for(int i=1; i<=3;i++){
    if(c%2==1){
      if(map[l][c-1]==i){
        tab[i-1]=i;
      }
      if(map[l][c+1]==i){
        tab[i-1]=i;
      }
      if(map[l][c]==i){
        tab[i-1]=i;
      }
      if(map[l-1][c-1]==i){
        tab[i-1]=i;
      }
      if(map[l-1][c]==i){
        tab[i-1]=i;
      }
      if(map[l-1][c+1]==i){
        tab[i-1]=i;
      }
      if(map[l+1][c]==i){
        tab[i-1]=i;
      }
    }else{
      if(map[l][c]==i){
        tab[i-1]=i;
      }
      if(map[l-1][c]==i){
        tab[i-1]=i;
      }
      if(map[l+1][c]==i){
        tab[i-1]=i;
      }
      if(map[l][c+1]==i){
        tab[i-1]=i;
      }
      if(map[l][c-1]==i){
        tab[i-1]=i;
      }
      if(map[l+1][c-1]==i){
        tab[i-1]=i;
      }
      if(map[l+1][c+1]==i){
        tab[i-1]=i;
      }
    }
  }
  prob[0]=rng(20+(10*tab[0]));
  prob[1]=rng(10+tab[1]);
  prob[2]=rng(7*tab[2]);

  for(int i=0;i<4;i++){
    if(prob[i]==1){
      t=i+1; // priority of spawning -> hill,forest,village,city
    }
  }
  return t;
}

void nextgen(int map[D][D]){ // generates additional hexes on the map with different chance
  int i,j,c;
  for(c=0;c<3;c++){
    for(i=1;i<D-1;i++){
      for(j=1;j<D-1;j++){
        if(map[i][j]==prairie){
          map[i][j]=spawntype(i,j,map);
        }
      }
    }
  }
}

int coordonnees_valides(int l, int c){
  return ((l >= 0 && l < D) && (c >= 0 && c < D));
}

void portable_switch(int i, int j, int map[D][D]){ // FONCTION QUI PRINT LE CODE DE LA CELLULE, CREE POUR EVITER DE REFAIRE LES SWITCHS DANS DIFFERENTS FONCTIONS D'AFFICHAGE
  if(coordonnees_valides(i,j)){
    switch(map[i][j]){
      case 1: printf(" PR "); break;
      case 2: printf(" FR "); break;
      case 3: printf(" VL "); break;
      case 4: printf(" LC "); break;
      case 5: printf(" CM "); break;
      case 6: printf(" CB "); break;
      case 7: printf(" MK "); break;
      case 8: printf(" FV "); break;
      case 9: printf(" MT "); break;
      case 10: printf(" BD "); break;
      case 11: printf(" SE "); break;
      case 12: printf(" WT "); break;
      default: printf("    "); break;
    }
  }
  else {
    printf("    ");
  }
}

void display_TEXT(int l, int c, int map[D][D]){ // AFFICHE LA MAP EN VERSION TEXT AVEC LA LEGENDE
  int i,j,nb;

  for(i=0; i<D; i++){
    for(j=0; j<D; j++){
      printf("+----");
    }
    printf("+\n");
    for(j=0; j<D; j++){
      if(i==l && j==c){
        printf("|");
        printf("\033[1;32m");
        printf(" JR ");
        printf("\033[0m");
      }else{
        printf("|");
        portable_switch(i,j,map);
      }
    }
    if(i==0){
      printf("|     LEGENDE:\n");
    }else if(i==1){
      printf("|     JR - Joueur\n");
    }else if(i==2){
      printf("|     PR - Prairie\n");
    }else if(i==3){
      printf("|     FR - Foret\n");
    }else if(i==4){
      printf("|     VL - Ville\n");
    }else if(i==5){
      printf("|     LC - Lac\n");
    }else if(i==6){
      printf("|     CM - Camp militaire\n");
    }else if(i==7){
      printf("|     CB - Camp de bandits\n");
    }else if(i==8){
      printf("|     MK - Marchand\n");
    }else if(i==9){
      printf("|     FV - Favella\n");
    }else if(i==10){
      printf("|     MT - Montagne\n");
    }else if(i==11){
      printf("|     BD - Frontiere\n");
    }else if(i==12){
      printf("|     SE - Mer\n");
    }else if(i==13){
      printf("|     WT - Wasteland\n");
    }else{
      //prairie=1,foret,ville,lac,camp_mil,camp_ban,market,favella,montagne,frontiere,mer,wasteland
      printf("|\n");
    }
  }
  for(i=0; i<D; i++){
    printf("+----");
  }
  printf("+\n");

  do {
    printf("\nBack to the menu (1) : ");
    scanf("%d",&nb);
    if(nb != 1){
      printf("Type 1 to return to the inventory menu\n");
    }
  } while (nb != 1);
}

void init_base(int map[D][D]){
  int i,j;
  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      map[i][j]=prairie;
    }
  }
}

void count(const int map[D][D]){ // COMPTE LE NOMBRE D'OCCURENCE DE CHAQUE TYPE DE CELLULE
  int c=0,f=0,h=0,cb=0,cm=0,mr=0,fv=0;
  for(int i=0; i<D;i++){
    for(int j=0; j<D;j++){
      if(map[i][j]==ville){
        c++;
      }if(map[i][j]==foret){
        f++;
      }if(map[i][j]==prairie){
        h++;
      }if(map[i][j]==camp_ban){
        cb++;
      }if(map[i][j]==camp_mil){
        cm++;
      }if(map[i][j]==market){
        mr++;
      }if(map[i][j]==favella){
        fv++;
      }
    }
  }
  printf("\nCity: %d\nForest: %d\nHills: %d\nBandit camp: %d\nMilitary camp: %d\nMarket: %d\nFavella: %d\n",c,f,h,cb,cm,mr,fv);
}

void display_grid(const int map[D][D]){ // AFFICHE LA MAP COMPLETE AVEC LA LEGENDE
  int i,j;
  clrscr();
  for(i=0; i<D; i++){
    for(j=0; j<D; j++){
      printf("+-------");
    }
    printf("+\n");
    for(j=0; j<D; j++){
      printf("|  %2d   ",map[i][j]);
    }
    if(i==0){
      printf("|     LEGENDE:\n");
    }else if(i==1){
      printf("|     X - Joueur\n");
    }else if(i==1){
      printf("|     PR - Prairie\n");
    }else if(i==2){
      printf("|     VL - Ville\n");
    }else if(i==3){
      printf("|     FR - Foret\n");
    }else if(i==5){
      printf("|     LC - Lac:\n");
    }else if(i==6){
      printf("|     CM - Camp militaire\n");
    }else if(i==7){
      printf("|     CB - Camp de bandits\n");
    }else if(i==8){
      printf("|     GR - Grotte\n");
    }else if(i==9){
      printf("|     MT - Montagne\n");
    }else if(i==10){
      printf("|     BD - Frontiere\n");
    }else if(i==11){
      printf("|     SE - Mer\n");
    }else if(i==12){
      printf("|     WT - Wasteland\n");
    }else{
      printf("|\n");
    }
  }
  for(i=0; i<D; i++){
    printf("+-------");
  }
  printf("+\n");
}

void map_init(int map[D][D]){
  init_base(map);
  init_border(map);
  topup(map);
  nextgen(map);
}
