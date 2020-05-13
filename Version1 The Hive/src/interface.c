#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<time.h>
#include"lib/interface.h"
#include"lib/commun.h"

/**
 * \file interface.c
 * \brief Affichage de l'interface de jeu via SDL2
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

char *map[N*N];
/*
 * fonction de test qui permet de tester l'affichage de la map avec une version d'essais, simplifiée
 */
void init_map_essai(int mapint[N][N]){
	int i,j,k;

	for(i=0;i<N;i++){
		for (j=0;j<N;j++){
			k = (rand()%11)+1;
			mapint[i][j] = k;
		}
	}
}


/**
 * \fn void relation_hexa_char(char* mapchar[], int mapint[N][N])
 * \brief Remplit un matrice des nom des cases a afficher (images) à partir du chiffre contenu dans la matrice initiale
 * \param char* mapchar[]
 * \param int mapint[N][N]
 * \return Rien
 */
void relation_hexa_char(char*mapchar[], int mapint[N][N]){
	int i,j,k=0;
	for (i=0; i<N;i++){
		for (j=0; j<N;j++){
			switch(mapint[i][j]){
				case 1 : mapchar[k]="../data/hexa_png/hex_forest2.png";k++;break;
				case 2 : mapchar[k]="../data/hexa_png/hex_city1.png";k++;break;
				case 3 : mapchar[k]="../data/hexa_png/hex_lake1.png";k++;break;
				case 4 : mapchar[k]="../data/hexa_png/hex_military_base.png";k++;break;
				case 5 : mapchar[k]="../data/hexa_png/hex_bandit_camp.png";k++;break;
				case 6 : mapchar[k]="../data/hexa_png/hex_market.png";k++;break;
				case 7 : mapchar[k]="../data/hexa_png/hex_favella.png";k++;break;
				case 8 : mapchar[k]="../data/hexa_png/hex_mountains.png";k++;break;
				case 9 : mapchar[k]="../data/hexa_png/hex_border.png";k++;break;
				case 10 : mapchar[k]="../data/hexa_png/hex_sea.png";k++;break;
				case 11 : mapchar[k]="../data/hexa_png/hex_wasteland1.png";k++;break;
				default : mapchar[k]="../data/hexa_png/HexBlankDay.png";k++;
			}
		}
	}
}
/**
 * \fn void affichage_case_centrale(SDL_Renderer **renderer)
 * \brief Affiche dans la case centrale de l'écran un hilight et le personnage
 * \param SDL_Renderer **renderer
 * \return Rien
 */
void affichage_case_centrale(SDL_Renderer **renderer){
	SDL_Surface *hilight_surface, *personnage;
	SDL_Rect dest_centre;
	SDL_Texture *hilight_txt, *personnage_txt;
	SDL_RWops *rwop_hilight, *rwop_personnage;
	//cellule surligné qui indique ou es le personnage
	rwop_hilight = SDL_RWFromFile("../data/img/HexHilight.png","rb");
	rwop_personnage = SDL_RWFromFile("../data/img/CreBandit03.png","rb");
	hilight_surface = IMG_LoadPNG_RW(rwop_hilight);
	personnage = IMG_LoadPNG_RW(rwop_personnage);
	hilight_txt = SDL_CreateTextureFromSurface(*renderer,hilight_surface);
	personnage_txt = SDL_CreateTextureFromSurface(*renderer, personnage);
	dest_centre.x = 800;
	dest_centre.y = 235;

	SDL_QueryTexture(hilight_txt, NULL, NULL, &(dest_centre.w), &(dest_centre.h));
	SDL_QueryTexture(personnage_txt, NULL, NULL, &(dest_centre.w), &(dest_centre.h));
	SDL_RenderCopy(*renderer, hilight_txt, NULL, &dest_centre);
	SDL_RenderCopy(*renderer, personnage_txt, NULL, &dest_centre);
	SDL_FreeSurface(hilight_surface);
	SDL_FreeSurface(personnage);
}


/**
 * \fn void affichage_map(SDL_Renderer **renderer, char *map[])
 * \brief Affiche la map, c'est à dire la partie composée d'hexagones
 * \param SDL_Renderer **renderer
 * \param char *map[]
 * \return Rien
 */
