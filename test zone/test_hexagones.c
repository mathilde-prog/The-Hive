#include <stdio.h>
#include <stdlib.h>

#define N 50
#define Cote 5


void init_grille(int grille[N][N]){
  int i,j;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      grille[i][j]=0;
}

void afficher_map(int grille[N][N]){
  int i,j;
  printf("\n");
  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
      if (grille[i][j])
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}


void placer_hexa(int grille[N][N], int haut_x, int haut_y){
  int i,j;
  //lignes du haut et du bas de l'hexagone
  for (i = 0; i<Cote; i++){
    grille[haut_x][haut_y+i] = 1;
    grille[haut_x+(2*Cote-1)-1][haut_y+i] = 1;
  }
  //les 4 cotes restants qui vont en diagonales
  j = 0;
  for (i = 0; i <= (Cote-1); i++){
    grille[haut_x+i][haut_y-j] = 1;
    grille[haut_x+i][haut_y+(Cote-1)+j] = 1;
    j++;
  }
  j = 0;
  for (i =0; i<= (Cote-1); i++){
    grille[haut_x+2*(Cote-1)-i][haut_y-j] = 1;
    grille[haut_x+2*(Cote-1)-i][haut_y+(Cote-1)+j] = 1;
    j++;
  }
}

int valide(int haut_x, int haut_y){
  if (haut_x >= 0 && haut_x < N-(Cote+2) && haut_y >= (Cote-1) && haut_y <= N-(Cote-1))
    return 1;
  return 0;
}


int main (){
  int grille[N][N];
  int i,j;
  int haut_x = 0, haut_y = Cote;
  int hx2 = haut_x, hy2 = haut_y;
  init_grille(grille);
  if (valide(haut_x,haut_y)){
    placer_hexa(grille, haut_x, haut_y);
  }
  haut_x += 2*(Cote-1);
  if (valide(haut_x,haut_y))
    placer_hexa(grille, haut_x, haut_y);

  hx2 += Cote-1;
  hy2 += 2*(Cote-1);
  if (valide(hx2, hy2))
    placer_hexa(grille, hx2, hy2);
  haut_x += 2*(Cote-1);
  if (valide(haut_x,haut_y))
    placer_hexa(grille, haut_x, haut_y);
  hx2 += 2*(Cote-1);
  if (valide(hx2, hy2))
    placer_hexa(grille, hx2, hy2);

  system("clear");
  afficher_map(grille);
}
