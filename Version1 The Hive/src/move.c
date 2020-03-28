#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

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

void look_around(int i, int j, cell_t map[D][D]){
  int esp;

  printf("+----+----+----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----+----+----+\n");
  printf("|");
  portable_switch(i-1,j-1,map);
  printf("|");
  portable_switch(i-1,j,map);
  printf("|");
  portable_switch(i-1,j+1,map);
  printf("| <-- Regardez autour de vous pour choisir où aller | 01 | 02 | 03 |\n");
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+\n");
  printf("|");
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
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----");
  printf("\033[1;32m+----+\033[0m");
  printf("----+\n");
  printf("|");
  portable_switch(i+1,j-1,map);
  printf("|");
  portable_switch(i+1,j,map);
  printf("|");
  portable_switch(i+1,j+1,map);
  printf("|     Saisissez le code où vous souhaitez aller -->  | 06 | 07 | 08 |\n");
  printf("+----+----+----+");
  for(esp = 0; esp < 51; esp++){
    printf(" ");
  }
  printf("+----+----+----+\n");
}

void move (perso_t * player, cell_t map[D][D]){
  int nb, change,  l = player->posX, c = player->posY, code;

  jump:
  look_around(l, c, map);
  printf("\n--> Si vous souhaitez rester où vous êtes, saisissez -1.\n\n");

  printf("========================= Légende =========================\n");
  printf("PR - Prairie        (-1 pa)   FR - Forêt           (-2 pa)\n");
  printf("VL - Ville          (-1 pa)   LC - Lac             (-2 pa)\n");
  printf("CM - Camp militaire (-2 pa)   CB - Camp de bandits (-2 pa)\n");
  printf("MK - Marché         (-1 pa)   FV - Favella         (-2 pa)\n");
  printf("MT - Montagne       (-3 pa)   BD - Frontière       (-1 pa)\n");
  printf("SE - Mer            (-1 pa)   WT - Wasteland       (-1 pa)\n");
  printf("===========================================================\n\n");

  if(player->pa){
    do {
      printf("Vous avez %d points d'action.\n",player->pa);
      printf("Où souhaitez-vous vous rendre ? Code: ");
      scanf("%d",&code);
      if((code != -1) && ((code < 1) || (code > 8))){
        printf("Code incorrect. La valeur doit être entre 1 et 8)\n");
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas!\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas!\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
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
          printf("Vous n'avez pas assez de points d'action pour vous y rendre.\n");
          sleep(1); clrscr();
        }
      }
      else {
        printf("Vous ne pouvez pas aller là-bas\n"); sleep(1); clrscr();
        goto jump;
      }
    }
  }
  else {
    printf("Vous ne pouvez aller nul part sans point d'action.\n");
    do {
      printf("\nRetour au menu (1) : ");
      scanf("%d",&nb);
      if(nb != 1){
        printf("Saisissez 1 pour retourner au menu principal\n");
      }
    } while (nb != 1);
  }
}
