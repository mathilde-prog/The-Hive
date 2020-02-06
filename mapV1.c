#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
//ville | prairie | foret | lac | mer | montagne | abandoné(grottes...) | camp des bandits | bordures
//
#define D 15

typedef enum{prairie=1,foret,ville,lac,camp_mil,camp_ban,market,favella,montagne,frontiere,mer,wasteland}hex_t;

int range(int a,int b){ // generates random number in range
  return (rand()%(b-a+1))+a;
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
  int c,s,i,j,b;
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

void display_map(int map[D][D]){
  int i,j;

  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      if(map[i][j]>=10){
        printf("  %d ", map[i][j]);
      }else{
        printf("  %d  ", map[i][j]);
      }
    }
    printf("\n");
  }
}

void init_base(int map[D][D]){
  int i,j;
  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      map[i][j]=prairie;
    }
  }
}

void count(int map[D][D]){
  int c=0,v=0,f=0,h=0,cb=0,cm=0,mr=0,fv=0;
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

int main(){
  int map[D][D]={{0}};

  srand(time(NULL));
  init_base(map);
  init_border(map);
  topup(map);
  nextgen(map);
  display_map(map);
  count(map);
}
