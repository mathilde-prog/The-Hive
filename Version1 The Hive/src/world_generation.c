#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

/**
 * \file world_generation.c
 * \brief Génération de la carte (Moustapha --> COMPLETER ET VERIFIER DOCUMENTATION DES FONCTIONS)
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/


/**
 * \fn void init_border(cell_t map[D][D])
 * \brief Initialise les contours de la map
 * \param cell_t map[D][D]
 * \return Rien
*/
void init_border(cell_t map[D][D]){ // initiates border of the map
  int i;
  for(i=0; i<D;i++){
    map[D-1][i].type=mer;
    map[D-1][i].categ=nature;
  }
  for(i=0; i<D;i++){
    map[i][0].type=wasteland;
    map[i][0].categ=other;
  }
  for(i=0; i<D;i++){
    map[0][i].type=montagne;
    map[0][i].categ=nature;
  }
  for(i=0; i<D;i++){
    map[i][D-1].type=frontiere;
    map[i][D-1].categ=other;
  }
}


/**
 * \fn int bordercross(int i, int j, cell_t map[D][D])
 * \brief MOUSTAPHA
 * \param int i
 * \param int j
 * \param cell_t map[D][D]
 * \return Retourne un \a int : MOUSTAPHA
*/
int bordercross(int i, int j, cell_t map[D][D]){ // fonction to prevent favellas spawning on border
  return (map[i-1][j].type>=9 || map[i-1][j-1].type>=9 || map[i-1][j+1].type>=9 || map[i][j-1].type>=9 || map[i][j+1].type>=9 || map[i+1][j-1].type>=9 || map[i+1][j].type>=9 || map[i+1][j+1].type>=9);
}


/**
 * \fn void topup(cell_t map[D][D])
 * \brief MOUSTAPHA
 * \param cell_t map[D][D]
 * \return Rien
*/
void topup(cell_t map[D][D], int quest_map[6][2]){ // spawns fixed amount of essential hexes on random coordinates
  int s,i,j;
  int low=1, high=13;

  i = range(low+1,high-1);
  j = range(low+1,high-1);
  map[i][j].type=market;
  map[i][j].categ=urbain;
  map[i-1][j].type=favella;
  map[i-1][j].categ=urbain;
  map[i-1][j-1].type=favella;
  map[i-1][j-1].categ=urbain;
  map[i-1][j+1].type=favella;
  map[i-1][j+1].categ=urbain;
  map[i][j-1].type=favella;
  map[i][j-1].categ=urbain;
  map[i][j+1].type=favella;
  map[i][j+1].categ=urbain;
  map[i+1][j-1].type=favella;
  map[i+1][j-1].categ=urbain;
  map[i+1][j].type=favella;
  map[i+1][j].categ=urbain;
  map[i+1][j+1].type=favella;
  map[i+1][j+1].categ=urbain;

  for(s=3; s!=0;s--){
    i = range(low,high);
    j = range(low,high);
    map[i][j].type=ville;
    map[i][j].categ=urbain;
  }

  while(map[i][j].type != prairie){
    i = range(low,high);
    j = range(low,high);
  }
  map[i][j].type=camp_mil;
  map[i][j].categ=militaire;


  while(map[i][j].type!=prairie){
    i = range(low,high);
    j = range(low,high);
  }
  map[i][j].type=camp_ban;
  map[i][j].categ=other;
  quest_map[3][0]=i; // bandits
  quest_map[3][1]=j;
  map[i][j].quest_id=4;


  for(s=5;s!=0;s--){
    while(map[i][j].type!=prairie){
      i = range(low,high);
      j = range(low,high);
    }
    map[i][j].type=lac;
    map[i][j].categ=nature;
  }
}


