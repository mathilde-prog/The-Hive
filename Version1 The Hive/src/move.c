#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file move.c
 * \brief Gestion du déplacement du joueur
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int move_lose_pa (hex_t type_hexa)
 * \brief Calcule le nombre de points d'actions nécessaires pour se déplacer dans le type d'hexagone passé en paramètre
 * \param hex_t type_hexa
 * \return Un \a int représentant le nombre de points d'action nécessaires (prairie : 1, foret : 2, ville : 1, lac : 2, camp_mil : 2, camp_ban : 2, market : 1, favella : 2, montagne : 3, frontiere : 1, mer : 1, wasteland : 1)
*/
int move_lose_pa (hex_t type_hexa){
  switch(type_hexa){
    case prairie: return 1; break;
    case foret: return 2; break;
    case ville: return 1; break;
    case lac: return 2; break;
    case camp_mil: return 2; break;
    case camp_ban: return 2; break;
    case market: return 1; break;
    case favella: return 2; break;
    case montagne: return 3; break;
    case frontiere: return 1; break;
    case mer: return 1; break;
    case wasteland: return 1; break;
    default: return 0; break;
  }
}

/**
 * \fn void look_around(int i, int j, cell_t map[D][D])
 * \brief Affiche une vue des 8 hexagones qui entourent le joueur et les codes pour choisir où se déplacer
 * \param int i
 * \param int j
 * \param cell_t map[D][D]
 * \return Rien
*/
void look_around(int i, int j, cell_t map[D][D]){
  int esp;

  printf("\n   +----+----+----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----+----+----+\n");
  printf("   |");
  portable_switch(i-1,j-1,map);
  printf("|");
  portable_switch(i-1,j,map);
  printf("|");
  portable_switch(i-1,j+1,map);
  printf("| <-- Regardez autour de vous pour choisir où aller | 01 | 02 | 03 |\n");
  printf("   +----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+\n");
  printf("   |");
  portable_switch(i,j-1,map);
  printf("\033[1;32m|\033[0m");
  portable_switch(i,j,map);
  printf("\033[1;32m|\033[0m");
  portable_switch(i,j+1,map);
  printf("|");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("| 04 ");
  printf("\033[1;32m| -1 |\033[0m");
  printf(" 05 |\n");
  printf("   +----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+\n");
  printf("   |");
  portable_switch(i+1,j-1,map);
  printf("|");
  portable_switch(i+1,j,map);
  printf("|");
  portable_switch(i+1,j+1,map);
  printf("|     Saisissez le code où vous souhaitez aller --> | 06 | 07 | 08 |\n");
  printf("   +----+----+----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----+----+----+\n");
}

/**
 * \fn void move (perso_t * player, cell_t map[D][D])
 * \brief Déplace le joueur où il le souhaite, si cela est possible (conditions : coordonnées valides et assez de points d'action)
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Rien
*/
void move (perso_t * player, cell_t map[D][D]){
  int change,  l = player->posX, c = player->posY, code;

  jump:
  look_around(l, c, map);
  printf("\n                Si vous souhaitez rester où vous êtes, saisissez -1. \n\n");

  printf("             ========================= Légende =========================\n");
  printf("              PR - Prairie        (-1 pa)   FR - Forêt           (-2 pa)\n");
  printf("              VL - Ville          (-1 pa)   LC - Lac             (-2 pa)\n");
  printf("              CM - Camp militaire (-2 pa)   CB - Camp de bandits (-2 pa)\n");
  printf("              MK - Marché         (-1 pa)   FV - Favella         (-2 pa)\n");
  printf("              MT - Montagne       (-3 pa)   BD - Frontière       (-1 pa)\n");
  printf("              SE - Mer            (-1 pa)   WT - Wasteland       (-1 pa)\n");
  printf("             ===========================================================\n\n");

  if(player->pa){
    printf("   Vous avez \033[1;32m%d\033[00m points d'actions.\n\n", player->pa);
    printf("   Où souhaitez-vous vous rendre ? Code : ");
    do {
      scanf("%d",&code);
      if((code != -1) && ((code < 1) || (code > 8))){
        printf("   Code incorrect. La valeur doit être entre 1 et 8 (ou -1 pour ne pas bouger). Veuillez ressaisir : ");
      }
    } while ((code != -1) && ((code < 1) || (code > 8)));

    if(code == 1){
      if(coordonnees_valides(l-1,c-1)){
        change = move_lose_pa(map[l-1][c-1].type);
        if(change <= player->pa){
          player->posX = l-1;
          player->posY = c-1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas!\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 2){
      if(coordonnees_valides(l-1,c)){
        change = move_lose_pa(map[l-1][c].type);
        if(change <= player->pa){
          player->posX = l-1;
          player->posY = c;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas!\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 3){
      if(coordonnees_valides(l-1,c+1)){
        change = move_lose_pa(map[l-1][c+1].type);
        if(change <= player->pa){
          player->posX = l-1;
          player->posY = c+1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 4){
      if(coordonnees_valides(l,c-1)){
        change = move_lose_pa(map[l][c-1].type);
        if(change <= player->pa){
          player->posX = l;
          player->posY = c-1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 5){
      if(coordonnees_valides(l,c+1)){
        change = move_lose_pa(map[l][c+1].type);
        if(change <= player->pa){
          player->posX = l;
          player->posY = c+1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 6){
      if(coordonnees_valides(l+1,c-1)){
        change = move_lose_pa(map[l+1][c-1].type);
        if(change <= player->pa){
          player->posX = l+1;
          player->posY = c-1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 7){
      if(coordonnees_valides(l+1,c)){
        change = move_lose_pa(map[l+1][c].type);
        if(change <= player->pa){
          player->posX = l+1;
          player->posY = c;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
    else if(code == 8){
      if(coordonnees_valides(l+1,c+1)){
        change = move_lose_pa(map[l+1][c+1].type);
        if(change <= player->pa){
          player->posX = l+1;
          player->posY = c+1;
          player->pa -= change;
        }
        else {
          printf("   Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("   Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
  }
  else {
    printf("   Vous ne pouvez aller nul part sans point d'action.\n\n");
    entree_pour_continuer();
  }
}

void random_move(perso_t * player, cell_t map[D][D]){
  int code, l, c;
  code=range(1,8);
  while(1){
    if(code==1 && coordonnees_valides(l-1,c-1)){

    }else if(code==2 && coordonnees_valides(l-1,c)){
      player->posX = l-1;
      player->posY = c;
      return;
    }else if(code==3 && coordonnees_valides(l-1,c+1)){
      player->posX = l-1;
      player->posY = c+1;
      return;
    }else if(code==4 && coordonnees_valides(l,c-1)){
      player->posX = l;
      player->posY = c-1;
      return;
    }else if(code==5 && coordonnees_valides(l,c+1)){
      player->posX = l;
      player->posY = c+1;
      return;
    }else if(code==6 && coordonnees_valides(l+1,c-1)){
      player->posX = l+1;
      player->posY = c-1;
      return;
    }else if(code==7 && coordonnees_valides(l+1,c)){
      player->posX = l+1;
      player->posY = c;
      return;
    }else if(code==8 && coordonnees_valides(l+1,c+1)){
      player->posX = l+1;
      player->posY = c+1;
      return;
    }
  }
}
