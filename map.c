#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define D 10
#define H 1
#define F 2
#define V 3
#define C 4
#define M 5
#define B 6
#define O 7
#define W 8

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

void initBorder(int map[D][D]){ //spawns border of the map
  int i;
  int low=1;
  int high=4;
  int t = range(low,high);
  if(t==1){
    for(i=0; i<D;i++){
      map[D-1][i]=M;
      map[i][0]=B;
      map[0][i]=O;
      map[i][D-1]=W;
    }
  }else if(t==2){
    for(i=0; i<D;i++){
      map[i][0]=M;
      map[0][i]=B;
      map[i][D-1]=O;
      map[D-1][i]=W;
    }
  }else if(t==3){
    for(i=0; i<D;i++){
      map[0][i]=M;
      map[i][D-1]=B;
      map[D-1][i]=O;
      map[i][0]=W;
    }
  }else if(t==4){
    for(i=0; i<D;i++){
      map[i][D-1]=M;
      map[D-1][i]=B;
      map[i][0]=O;
      map[0][i]=W;
    }
  }
}

void initObj(int map[D][D]){ // spawns fixed amount of cities on random coordinates
  int c,s,i,j;
  int low=0;
  int high=9;

    for(i=1;i<D-1;i++){
      for(j=1;j<D-1;j++){
        if(rng(30)){
          map[i][j]=F;
        }
        if(rng(20)){
          map[i][j]=V;
        }
      }
    }

    if(D == 10){
      for(s=1; s!=0;s--){
        i = range(low,high);
        j = range(low,high);
        map[i][j]=C;
      }
    }else if(D == 25){
      for(s=3; s!=0;s--){
        i = range(low,high);
        j = range(low,high);
        map[i][j]=C;
      }
    }else if(D == 50){
      for(s=5; s!=0;s--){
        i = range(low,high);
        j = range(low,high);
        map[i][j]=C;
      }
    }
}


int spawntype(int l, int c, int map[D][D]){ // returns hex type that must be spawned on current matrix position
  int tab[4]={0}; // number of each type of hex around the current one
  int prob[4]={0}; // probability of each type of hex spawning (1 or 0)
  int t;

  for(int i=1; i<=4;i++){
    if(map[l][c]==i){
      tab[i-1]+=1;
    }
    if(map[l-1][c]==i){
      tab[i-1]+=1;
    }
    if(map[l-1][c+1]==i){
      tab[i-1]+=1;
    }
    if(map[l][c+1]==i){
      tab[i-1]+=1;
    }
    if(map[l+1][c+1]==i){
      tab[i-1]+=1;
    }
    if(map[l-1][c]==i){
      tab[i-1]+=1;
    }
    if(map[l-1][c-1]==i){
      tab[i-1]+=1;
    }
    if(map[l][c-1]==i){
      tab[i-1]+=1;
    }
    if(map[l+1][c-1]==i){
      tab[i-1]+=1;
    }
  }
  prob[0]=rng(20+(10*tab[0]));
  prob[1]=rng(30+tab[1]);
  prob[2]=rng(10+(5*tab[2]));
  prob[3]=rng(5+tab[3]);

  for(int i=0;i<4;i++){
    if(prob[i]==1){
      t=i+1; // priority of spawning -> hill,forest,village,city
      printf("\nT status: %d\n", t);
    }
  }
  return t;
}

void topup(int map[D][D]){ // generates additional hexes on the map with different chance
  int i,j;
  for(int c=0;c<5;c++){
    for(i=1;i<D-1;i++){
      for(j=1;j<D-1;j++){
        map[i][j]=spawntype(i,j,map);
      }
    }
  }
}

void displayMap(int map[D][D]){
  int i,j;

  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      printf(" %d ", map[i][j]);
    }
    printf("\n");
  }
}

void displayMapV(int map[D][D], wchar_t mapV[D][D]){
  int i,j;
  wchar_t mountain = 0x25ee;
  wchar_t border = 0x25a4;
  wchar_t hill = 0x25cf;
  wchar_t village = 0x2bc2;
  wchar_t city = 0x2bc4;
  wchar_t forest = 0x29f0;

  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      if(map[D][D]==1){
        printf(" %lc ", hill);
      }else if(map[D][D]==2){
        printf(" %lc ", forest);
      }else if(map[D][D]==3){
        printf(" %lc ", village);
      }else if(map[D][D]==4){
        printf(" %lc ", city);
      }else if(map[D][D]==5){
        printf(" %lc ", mountain);
      }else if(map[D][D]==6){
        printf(" %lc ", border);
      }
    }
    printf("\n");
  }
}

void initBase(int map[D][D]){
  int i,j;
  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      map[i][j]=1;
    }
  }
}

void count(int map[D][D]){
  int c=0,v=0,f=0,h=0;
  for(int i=0; i<D;i++){
    for(int j=0; j<D;j++){
      if(map[i][j]==4){
        c++;
      }if(map[i][j]==3){
        v++;
      }if(map[i][j]==2){
        f++;
      }if(map[i][j]==1){
        h++;
      }
    }
  }
  printf("\nNumber of city hex: %d\nNumber of village hex: %d\nNumber of forest hex: %d\nNumber of hill hex: %d\n", c,v,f,h);
}

int main(){
  setlocale(LC_CTYPE, "");
  wchar_t mapV[D][D]={{0}};
  int map[D][D]={{0}};
  srand(time(NULL));
  initBase(map);
  initBorder(map);
  displayMap(map);
  count(map);
  //displayMapV(map, mapV);
}
