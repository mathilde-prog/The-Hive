#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"lib/interface_options.h"

/**
 * \file interface_options.c
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
 * \fn int combat(TTF_Font *police, stat_t * combat_stats, npc_t * npc)
 * \brief Affiche l'interface de combat
 * \param TTF_Font *police
 * \param stat_t * combat_stats
 * \param npc_t * npc
 * \return Rien
 */
int combat_bis(TTF_Font *police/*, stat_t * combat_stats, npc_t * npc*/){
 	SDL_Window *fight_window = NULL;
 	SDL_Renderer *fight_renderer=NULL;
 	SDL_Rect cases[7];
 	SDL_Surface *texte_fuir=NULL, *texte_reculer=NULL, *texte_attaquer=NULL, *texte_avancer=NULL;
 	SDL_Rect bouton_fuir = {60,400,185,80}, dest_textFuir = {110,420,185,80};
 	SDL_Rect bouton_reculer = {260,400,185,80}, dest_textReculer = {300,420,185,80};
 	SDL_Rect bouton_attaquer = {460,400,185,80}, dest_textAttaquer = {495,420,185,80};
 	SDL_Rect bouton_avancer = {660,400,185,80}, dest_textAvancer = {700,420,185,80};
 	SDL_Color couleurRouge = {255, 0, 0};
 	int i, position_perso = 240, position_npc = 560;

 	fight_window = SDL_CreateWindow("The Hive - Help",SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,900,600, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
 	if(!fight_window){
 		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
 		exit(EXIT_FAILURE);
 	}

 	fight_renderer = SDL_CreateRenderer(fight_window, -1, SDL_RENDERER_ACCELERATED);
 	if(fight_renderer == NULL){
 		fprintf(stderr, "Erreur à la création du renderer\n");
 		exit(EXIT_FAILURE);
 	}

 	texte_fuir = TTF_RenderUTF8_Blended(police, "Fuir",couleurRouge);
 	texte_reculer = TTF_RenderUTF8_Blended(police, "Reculer",couleurRouge);
 	texte_attaquer = TTF_RenderUTF8_Blended(police, "Attaquer",couleurRouge);
 	texte_avancer = TTF_RenderUTF8_Blended(police, "Avancer",couleurRouge);
 	SDL_Texture *txt_texteFuire = SDL_CreateTextureFromSurface(fight_renderer, texte_fuir);
 	SDL_Texture *txt_texteReculer = SDL_CreateTextureFromSurface(fight_renderer, texte_reculer);
 	SDL_Texture *txt_texteAttaquer = SDL_CreateTextureFromSurface(fight_renderer, texte_attaquer);
 	SDL_Texture *txt_texteAvancer = SDL_CreateTextureFromSurface(fight_renderer, texte_avancer);
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
 		cases[i].x = 170+80*i;
 		cases[i].w = 80;
 		cases[i].h = 20;
 	}

	if(fight_window){
 		int running = 1;
 		while(running){
 			SDL_Event event;
 			while(SDL_WaitEvent(&event)){
 				switch(event.type){
 					case SDL_WINDOWEVENT:
					switch(event.window.event){
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
						case SDL_WINDOWEVENT_SHOWN:
		 				SDL_RenderClear(fight_renderer);
		 				SDL_SetRenderDrawColor(fight_renderer, 255, 0, 0, 255);
		 				for (i = 0; i<7; i++){
		 					SDL_RenderDrawRect(fight_renderer,&cases[i]);
		 				}
		 				SDL_RenderCopy(fight_renderer, txt_texteFuire, NULL, &dest_textFuir);
		 				SDL_RenderCopy(fight_renderer, txt_texteReculer, NULL, &dest_textReculer);
		 				SDL_RenderCopy(fight_renderer, txt_texteAttaquer, NULL, &dest_textAttaquer);
		 				SDL_RenderCopy(fight_renderer, txt_texteAvancer, NULL, &dest_textAvancer);
		 				SDL_RenderDrawRect(fight_renderer,&bouton_fuir);
		 				SDL_RenderDrawRect(fight_renderer,&bouton_reculer);
		 				SDL_RenderDrawRect(fight_renderer,&bouton_attaquer);
		 				SDL_RenderDrawRect(fight_renderer,&bouton_avancer);

		 				affichage_personnage(fight_renderer,"img/CreBandit03_inv.png", position_perso, 290);
		 				affichage_personnage(fight_renderer,"img/CreBandit02.png",position_npc,290);

		 				SDL_SetRenderDrawColor(fight_renderer, 206, 206, 206, 255);
		 				SDL_RenderPresent(fight_renderer);
		 				break;
					}
 					case SDL_MOUSEBUTTONDOWN:
 					if(event.button.button == SDL_BUTTON_LEFT){
 						//on regarde lequel des 4 boutons a été pushed
 						if(event.button.x > bouton_fuir.x && event.button.x < bouton_fuir.x+bouton_fuir.w && (event.button.y > bouton_fuir.y && event.button.y < bouton_fuir.y+bouton_fuir.h))
						{
 							if(position_perso <= 170){
 								printf("Vous prenez la fuite \n");
 								running = 0;
								 SDL_DestroyWindow(fight_window);
								return 1;
 							}
 							else {
 								printf("Vous devez d'abrod reculez pour fuire\n");
 							}
 						}
 						if(event.button.x > bouton_reculer.x && event.button.x < bouton_reculer.x+bouton_reculer.w && (event.button.y > bouton_reculer.y && event.button.y < bouton_reculer.y+bouton_reculer.h)){
 							if(position_perso <= 160)
 								printf("Impossible de reculer d'avantage, mais vous pouvez fuir\n");
 							else
 								position_perso -= 80;
 						}
 						if(event.button.x > bouton_attaquer.x && event.button.x < bouton_attaquer.x+bouton_attaquer.w && (event.button.y > bouton_attaquer.y && event.button.y < bouton_attaquer.y+bouton_attaquer.h)){
 							printf("Vous décidez d'attaquer votre adversaire \n");
 						}
 						if(event.button.x > bouton_avancer.x && event.button.x < bouton_avancer.x+bouton_avancer.w && (event.button.y > bouton_avancer.y && event.button.y < bouton_avancer.y+bouton_avancer.h)){
 							if(position_npc <= position_perso+80)
 								printf("Impossible d'avancer davantage, votre adversaire est devant vous\n");
 							else
 								position_perso += 80;
 						}
 					}
					SDL_RenderClear(fight_renderer);
					SDL_SetRenderDrawColor(fight_renderer, 255, 0, 0, 255);
					for (i = 0; i<7; i++){
						SDL_RenderDrawRect(fight_renderer,&cases[i]);
					}
					SDL_RenderCopy(fight_renderer, txt_texteFuire, NULL, &dest_textFuir);
					SDL_RenderCopy(fight_renderer, txt_texteReculer, NULL, &dest_textReculer);
					SDL_RenderCopy(fight_renderer, txt_texteAttaquer, NULL, &dest_textAttaquer);
					SDL_RenderCopy(fight_renderer, txt_texteAvancer, NULL, &dest_textAvancer);
					SDL_RenderDrawRect(fight_renderer,&bouton_fuir);
					SDL_RenderDrawRect(fight_renderer,&bouton_reculer);
					SDL_RenderDrawRect(fight_renderer,&bouton_attaquer);
					SDL_RenderDrawRect(fight_renderer,&bouton_avancer);

					affichage_personnage(fight_renderer,"../data/img/CreBandit03_inv.png", position_perso, 290);
					affichage_personnage(fight_renderer,"../data/img/CreBandit02.png",position_npc,290);

					SDL_SetRenderDrawColor(fight_renderer, 206, 206, 206, 255);
					SDL_RenderPresent(fight_renderer);
					break;
 				}
 			}
 		}
	}
	//ne seras jamais atteinds mais permet d'éviter un warning à la compilation
	return 0;
}


