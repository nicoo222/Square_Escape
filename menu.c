#include "menu.h"

void loadMenu(Menu *pMenu, Screen *pScreen){
	SDL_Surface * start;
	SDL_Surface * option;
	SDL_Surface * quit;
	SDL_Surface * selection;
	SDL_Surface * sounds;
	SDL_Surface * background;
	SDL_Surface * bgGrey;
	SDL_Surface * bgSea;
	SDL_Surface * on;
	SDL_Surface * off;
	SDL_Surface * bgSpace;
	
	
	start = SDL_LoadBMP("Pictures/StartOff.bmp");
	option = SDL_LoadBMP("Pictures/Option.bmp");
	quit = SDL_LoadBMP("Pictures/QuitOff.bmp");
	selection = SDL_LoadBMP("Pictures/Selection.bmp");
	sounds = SDL_LoadBMP("Pictures/Sounds.bmp");
	on = SDL_LoadBMP("Pictures/On.bmp");
	off = SDL_LoadBMP("Pictures/Off.bmp");
	background = SDL_LoadBMP("Pictures/BackGround.bmp");
	bgSpace = SDL_LoadBMP("Pictures/Grey.bmp");
	bgSea = SDL_LoadBMP("Pictures/BGsea.bmp");
	bgGrey = SDL_LoadBMP("Pictures/BGgrey.bmp");

	int h = 52;
	int w = 150;
	int *ph = &h;
	int *pw = &w;	
	
	if (start == NULL){
		fprintf(stderr,"Erreur chargement de l'image StartOn\n");
		exit(1);
	}
	if (option == NULL){
		fprintf(stderr,"Erreur chargement de l'image Option\n");
		exit(1);
	}
	if (quit == NULL){
		fprintf(stderr,"Erreur chargement de l'image QuitOn\n");
		exit(1);
	}
	if (selection == NULL){
		fprintf(stderr,"Erreur chargement de l'image Selection\n");
		exit(1);
	}
	if (sounds == NULL){
		fprintf(stderr,"Erreur chargement de l'image Sounds\n");
		exit(1);
	}
	if (background == NULL){
		fprintf(stderr,"Erreur chargement de l'image BackGround\n");
		exit(1);
	}
	if (bgGrey == NULL){
		fprintf(stderr,"Erreur chargement de l'image Grey\n");
		exit(1);
	}
	if (bgSea == NULL){
		fprintf(stderr,"Erreur chargement de l'image Sea\n");
		exit(1);
	}
	if (on == NULL){
		fprintf(stderr,"Erreur chargement de l'image On\n");
		exit(1);
	}
	if (off == NULL){
		fprintf(stderr,"Erreur chargement de l'image Off\n");
		exit(1);
	}
	//Mise en place des Render
	pMenu->Start=SDL_CreateTextureFromSurface(pScreen->renderer,start);
	SDL_QueryTexture(pMenu->Start, NULL, NULL, &(pMenu->ButtonPos[0].w), &(pMenu->ButtonPos[0].h));

	pMenu->Option=SDL_CreateTextureFromSurface(pScreen->renderer,option);
	SDL_QueryTexture(pMenu->Option, NULL, NULL, &(pMenu->ButtonPos[1].w), &(pMenu->ButtonPos[1].h));
	
	pMenu->Quit=SDL_CreateTextureFromSurface(pScreen->renderer,quit);
	SDL_QueryTexture(pMenu->Quit, NULL, NULL, &(pMenu->ButtonPos[2].w), &(pMenu->ButtonPos[2].h));

	pMenu->Selection=SDL_CreateTextureFromSurface(pScreen->renderer,selection);
	SDL_QueryTexture(pMenu->Selection, NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));

	pMenu->Sounds=SDL_CreateTextureFromSurface(pScreen->renderer,sounds);
	SDL_QueryTexture(pMenu->Sounds, NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));

	pMenu->BackGround=SDL_CreateTextureFromSurface(pScreen->renderer,background);
	SDL_QueryTexture(pMenu->BackGround, NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));

	pMenu->OnOff[0]=SDL_CreateTextureFromSurface(pScreen->renderer,on);
	SDL_QueryTexture(pMenu->OnOff[0], NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));

	pMenu->OnOff[1]=SDL_CreateTextureFromSurface(pScreen->renderer,off);
	SDL_QueryTexture(pMenu->OnOff[1], NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));

	pMenu->BackGround=SDL_CreateTextureFromSurface(pScreen->renderer,background);
	SDL_QueryTexture(pMenu->BackGround, NULL, NULL, &(pMenu->ButtonPos[3].w), &(pMenu->ButtonPos[3].h));
	
	pMenu->menuBG=SDL_CreateTextureFromSurface(pScreen->renderer,bgGrey);

	pMenu->BgChoice[0]=SDL_CreateTextureFromSurface(pScreen->renderer,bgGrey);
	SDL_QueryTexture(pMenu->BgChoice[0], NULL, NULL, pw, ph);

	pMenu->BgChoice[1]=SDL_CreateTextureFromSurface(pScreen->renderer,bgSea);
	SDL_QueryTexture(pMenu->BgChoice[1], NULL, NULL, pw, ph);

	//Position des boutons
	
	pMenu->ButtonPos[3].w = 50;
	
	pMenu->ButtonPos[0].x = 350;
	pMenu->ButtonPos[0].y = 250;
	pMenu->ButtonPos[1].x = 350;
	pMenu->ButtonPos[1].y = 350;
	pMenu->ButtonPos[2].x = 350;
	pMenu->ButtonPos[2].y = 450;
	pMenu->ButtonPos[3].x = 259;	
	pMenu->ButtonPos[3].y = 250;
	pMenu->ButtonPos[4].x = 447;
	pMenu->ButtonPos[4].y = 250;
	pMenu->ButtonPos[5].x = 528;
	pMenu->ButtonPos[5].y = 350;
	
	pMenu->menuBGRec.x = 0;
	pMenu->menuBGRec.y = 0;
	pMenu->menuBGRec.h = SCREEN_HEIGHT;
	pMenu->menuBGRec.w = SCREEN_WIDTH;
}

