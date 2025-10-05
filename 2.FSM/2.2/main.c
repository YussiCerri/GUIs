#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	int temEvento = SDL_WaitEventTimeout(evt,*ms);
	(*ms) -= (SDL_GetTicks() - antes);
	if((*ms)>1000)(*ms)=0;//evita underflow
	return temEvento;
}

typedef struct{
	SDL_bool press;//está arrastando
	SDL_bool drag;
	SDL_Rect orig;//copia do retângulo original
	SDL_Rect* r;//ponteiro para o retângulo a ser arrastado
	SDL_Point p;
}YCF_Arrasta;

int main(int argc, char* args[]){
	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("2.2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000, 700, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    SDL_Event evt;
    SDL_bool rodando = SDL_TRUE;
    Uint32 espera = 10;
    YCF_Arrasta aux = {SDL_FALSE,SDL_FALSE,(SDL_Rect){0,0,0,0},NULL};
    SDL_Rect P[5] = {{0,0,50,50},{600,100,50,100},{100,100,100,50},{200,200,25,25},{700,600,20,20}};
    
	while(rodando){
		SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);
		SDL_RenderClear(ren);
		
		
		if(AUX_WaitEventTimeoutCount(&evt,&espera)){
			switch(evt.type){
				case SDL_QUIT://para sair sem matar o processo
					rodando = SDL_FALSE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					aux.p = (SDL_Point){evt.button.x,evt.button.y};
					if(!aux.press){
						for(int i = 0; i < 5; i++){
							if(aux.press = SDL_PointInRect(&aux.p,&P[i])){
								aux.r = &P[i];
								aux.orig = P[i];
								break;
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					aux.press = SDL_FALSE;
					aux.drag =  SDL_FALSE;
					aux.r = NULL;
					break;
				case SDL_MOUSEMOTION:
					if(aux.press){
						aux.drag = SDL_TRUE;
						(*aux.r).x += evt.motion.xrel;
						(*aux.r).y += evt.motion.yrel;
					}
					break;
				case SDL_KEYDOWN:
					if(evt.key.keysym.sym == SDLK_ESCAPE && aux.drag){
						aux.drag =  SDL_FALSE;
						*(aux.r) = aux.orig;//restaura o retângulo em sua forma original
					}
					break;
			}
		}else espera = 10;
		SDL_SetRenderDrawColor(ren,0xff,0x00,0x00,0x00);
		for(int i = 0; i < 5; i++)SDL_RenderFillRect(ren,&P[i]);
		SDL_RenderPresent(ren);
	}
	
	
	SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
	return 0;
}