void affichage_map(SDL_Renderer **renderer, char *map[]){
	SDL_Surface *image[N*N];
	SDL_Rect dest_image[N*N];
	SDL_Texture *image_tex[N*N];
	SDL_RWops *rwop[N*N];
	int mapint[N][N];
	int i,j,k,l;
	// x et y sont les coordonées auxquelles on affichera un hexagone
	int x,y;

	init_map_essai(mapint);
	relation_hexa_char(map,mapint);

	for (i=0; i<N*N; i++){
		rwop[i]=SDL_RWFromFile(map[i],"rb");
		image[i]=IMG_LoadPNG_RW(rwop[i]);
 		image_tex[i] = SDL_CreateTextureFromSurface(*renderer,image[i]);
	}
	x=400;
	y=-25;
	dest_image[0].x=x;
	dest_image[0].y=y;
	for (k=0;k<N;k++){
		x=400;
		for (l=0;l<N;l++){
			//la premiere case etant deja initialisé on n'y touche pas
			if (k==0 && l==0)
				x=480;
			else {
				if (l%2==0){
					dest_image[k*N+l].x = x;
					dest_image[k*N+l].y = y;
					x+=80;
				}
				else {
					dest_image[k*N+l].x = x;
					dest_image[k*N+l].y = y+20;
					x+=80;
				}
			}
		}
		y+=40;
	}

	// on affiche d'abord les cellules paires car sinon on a le bas de la cellule qui passe au premier plan
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			if (j%2==0){
				SDL_QueryTexture(image_tex[i*N+j], NULL, NULL, &(dest_image[i*N+j].w), &(dest_image[i*N+j].h));
				SDL_RenderCopy(*renderer, image_tex[i*N+j], NULL, &dest_image[i*N+j]);
				SDL_FreeSurface(image[i*N+j]);
			}
		}
		for (j=0;j<N;j++){
			if (j%2){
				SDL_QueryTexture(image_tex[i*N+j], NULL, NULL, &(dest_image[i*N+j].w), &(dest_image[i*N+j].h));
				SDL_RenderCopy(*renderer, image_tex[i*N+j], NULL, &dest_image[i*N+j]);
				SDL_FreeSurface(image[i*N+j]);
			}
		}
	}
	affichage_case_centrale(renderer);
}


/**
 * \fn int interface()
 * \brief Affiche l'interface en elle-même
 * \return 0 si tout c'est bien passé
 */
