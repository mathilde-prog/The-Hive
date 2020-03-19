#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"interface.h"

char *map[N*N];
/*
 * fonction de test qui permet de tester l'affichage de la map avec une version d'essais, simplifiée
 */
void init_map_essai(int mapint[N][N]){
	int i,j;
	for(i=0;i<N;i++){
		for (j=0;j<N;j++)
		 if (i%2 && j%2)
			 mapint[i][j]=1;
		 else if(!j%2)
			 mapint[i][j]=3;
		 else
			 mapint[i][j]=2;
 	}
}


/*
 * fonction qui remplit map des chaines de caracteres correspondants à l'image a affiché
 */
void relation_hexa_char(char*mapchar[], int mapint[N][N]){
	int i,j,k=0;
	for (i=0; i<N;i++){
		for (j=0; j<N;j++){
			switch(mapint[i][j]){
				case 1 : mapchar[k]="hexa_png/hex_forest2.png";k++;break;
				case 2 : mapchar[k]="hexa_png/hex_city1.png";k++;break;
				case 3 : mapchar[k]="hexa_png/hex_lake1.png";k++;break;
				case 4 : mapchar[k]="hexa_png/hex_military_base.png";k++;break;
				case 5 : mapchar[k]="hexa_png/hex_bandit_camp.png";k++;break;
				case 6 : mapchar[k]="hexa_png/hex_market.png";k++;break;
				case 7 : mapchar[k]="hexa_png/hex_favella.png";k++;break;
				case 8 : mapchar[k]="hexa_png/hex_mountains.png";k++;break;
				case 9 : mapchar[k]="hexa_png/hex_border.png";k++;break;
				case 10 : mapchar[k]="hexa_png/hex_sea.png";k++;break;
				case 11 : mapchar[k]="hexa_png/hex_wasteland1.png";k++;break;
				default : mapchar[k]="hexa_png/HexBlankDay.png";k++;
			}
		}
	}
}

/*
 * fonction qui affiche uniquement la map c'est a dire la partie composée d'hexagones
 * collés les uns aux autres
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
}

/*
 * fonction qui affiche l'interface
 */
int interface(){
  //Le pointeur vers la fenetre
	SDL_Window* ecran = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
  SDL_Surface *texte_help=NULL, *texte_exit=NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect rect1 = {0,0,400,800};
	SDL_Rect rect2 = {400,600,1100,200};
	SDL_Rect bouton_help = {5,605,390,90};
	SDL_Rect bouton_exit = {5,705,390,90};
	SDL_Rect dest_textHelp = bouton_help, dest_textExit = bouton_exit;

	// Le pointeur vers notre police
	TTF_Font *police = NULL;
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
	ecran = SDL_CreateWindow("The Hive",SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,1500,800, SDL_WINDOW_SHOWN);
	/* icone de la fenetre */
	SDL_Surface *icon=NULL;
	SDL_RWops *icon_rwop=NULL;
	icon_rwop=SDL_RWFromFile("img/ItmEncMergaLoupe.png","rb");
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
	if( (police = TTF_OpenFont("Menlo-Regular.ttf", 55)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}

	/* creation des textures pour afficher le texte */
	texte_help = TTF_RenderUTF8_Blended(police, " Help", couleurVerte);
	texte_exit = TTF_RenderUTF8_Blended(police, " Exit",couleurVerte);
	SDL_Texture *txt_texteHelp = SDL_CreateTextureFromSurface(renderer, texte_help);
	SDL_Texture *txt_texteExit = SDL_CreateTextureFromSurface(renderer, texte_exit);
	SDL_FreeSurface(texte_exit);
	SDL_FreeSurface(texte_help);
	SDL_QueryTexture(txt_texteHelp, NULL, NULL, &(dest_textHelp.w), &(dest_textHelp.h));
	SDL_QueryTexture(txt_texteExit, NULL, NULL, &(dest_textExit.w), &(dest_textExit.h));

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
						/* les boutons */
						SDL_SetRenderDrawColor(renderer,200,200,200,255);
						SDL_RenderDrawRect(renderer,&bouton_exit);
						SDL_RenderDrawRect(renderer,&bouton_help);
						/* couleur du reste de la fenetre */
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
						/*affichage de la carte */
						affichage_map(&renderer, map);

						SDL_RenderPresent(renderer);

							break;
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

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
  SDL_Quit();
	return 0;
}

int main(){
	interface();
}
