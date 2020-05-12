#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"lib/interface_combat.h"

/**
 * \file combat.c
 * \brief Affichage de l'interface de combat via SDL2
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void affichage_personnage(SDL_Renderer *renderer, char *img_perso, int x, int y)
 * \brief Affiche un personnage dont l'image est en paramètre aux coordonées passées en paramètres
 * \param SDL_Renderer *renderer
 * \param char *img_perso
 * \param int x
 * \param int y
 * \return Rien
 */
void affichage_personnage(SDL_Renderer *renderer, char *img_perso, int x, int y){
	SDL_Surface *personnage;
	SDL_Rect dest_centre;
	SDL_Texture *personnage_txt;
	SDL_RWops *rwop_personnage;
	rwop_personnage = SDL_RWFromFile(img_perso,"rb");
	personnage = IMG_LoadPNG_RW(rwop_personnage);
	personnage_txt = SDL_CreateTextureFromSurface(renderer, personnage);
	dest_centre.x = x;
	dest_centre.y = y;

	SDL_QueryTexture(personnage_txt, NULL, NULL, &(dest_centre.w), &(dest_centre.h));
	SDL_RenderCopy(renderer, personnage_txt, NULL, &dest_centre);
	SDL_FreeSurface(personnage);
}

/**
 * \fn int combat(SDL_Renderer * renderer, TTF_Font *police, stat_t * combat_stats, npc_t * npc)
 * \brief Affiche l'interface de combat
 * \param SDL_Renderer * renderer
 * \param TTF_Font *police
 * \param stat_t * combat_stats
 * \param npc_t * npc
 * \return Rien
 */