/**
 * \fn int spawntype(int l, int c, cell_t map[D][D])
 * \brief MOUSTAPHA
 * \param int l
 * \param int c
 * \param cell_t map[D][D]
 * \return Retourne un \a int : MOUSTAPHA
*/
int spawntype(int l, int c, cell_t map[D][D]){ // returns hex type that must be spawned on current matrix position
  int tab[3]={0}; // number of each type of hex around the current one
  int prob[3]={0}; // probability of each type of hex spawning (1 or 0)
  int t=1;

  for(int i=1; i<=3;i++){
    if(c%2==1){
      if(map[l][c-1].type==i){
        tab[i-1]=i;
      }
      if(map[l][c+1].type==i){
        tab[i-1]=i;
      }
      if(map[l][c].type==i){
        tab[i-1]=i;
      }
      if(map[l-1][c-1].type==i){
        tab[i-1]=i;
      }
      if(map[l-1][c].type==i){
        tab[i-1]=i;
      }
      if(map[l-1][c+1].type==i){
        tab[i-1]=i;
      }
      if(map[l+1][c].type==i){
        tab[i-1]=i;
      }
    }else{
      if(map[l][c].type==i){
        tab[i-1]=i;
      }
      if(map[l-1][c].type==i){
        tab[i-1]=i;
      }
      if(map[l+1][c].type==i){
        tab[i-1]=i;
      }
      if(map[l][c+1].type==i){
        tab[i-1]=i;
      }
      if(map[l][c-1].type==i){
        tab[i-1]=i;
      }
      if(map[l+1][c-1].type==i){
        tab[i-1]=i;
      }
      if(map[l+1][c+1].type==i){
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


/**
 * \fn int categ_switch(int input)
 * \brief Donne la catégorie de l'hexagone passé en paramètre
 * \param int input
 * \return Retourne un \a int correspondant à la catégorie de l'hexagone
*/
int categ_switch(int input){ // returns hexagone category (urbain,nature, military, other)
    switch(input){
        case 1: return 1; break;
        case 2: return 1; break;
        case 3: return 2; break;
        case 4: return 1; break;
        case 5: return 3; break;
        case 6: return 0; break;
        case 7: return 2; break;
        case 8: return 2; break;
        case 9: return 1; break;
        case 10: return 0; break;
        case 11: return 1; break;
        case 12: return 0; break;
        default: return -1; break;
    }
}


/**
 * \fn void nextgen(cell_t map[D][D])
 * \brief MOUSTAPHA
 * \param cell_t map[D][D]
 * \return Rien
*/
void nextgen(cell_t map[D][D]){ // generates additional hexes on the map with different chance
  int i,j,c,tmp;
  for(c=0;c<3;c++){
    for(i=1;i<D-1;i++){
      for(j=1;j<D-1;j++){
        if(map[i][j].type==prairie){
          tmp=spawntype(i,j,map);
          map[i][j].type=tmp;
          map[i][j].categ=categ_switch(tmp);
        }
      }
    }
  }
}


/**
 * \fn int coordonnees_valides(int l, int c)
 * \brief Vérifie si les coordonées sont valides
 * \param int l
 * \param int c
 * \return Retourne un \a int : 1 si les coordonées sont valides, 0 si non
*/
int coordonnees_valides(int l, int c){
  return ((l >= 0 && l < D) && (c >= 0 && c < D));
}


/**
 * \fn void portable_switch(int i, int j, cell_t map[D][D])
 * \brief Affiche le code de la cellule
 \details
    Créé pour éviter de refaire le switch dans différentes fonctions d'affichage
 * \param int i
 * \param int j
 * \param cell_t map[D][D]
 * \return Rien
*/
void portable_switch(int i, int j, cell_t map[D][D]){ // FONCTION QUI PRINT LE CODE DE LA CELLULE, CREE POUR EVITER DE REFAIRE LES SWITCHS DANS DIFFERENTS FONCTIONS D'AFFICHAGE
  if(coordonnees_valides(i,j)){
    switch(map[i][j].type){
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


/**
 * \fn void display_TEXT(int l, int c, cell_t map[D][D])
 * \brief Affiche la map en version texte avec la légende
 * \param int l
 * \param int c
 * \param cell_t map[D][D]
 * \return Rien
*/
void display_TEXT(int l, int c, cell_t map[D][D]){ // AFFICHE LA MAP EN VERSION TEXT AVEC LA LEGENDE
  int i,j;

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
  printf("+\n\n");

  entree_pour_continuer();
}


/**
 * \fn void inti_base(cell_t map[D][D])
 * \brief Initialise la base de la map
 \details
    La map est initialisé par des hexagones de type prairie, donc catégorie "nature". Et les differents \a int de la structure cell_t map sont mis à 0.
 * \param cell_t map[D][D]
 * \return Rien
*/
void init_base(cell_t map[D][D]){
  int i,j;
  for(i=0;i<D; i++){
    for(j=0;j<D;j++){
      map[i][j].type=prairie;
      map[i][j].categ=nature;
      map[i][j].encounter=0;
      map[i][j].quest_id=0;
      map[i][j].scavenged=0;
    }
  }
}


/**
 * \fn void count(const cell_t map[D][D])
 * \brief Compte le nombre d'occurence de chaque type de cellule
 * \param const cell_t map[D][D]
 * \return Rien
*/
void count(const cell_t map[D][D]){ // COMPTE LE NOMBRE D'OCCURENCE DE CHAQUE TYPE DE CELLULE
  int c=0,f=0,h=0,cb=0,cm=0,mr=0,fv=0;
  for(int i=0; i<D;i++){
    for(int j=0; j<D;j++){
      if(map[i][j].type==ville){
        c++;
      }if(map[i][j].type==foret){
        f++;
      }if(map[i][j].type==prairie){
        h++;
      }if(map[i][j].type==camp_ban){
        cb++;
      }if(map[i][j].type==camp_mil){
        cm++;
      }if(map[i][j].type==market){
        mr++;
      }if(map[i][j].type==favella){
        fv++;
      }
    }
  }
  printf("\nCity: %d\nForest: %d\nHills: %d\nBandit camp: %d\nMilitary camp: %d\nMarket: %d\nFavella: %d\n",c,f,h,cb,cm,mr,fv);
}


/**
 * \fn void display_grid (const cell_t map[D][D])
 * \brief Affiche la map complète avec la légende
* \param const cell_t map[D][D]
 * \return Rien
*/
void display_grid(const cell_t map[D][D]){ // AFFICHE LA MAP COMPLETE AVEC LA LEGENDE
  int i,j;
  clrscr();
  for(i=0; i<D; i++){
    for(j=0; j<D; j++){
      printf("+-------");
    }
    printf("+\n");
    for(j=0; j<D; j++){
      printf("|  %2d   ",map[i][j].type);
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


/**
 * \fn void display_quest(int quest_map[6][2])
 * \brief MOUSTPAHA
 * \param int quest_map[6][2]
 * \return Rien
*/
void display_quest(int quest_map[6][2]){
  int i,j;
  for(i=0; i<6; i++){
    printf("Quest %d coordinates: ", i);
    for(j=0; j<2; j++){
      printf(" %d", quest_map[i][j]);
    }
    printf("\n");
  }
}


/**
 * \fn void encounter_init(cell_t map[D][D], perso_t player)
 * \brief MOUSTAPHA
 \details
    MOUSTAPHA
 * \param cell_t map[D][D]
 * \param perso_t player
 * \return Rien
*/
void encounter_init(cell_t map[D][D], perso_t player){
  int i,j;

  for(i=1;i<D-1;i++){
    for(j=1;j<D-1;j++){
      if(rng(10)){
        if((i != player.posY) || (j != player.posX)){ //Pour ne pas que le joueur commence la partie directement par un combat
          map[i][j].encounter=1;
        }
      }
    }
  }
}


/**
 * \fn void quest_init(cell_t map[D][D], int quest_map[6][2])
 * \brief Initialise les quêtes (id_quest) sur la map
 \details
    Les quêtes sont placés sur la map de façon aléaoires
 * \param cell_t map[D][D]
 * \param int quest_map[6][2]
 * \return Rien
*/
void quest_init(cell_t map[D][D], int quest_map[6][2]){
  /*Quête montagne*/
  quest_map[0][0]=0;
  quest_map[0][1]=range(0,D);
  map[quest_map[0][0]][quest_map[0][1]].quest_id=1;

  /*Quête frontière*/
  quest_map[1][0]=range(0,D);
  quest_map[1][1]=1;
  map[quest_map[1][0]][quest_map[1][1]].quest_id=2;

  /*Quête bunker*/
  quest_map[2][0]=range(1,D-1);
  quest_map[2][1]=range(1,D-1);
  map[quest_map[2][0]][quest_map[2][1]].quest_id=3;

  /*Quête soin*/
  quest_map[4][0]=range(1,D-1);
  quest_map[4][1]=range(1,D-1);
  map[quest_map[4][0]][quest_map[4][1]].quest_id=5;

  /*Quête search*/
  do{ //L'hexagone où se trouve la quete search doit être sur un hexagone de categorie non urbain
      quest_map[5][0]=range(1,D-1);
      quest_map[5][1]=range(1,D-1);
  }while(map[quest_map[5][0]][quest_map[5][1]].categ == 2);
  map[quest_map[5][0]][quest_map[5][1]].quest_id=6;
}


/**
 * \fn void map_init(cell_t map[D][D], int quest_map[6][2], perso_t player)
 * \brief Initialise la map au début de chaque partie
 * \param cell_t map[D][D]
 * \param int quest_map[6][2]
 * \param perso_t player
 * \return Rien
*/
void map_init(cell_t map[D][D], int quest_map[6][2], perso_t player){
  init_base(map);
  init_border(map);
  topup(map, quest_map);
  nextgen(map);
  encounter_init(map,player);
  quest_init(map,quest_map);
}
