/**
 * \file interface.h
 * \brief Les en-têtes des fonctions de interface.c
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

#define N 13
void init_map_essai(int mapint[N][N]);
void relation_hexa_char(char*mapchar[], int mapint[][N]);
void affichage_case_centrale(SDL_Renderer **renderer);
void affichage_map(SDL_Renderer **renderer, char *map[]);
int interface();

void affichage_personnage(SDL_Renderer *renderer, char *img_perso, int x, int y);
int combat_bis(TTF_Font *police/*, stat_t * combat_stats, npc_t * npc*/);
void affichage_help();

int monscanf(char * c);
int testscanf();
