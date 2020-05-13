#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/commun.h"

/**
 * \file world_generation.c
 * \brief Génération de la carte
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void afficher_type_categ_hexa(cell_t map[D][D], int l, int c)
 * \brief Affiche le type et la catégorie de l'hexagone de la carte dont les coordonnées sont passées en paramètres
 * \param map[D][D] Matrice de la carte
 * \param l Coordonnée ligne de l'hexagone qu'on souhaite afficher
 * \param c Coordonnée colonne de l'hexagone qu'on souhaite afficher
 * \return Rien
*/
void afficher_type_categ_hexa(cell_t map[D][D], int l, int c){
  switch(map[l][c].type){
    case prairie   : printf("prairie "); break;
    case foret     : printf("forêt ");    break;
    case ville     : printf("ville ");    break;
    case lac       : printf("lac ");     break;
    case camp_mil  : printf("camp militaire ");  break;
    case camp_ban  : printf("camp des bandits ");     break;
    case market    : printf("marché ");   break;
    case favela   : printf("favela ");   break;
    case montagne  : printf("montagne ");     break;
    case frontiere : printf("frontière ");      break;
    case mer       : printf("mer ");   break;
    case wasteland : printf("wasteland ");    break;
  }

  switch(map[l][c].categ){
    case other   : printf("[AUTRE]\n"); break;
    case nature  : printf("[NATURE]\n"); break;
    case urbain  : printf("[URBAIN]\n"); break;
    case militaire : printf("[MILITAIRE]\n");  break;
  }
}

