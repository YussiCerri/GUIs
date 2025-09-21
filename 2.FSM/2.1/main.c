#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	int temEvento = SDL_WaitEventTimeout(evt,*ms);
	(*ms)-= (SDL_GetTicks() - antes);
	return temEvento;
}

typedef struct ClickManager{
	Uint32 n;
	Uint32 tick1;
	Uint32 estado;
}ClickManager;
void AguardaClick(ClickManager* cm){
	cm->n = 1;
	cm->tick1 = SDL_GetTicks();
	cm->estado = 1;
}
void ColetaClick(ClickManager* cm){
	cm->n++;
}
void CliqueMultiplo(ClickManager* cm){
	switch(cm->estado){
		case 0:
			AguardaClick(cm);
			break;
		case 1:
			ColetaClick(cm);
			break;
	}
}
void VerificaTempoClick(ClickManager* cm){
	if (cm->n && SDL_GetTicks() - cm->tick1 > 250) {
            SDL_Event* evt = (SDL_Event*) malloc(sizeof(SDL_Event));//cria novo evento
            evt->type = SDL_USEREVENT;
			evt->user.code = cm->n;
            cm->estado = 0;
            cm->n = 0;
            SDL_PushEvent(evt);
    }
}
int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("2.1",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,200, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	
	SDL_Event evt;
	Uint32 espera = 50,jogo = 1;
	ClickManager cm = {0,0,0};
	SDL_Rect r = {0,50,0,10};
	while(jogo){
		VerificaTempoClick(&cm);
		if(espera > 50)espera = 0;//lida com underflow
		if(AUX_WaitEventTimeoutCount(&evt,&espera)){
			switch(evt.type){
				case SDL_QUIT:
					jogo = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					CliqueMultiplo(&cm);
					break;
				case SDL_USEREVENT://clique multiplo
					r.w = evt.user.code*20;
					break;
			}
		}else{
			SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        	SDL_RenderClear(ren);
        	SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
        	SDL_RenderFillRect(ren,&r);
			espera = 50;
			SDL_RenderPresent(ren);
		}
	}
	
	SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
	return 0;
}