int combat_bis(SDL_Renderer * renderer, TTF_Font *police/*, stat_t * combat_stats, npc_t * npc*/){
	SDL_Rect rect_fight = {400,0,900,550};
	SDL_Rect cases[7];
	SDL_Surface *texte_fuir=NULL, *texte_reculer=NULL, *texte_attaquer=NULL, *texte_avancer=NULL;
	SDL_Rect bouton_fuir = {460,400,185,80}, dest_textFuir = {510,420,185,80};
	SDL_Rect bouton_reculer = {660,400,185,80}, dest_textReculer = {700,420,185,80};
	SDL_Rect bouton_attaquer = {860,400,185,80}, dest_textAttaquer = {895,420,185,80};
	SDL_Rect bouton_avancer = {1060,400,185,80}, dest_textAvancer = {1100,420,185,80};
	SDL_Color couleurRouge = {255, 0, 0};
	int i, position_perso = 640, position_npc = 960;

	texte_fuir = TTF_RenderUTF8_Blended(police, "Fuir",couleurRouge);
	texte_reculer = TTF_RenderUTF8_Blended(police, "Reculer",couleurRouge);
	texte_attaquer = TTF_RenderUTF8_Blended(police, "Attaquer",couleurRouge);
	texte_avancer = TTF_RenderUTF8_Blended(police, "Avancer",couleurRouge);
	SDL_Texture *txt_texteFuire = SDL_CreateTextureFromSurface(renderer, texte_fuir);
	SDL_Texture *txt_texteReculer = SDL_CreateTextureFromSurface(renderer, texte_reculer);
	SDL_Texture *txt_texteAttaquer = SDL_CreateTextureFromSurface(renderer, texte_attaquer);
	SDL_Texture *txt_texteAvancer = SDL_CreateTextureFromSurface(renderer, texte_avancer);
	SDL_FreeSurface(texte_fuir);
	SDL_FreeSurface(texte_reculer);
	SDL_FreeSurface(texte_attaquer);
	SDL_FreeSurface(texte_avancer);
	SDL_QueryTexture(txt_texteFuire, NULL, NULL, &(dest_textFuir.w), &(dest_textFuir.h));
	SDL_QueryTexture(txt_texteReculer, NULL, NULL, &(dest_textReculer.w), &(dest_textReculer.h));
	SDL_QueryTexture(txt_texteAttaquer, NULL, NULL, &(dest_textAttaquer.w), &(dest_textAttaquer.h));
	SDL_QueryTexture(txt_texteAvancer, NULL, NULL, &(dest_textAvancer.w), &(dest_textAvancer.h));

	for (i = 0; i<7; i++){
		cases[i].y = 350;
		cases[i].x = 570+80*i;
		cases[i].w = 80;
		cases[i].h = 20;
	}

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 206, 206, 206, 255);
	SDL_RenderFillRect(renderer,&rect_fight);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (i = 0; i<7; i++){
		SDL_RenderDrawRect(renderer,&cases[i]);
	}
	SDL_RenderCopy(renderer, txt_texteFuire, NULL, &dest_textFuir);
	SDL_RenderCopy(renderer, txt_texteReculer, NULL, &dest_textReculer);
	SDL_RenderCopy(renderer, txt_texteAttaquer, NULL, &dest_textAttaquer);
	SDL_RenderCopy(renderer, txt_texteAvancer, NULL, &dest_textAvancer);
	SDL_RenderDrawRect(renderer,&bouton_fuir);
	SDL_RenderDrawRect(renderer,&bouton_reculer);
	SDL_RenderDrawRect(renderer,&bouton_attaquer);
	SDL_RenderDrawRect(renderer,&bouton_avancer);

	affichage_personnage(renderer,"../data/img/CreBandit03_inv.png", position_perso, 290);
	affichage_personnage(renderer,"../data/img/CreBandit02.png",position_npc,290);

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderPresent(renderer);
	int fight = 1;
	while(fight){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT: fight = 0;
				break;
				case SDL_WINDOWEVENT:
				case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT){
					//on regarde lequel des 4 boutons a été pushed
					if(event.button.x > bouton_fuir.x && event.button.x < bouton_fuir.x+bouton_fuir.h && (event.button.y > bouton_fuir.y && event.button.y < bouton_fuir.y+bouton_fuir.h)){
						if(position_perso <= 560){
							printf("Vous prenez la fuite \n");
							fight = 0;
						}
						else {
							printf("Vous devez d'abrod reculez pour fuire\n");
						}
					}
					if(event.button.x > bouton_reculer.x && event.button.x < bouton_reculer.x+bouton_reculer.h && (event.button.y > bouton_reculer.y && event.button.y < bouton_reculer.y+bouton_reculer.h)){
						if(position_perso <= 560)
							printf("Impossible de reculer d'avantage, mais vous pouvez fuir\n");
						else
							position_perso -= 80;
					}
					if(event.button.x > bouton_attaquer.x && event.button.x < bouton_attaquer.x+bouton_attaquer.h && (event.button.y > bouton_attaquer.y && event.button.y < bouton_attaquer.y+bouton_attaquer.h)){
						printf("Vous décidez d'attaquer votre adversaire \n");
					}
					if(event.button.x > bouton_avancer.x && event.button.x < bouton_avancer.x+bouton_avancer.h && (event.button.y > bouton_avancer.y && event.button.y < bouton_avancer.y+bouton_avancer.h)){
						if(position_npc <= position_perso+80)
							printf("Impossible d'avancer davantage, votre adversaire est devant vous\n");
						else
							position_perso += 80;
					}
				}
				//on affiche a nouveau l'interface de combat
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 206, 206, 206, 255);
				SDL_RenderFillRect(renderer,&rect_fight);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				for (i = 0; i<7; i++){
					SDL_RenderDrawRect(renderer,&cases[i]);
				}
				SDL_RenderCopy(renderer, txt_texteFuire, NULL, &dest_textFuir);
				SDL_RenderCopy(renderer, txt_texteReculer, NULL, &dest_textReculer);
				SDL_RenderCopy(renderer, txt_texteAttaquer, NULL, &dest_textAttaquer);
				SDL_RenderCopy(renderer, txt_texteAvancer, NULL, &dest_textAvancer);
				SDL_RenderDrawRect(renderer,&bouton_fuir);
				SDL_RenderDrawRect(renderer,&bouton_reculer);
				SDL_RenderDrawRect(renderer,&bouton_attaquer);
				SDL_RenderDrawRect(renderer,&bouton_avancer);

				affichage_personnage(renderer,"../data/img/CreBandit03_inv.png", position_perso, 290);
				affichage_personnage(renderer,"../data/img/CreBandit02.png",position_npc,290);

				SDL_SetRenderDrawColor(renderer,0,0,0,255);
				SDL_RenderPresent(renderer);
				break;
			}
		}
	}
}