/**
 * \fn void affichage_help()
 * \brief Affiche la document d'aide pour le joueur
 * \return Rien
 */
void affichage_help(){
	//Le pointeur vers la fenetre
	SDL_Window* help_window = NULL;
	SDL_Renderer *help_renderer=NULL;
	SDL_Surface *help_surface;
	SDL_Rect dest_img;
	SDL_Texture *help_txt;
	SDL_RWops *rwop_help;

	help_window = SDL_CreateWindow("The Hive - Help",SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,840,710, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	if(!help_window){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	help_renderer = SDL_CreateRenderer(help_window, -1, SDL_RENDERER_ACCELERATED);
	if(help_renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

	rwop_help = SDL_RWFromFile("../data/help_the_hive_v2.png","rb");
	help_surface = IMG_LoadPNG_RW(rwop_help);
	help_txt = SDL_CreateTextureFromSurface(help_renderer,help_surface);
	dest_img.x = 0;
	dest_img.y = 0;
	SDL_QueryTexture(help_txt, NULL, NULL, &(dest_img.w), &(dest_img.h));
	SDL_FreeSurface(help_surface);

	if (help_window){
		int run =1;
		while(run){
			SDL_Event event1;
			while(SDL_PollEvent(&event1)) {
				switch(event1.type) {
					case SDL_WINDOWEVENT:
					switch(event1.window.event){
						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
						case SDL_WINDOWEVENT_SHOWN:
						SDL_RenderClear(help_renderer);
						SDL_RenderCopy(help_renderer, help_txt, NULL, &dest_img);
						SDL_RenderPresent(help_renderer);
						break;
					}
					break;
					case SDL_KEYDOWN:
            switch(event1.key.keysym.sym){
                 case SDLK_ESCAPE:
                 run = 0;
                 break;
            }
            break;
					case SDL_MOUSEWHEEL:
						if (event1.wheel.y > 0)
							if (dest_img.y < 0)
								dest_img.y +=15;
						if (event1.wheel.y < 0)
							if (dest_img.y > -(1500-710))
								dest_img.y -=15;
						SDL_QueryTexture(help_txt, NULL, NULL, &(dest_img.w), &(dest_img.h));
						SDL_RenderClear(help_renderer);
						SDL_RenderCopy(help_renderer, help_txt, NULL, &dest_img);
						SDL_RenderPresent(help_renderer);
						break;
				}
			}
		}
		SDL_DestroyWindow(help_window);
	}
}