int interface(){
  //Le pointeur vers la fenetre
	SDL_Window* ecran = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
  SDL_Surface *texte_help=NULL, *texte_exit=NULL, *texte_rest = NULL, *texte_turn = NULL, *texte_fouille = NULL, *texte_inv = NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect rect1 = {0,0,400,700};
	SDL_Rect rect2 = {400,550,900,150};
	SDL_Rect bouton_help = {5,505,390,90}, dest_textHelp = {85,515,390,90};
	SDL_Rect bouton_exit = {5,605,390,90}, dest_textExit = {85,615,390,90};
	SDL_Rect bouton_rest = {5,415,185,80}, dest_textRest = {15,440,185,80};
	SDL_Rect bouton_turn = {205,415,185,80}, dest_textTurn = {240,440,185,80};
	SDL_Rect bouton_fouille = {5,330,185,80}, dest_textFouille = {50,355,185,80};
	SDL_Rect bouton_inv = {205,330,185,80}, dest_textInv = {230,355,185,80};

	// Le pointeur vers notre police1
	TTF_Font *police1 = NULL, *police2 = NULL;
	// Une variable de couleur verte
	SDL_Color couleurVerte = {63, 206, 10};

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

  /* Création de la fenêtre */
	ecran = SDL_CreateWindow("The Hive - A Post Apocalypse Project",SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,1300,700, SDL_WINDOW_SHOWN);
	/* icone de la fenetre */
	SDL_Surface *icon=NULL;
	SDL_RWops *icon_rwop=NULL;
	icon_rwop=SDL_RWFromFile("../data/img/ItmEncMergaLoupe.png","rb");
	icon=IMG_LoadPNG_RW(icon_rwop);
	SDL_SetWindowIcon(ecran,icon);

	if(!ecran){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}
	if( (police1 = TTF_OpenFont("../data/Menlo-Regular.ttf", 55)) == NULL){
		fprintf(stderr, "1 erreur chargement font\n");
		exit(EXIT_FAILURE);
	}
	if( (police2 = TTF_OpenFont("../data/Menlo-Regular.ttf", 25)) == NULL){
		fprintf(stderr, "2 erreur chargement font\n");
		exit(EXIT_FAILURE);
	}

	/* creation des textures pour afficher le texte des boutons*/
	texte_help = TTF_RenderUTF8_Blended(police1, " Help", couleurVerte);
	texte_exit = TTF_RenderUTF8_Blended(police1, " Exit",couleurVerte);
	texte_rest = TTF_RenderUTF8_Blended(police2, "Rest & Heal",couleurVerte);
	texte_turn = TTF_RenderUTF8_Blended(police2, "End turn",couleurVerte);
	texte_fouille = TTF_RenderUTF8_Blended(police2, "Search",couleurVerte);
	texte_inv = TTF_RenderUTF8_Blended(police2, "Inventory",couleurVerte);
	SDL_Texture *txt_texteHelp = SDL_CreateTextureFromSurface(renderer, texte_help);
	SDL_Texture *txt_texteExit = SDL_CreateTextureFromSurface(renderer, texte_exit);
	SDL_Texture *txt_texteRest = SDL_CreateTextureFromSurface(renderer, texte_rest);
	SDL_Texture *txt_texteTurn = SDL_CreateTextureFromSurface(renderer, texte_turn);
	SDL_Texture *txt_texteFouille = SDL_CreateTextureFromSurface(renderer, texte_fouille);
	SDL_Texture *txt_texteInv = SDL_CreateTextureFromSurface(renderer, texte_inv);
	SDL_FreeSurface(texte_exit);
	SDL_FreeSurface(texte_help);
	SDL_FreeSurface(texte_rest);
	SDL_FreeSurface(texte_turn);
	SDL_FreeSurface(texte_fouille);
	SDL_FreeSurface(texte_inv);
	SDL_QueryTexture(txt_texteHelp, NULL, NULL, &(dest_textHelp.w), &(dest_textHelp.h));
	SDL_QueryTexture(txt_texteExit, NULL, NULL, &(dest_textExit.w), &(dest_textExit.h));
	SDL_QueryTexture(txt_texteRest, NULL, NULL, &(dest_textRest.w), &(dest_textRest.h));
	SDL_QueryTexture(txt_texteTurn, NULL, NULL, &(dest_textTurn.w), &(dest_textTurn.h));
	SDL_QueryTexture(txt_texteFouille, NULL, NULL, &(dest_textFouille.w), &(dest_textFouille.h));
	SDL_QueryTexture(txt_texteInv, NULL, NULL, &(dest_textInv.w), &(dest_textInv.h));

  if( ecran ){
    int running = 1;
		while(running) {
			SDL_Event event;
			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_WINDOWEVENT:
						switch(event.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_SHOWN:

				    SDL_RenderClear(renderer);

						/* affichage rectanglez verticale */
						SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
						SDL_RenderFillRect(renderer,&rect1);
						/* affichage rectangle horizontal */
						SDL_SetRenderDrawColor(renderer, 100, 90, 90, 255);
						SDL_RenderFillRect(renderer,&rect2);
						/* texte dans les boutons */
						SDL_RenderCopy(renderer, txt_texteHelp, NULL, &dest_textHelp);
						SDL_RenderCopy(renderer, txt_texteExit, NULL, &dest_textExit);
						SDL_RenderCopy(renderer, txt_texteRest, NULL, &dest_textRest);
						SDL_RenderCopy(renderer, txt_texteTurn, NULL, &dest_textTurn);
						SDL_RenderCopy(renderer, txt_texteFouille, NULL, &dest_textFouille);
						SDL_RenderCopy(renderer, txt_texteInv, NULL, &dest_textInv);
						/* les boutons */
						SDL_SetRenderDrawColor(renderer,200,200,200,255);
						SDL_RenderDrawRect(renderer,&bouton_exit);
						SDL_RenderDrawRect(renderer,&bouton_help);
						SDL_RenderDrawRect(renderer,&bouton_rest);
						SDL_RenderDrawRect(renderer,&bouton_turn);
						SDL_RenderDrawRect(renderer,&bouton_fouille);
						SDL_RenderDrawRect(renderer,&bouton_inv);
						/* couleur du reste de la fenetre */
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						/*affichage de la carte */
						affichage_map(&renderer, map);

						SDL_RenderPresent(renderer);

							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT){
							//si clique sur 1 des 2 grands boutons
							if (event.button.x > bouton_exit.x && event.button.x < bouton_exit.x+bouton_exit.w){
								//on regarde maintenant la hauteur du click afin de savoir sur quel bouton l'utilisateur a appuyé
								if (event.button.y > bouton_exit.y && event.button.y < bouton_exit.y+bouton_exit.h){
									running = 0;
								}
								if (event.button.y > bouton_help.y && event.button.y < bouton_help.y+bouton_help.h){
									affichage_help();
								}
							}
							//si on clique sur un des 4 autres boutons
							if(event.button.x > bouton_rest.x && event.button.x < bouton_rest.x+bouton_rest.w && event.button.y > bouton_rest.y && event.button.y < bouton_rest.y+bouton_rest.h){
								printf("rest & heal button pressed\n");
							}
							if(event.button.x > bouton_turn.x && event.button.x < bouton_turn.x+bouton_turn.w && event.button.y > bouton_turn.y && event.button.y < bouton_turn.y+bouton_turn.h){
								printf("end turn button pressed\n");
							}
							if(event.button.x > bouton_fouille.x && event.button.x < bouton_fouille.x+bouton_fouille.w && event.button.y > bouton_fouille.y && event.button.y < bouton_fouille.y+bouton_fouille.h){
								printf("search button pressed\n");
								combat_bis(police2);
							}
							if(event.button.x > bouton_inv.x && event.button.x < bouton_inv.x+bouton_inv.w && event.button.y > bouton_inv.y && event.button.y < bouton_inv.y+bouton_inv.h){
								printf("inventory button pressed\n");
							}
					}
					break;
				}
			}
		}
  }
  else {
    fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
  }


  /****************************************************************************
  ***                         Destruction de la fenetre                     ***
  ****************************************************************************/
  SDL_DestroyWindow(ecran);

	TTF_CloseFont(police1); /* Doit être avant TTF_Quit() */
	TTF_Quit();
  SDL_Quit();
	return 0;
}

int main(){
	srand(time(NULL));
	interface();
}