/**
 * \fn void informations_map(cell_t map[D][D])
 * \brief Affiche les informations de la carte
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void informations_map(cell_t map[D][D]){
  int l, c;

  printf("\033[34;01m   Type\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].type);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01mCateg\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].categ);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Encounter\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].encounter);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Quest ID\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].quest_id);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("\033[34;01m   Scavenged\033[00m\n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      if(c == 0){
        printf("   ");
      }
      printf("%2d ", map[l][c].scavenged);
    }
    printf("\n");
  }
  printf("\n\n");
}

/**
 * \fn void init_border(cell_t map[D][D])
 * \brief Initialise les contours de la map
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void init_border(cell_t map[D][D]){
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
 * \fn void topup(cell_t map[D][D], int quest_map[6][2])
 * \brief Crée un nombre déterminé d’hexagones indispensables pour la carte (comme camp militaire/bandit par exemple) sur des coordonnées aléatoires
 * \param map[D][D] Matrice de la carte
 * \param quest_map[6][2] Matrice des coordonnées des quêtes
 * \return Rien
*/
void topup(cell_t map[D][D], int quest_map[6][2]){
  int s,i,j;
  int low=1, high=D-1;

  i = range(low+1,high-2);
  j = range(low+1,high-2);
  map[i][j].type=market;
  map[i][j].categ=urbain;
  map[i-1][j].type=favela;
  map[i-1][j].categ=urbain;
  map[i-1][j-1].type=favela;
  map[i-1][j-1].categ=urbain;
  map[i-1][j+1].type=favela;
  map[i-1][j+1].categ=urbain;
  map[i][j-1].type=favela;
  map[i][j-1].categ=urbain;
  map[i][j+1].type=favela;
  map[i][j+1].categ=urbain;
  map[i+1][j-1].type=favela;
  map[i+1][j-1].categ=urbain;
  map[i+1][j].type=favela;
  map[i+1][j].categ=urbain;
  map[i+1][j+1].type=favela;
  map[i+1][j+1].categ=urbain;

  for(s=3; s!=0;s--){
    i = range(low,high-1);
    j = range(low,high-1);
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
 * \brief Compte le nombre d'hexagones-voisins similaires et selon ce nombre, après des calculs de probabilité, renvoie le type d’hexagone qui sera créé sur les coordonnées passées en paramètre
 * \param l Coordonnée ligne
 * \param c Coordonnée colonne
 * \param map[D][D] Matrice de la carte
 * \return Retourne un \a int : le type de l'hexagone qui va être créé
*/
int spawntype(int l, int c, cell_t map[D][D]){
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
 * \param input Type d'hexagone
 * \return Retourne un \a int correspondant à la catégorie de l'hexagone
*/
int categ_switch(int input){
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
 * \brief Parcours la matrice de la carte passée en paramètre et fait appel à #spawntype pour calculer le type d’hexagone qui va apparaître dans la cellule courante
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void nextgen(cell_t map[D][D]){
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
 * \brief Vérifie si les coordonnées sont valides
 * \param l Coordonnée ligne
 * \param c Coordonnée colonne
 * \return Retourne un \a int : 1 si les coordonnées sont valides, 0 si non
*/
int coordonnees_valides(int l, int c){
  return ((l >= 0 && l < D) && (c >= 0 && c < D));
}


/**
 * \fn void portable_switch(int i, int j, cell_t map[D][D])
 * \brief Affiche le code de la cellule
 * \details
    Cette fonction a été créée pour éviter de refaire le switch dans différentes fonctions d'affichage.
 * \param i Coordonnée ligne
 * \param j Coordonnée colonne
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void portable_switch(int i, int j, cell_t map[D][D]){
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
 * \param l Coordonnée ligne
 * \param c Coordonnée colonne
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void display_TEXT(int l, int c, cell_t map[D][D]){
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
      printf("|     FV - Favela\n");
    }else if(i==10){
      printf("|     MT - Montagne\n");
    }else if(i==11){
      printf("|     BD - Frontiere\n");
    }else if(i==12){
      printf("|     SE - Mer\n");
    }else if(i==13){
      printf("|     WT - Wasteland\n");
    }else{
      //prairie=1,foret,ville,lac,camp_mil,camp_ban,market,favela,montagne,frontiere,mer,wasteland
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
 * \fn void init_base(cell_t map[D][D])
 * \brief Initialise la base de la carte
 * \details La carte est initialisée par des hexagones de type prairie (catégorie nature), sans combat, sans quête et sans hexagones fouillés.
 * \param map[D][D] Matrice de la carte
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
 * \brief Compte le nombre d'occurence de chaque type de cellule (outil de test)
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void count(const cell_t map[D][D]){
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
      }if(map[i][j].type==favela){
        fv++;
      }
    }
  }
  printf("\nCity: %d\nForest: %d\nHills: %d\nBandit camp: %d\nMilitary camp: %d\nMarket: %d\nFavela: %d\n",c,f,h,cb,cm,mr,fv);
}

/**
 * \fn void encounter_init(cell_t map[D][D])
 * \brief Initialise les positions des combats sur la carte
 * \param map[D][D] Matrice de la carte
 * \return Rien
*/
void encounter_init(cell_t map[D][D]){
  int i,j;

  for(i=1;i<D-1;i++){
    for(j=1;j<D-1;j++){
      if(rng(10)){
          map[i][j].encounter=1;
      }
    }
  }
}

/**
 * \fn void quest_init(cell_t map[D][D], int quest_map[6][2])
 * \brief Initialise les quêtes (quest_id) sur la carte
 * \details
    Les quêtes sont placées aléatoirement sur la carte.
 * \param map[D][D] Matrice de la carte
 * \param quest_map[6][2] Matrice des coordonnées des quêtes
 * \return Rien
*/
void quest_init(cell_t map[D][D], int quest_map[6][2]){
  /*Quête montagne  - Sur un hexagone de type montagne*/
  quest_map[0][0]=0;
  quest_map[0][1]=range(0,D-2);
  map[quest_map[0][0]][quest_map[0][1]].quest_id=1;

  /*Quête frontière - Sur un hexagone de type frontière */
  quest_map[1][0]=range(0,D-1);
  quest_map[1][1]=D-1;
  map[quest_map[1][0]][quest_map[1][1]].quest_id=2;

  /*Quête bunker - Hexagone hors bordure de type nature (mais pas un lac) */
  do {
    quest_map[2][0]=range(1,D-2);
    quest_map[2][1]=range(1,D-2);
  } while((map[quest_map[2][0]][quest_map[2][1]].categ != nature) || (map[quest_map[2][0]][quest_map[2][1]].type == lac));
  map[quest_map[2][0]][quest_map[2][1]].quest_id=3;

  /*Quête soin - Hexagone hors bordure - ni lac, ni camp bandits, ni sur le même hexagone qu'une autre quête' */
  do {
    quest_map[4][0]=range(1,D-2);
    quest_map[4][1]=range(1,D-2);
  } while((map[quest_map[4][0]][quest_map[4][1]].type == lac) || (map[quest_map[4][0]][quest_map[4][1]].type == camp_ban) || (map[quest_map[4][0]][quest_map[4][1]].quest_id != 0));
  map[quest_map[4][0]][quest_map[4][1]].quest_id=5;

  /*Quête search - Hexagone hors bordure - ni urbain, ni camp_bandits, ni sur le même hexagone qu'une autre quête */
  do{
    quest_map[5][0]=range(1,D-2);
      quest_map[5][1]=range(1,D-2);
  }while((map[quest_map[5][0]][quest_map[5][1]].categ == urbain) || (map[quest_map[5][0]][quest_map[5][1]].type == camp_ban) || (map[quest_map[5][0]][quest_map[5][1]].quest_id != 0));
  map[quest_map[5][0]][quest_map[5][1]].quest_id=6;
}

/**
 * \fn void map_init(cell_t map[D][D], int quest_map[6][2])
 * \brief Initialise la carte au début de chaque partie
 * \param map[D][D] Matrice de la carte
 * \param quest_map[6][2] Matrice des coordonnées des quêtes
 * \param player Joueur
 * \return Rien
*/
void map_init(cell_t map[D][D], int quest_map[6][2]){
  init_base(map);
  init_border(map);
  topup(map, quest_map);
  nextgen(map);
  encounter_init(map);
  quest_init(map,quest_map);
}