void updateScreenMenu(Menu *pMenu, Screen *pScreen, GameState *pGamestate){
	
	//On efface le contenu de l'écran
	SDL_RenderClear(pScreen->renderer);
	
	//On ajoute les versions des sprites du menu
	if (pGamestate-> menu ==1) {
		SDL_RenderCopy(pScreen->renderer,pMenu->menuBG,NULL,&pMenu->menuBGRec);
		SDL_RenderCopy(pScreen->renderer,pMenu->Start,NULL,&(pMenu->ButtonPos[0]));
		SDL_RenderCopy(pScreen->renderer,pMenu->Quit,NULL,&(pMenu->ButtonPos[2]));
		SDL_RenderCopy(pScreen->renderer,pMenu->Option,NULL,&(pMenu->ButtonPos[1]));
		pMenu->ButtonPos[3].x = 259;
		
		if (pGamestate -> choice == 0){
			pMenu->ButtonPos[3].y = 250;
			SDL_RenderCopy(pScreen->renderer,pMenu->Selection,NULL,&(pMenu->ButtonPos[3]));
		}
		if (pGamestate -> choice == 1){
			pMenu->ButtonPos[3].y = 350;
			SDL_RenderCopy(pScreen->renderer,pMenu->Selection,NULL,&(pMenu->ButtonPos[3]));	
		}
		if (pGamestate -> choice == 2){
			pMenu->ButtonPos[3].y = 450;
			SDL_RenderCopy(pScreen->renderer,pMenu->Selection,NULL,&(pMenu->ButtonPos[3]));
		}
	}
	if (pGamestate->menu == 2){
		SDL_RenderCopy(pScreen->renderer,pMenu->menuBG,NULL,&pMenu->menuBGRec);
		SDL_RenderCopy(pScreen->renderer,pMenu->Sounds,NULL,&(pMenu->ButtonPos[0]));
		SDL_RenderCopy(pScreen->renderer,pMenu->BackGround,NULL,&(pMenu->ButtonPos[1]));
		if (pGamestate -> choice == 0){
			pMenu->ButtonPos[3].x = 257;
			pMenu->ButtonPos[3].y = 250;
			SDL_RenderCopy(pScreen->renderer,pMenu->Selection,NULL,&(pMenu->ButtonPos[3]));
		}
		if (pGamestate -> sChoice == 0){
			SDL_RenderCopy(pScreen->renderer,pMenu->OnOff[0],NULL,&(pMenu->ButtonPos[4]));
		}
		else { SDL_RenderCopy(pScreen->renderer,pMenu->OnOff[1],NULL,&(pMenu->ButtonPos[4]));
		}
		if (pGamestate -> choice == 1){
			pMenu->ButtonPos[3].x = 218;
			pMenu->ButtonPos[3].y = 350;			
			SDL_RenderCopy(pScreen->renderer,pMenu->Selection,NULL,&(pMenu->ButtonPos[3]));
		}
		if (pGamestate->bgChoice == 0){
			SDL_RenderCopy(pScreen->renderer, pMenu->BgChoice[0],NULL,&(pMenu->ButtonPos[5]));
		}
		else { SDL_RenderCopy(pScreen->renderer, pMenu->BgChoice[1],NULL,&(pMenu->ButtonPos[5]));
		}

	}
	
	//On réaffiche le tout 
	SDL_RenderPresent(pScreen->renderer);
}
