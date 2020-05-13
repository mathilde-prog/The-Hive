/**
 * \file interface_options.h
 * \brief Les en-têtes des fonctions de interface_combat.c
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

void affichage_personnage(SDL_Renderer *renderer, char *img_perso, int x, int y);
int combat_bis(SDL_Renderer * renderer, TTF_Font *police/*, stat_t * combat_stats, npc_t * npc*/);
void affichage_help();
