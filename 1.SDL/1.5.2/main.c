#include <SDL2/SDL.h>
#define TEMPO_UPDATE 100

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	int temEvento = SDL_WaitEventTimeout(evt,*ms);
	(*ms) = (temEvento)?(*ms)-(SDL_GetTicks()-antes):TEMPO_UPDATE;
	(*ms) = (*ms > TEMPO_UPDATE)? TEMPO_UPDATE: *ms;//corrige subtrações com resultado abaixo de 0
	return temEvento;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.5.2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r1 = {0,0,10,10};//tempo - azul
    SDL_Rect r2 = {0,0,10,10};//teclado - verde
    SDL_Rect r3 = {0,0,10,10};//mouse - vermelho
    Uint32 tempo_ultimo = 0;
    int ydir = 1,xdir = 1;
    Uint32 espera = TEMPO_UPDATE;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);//b
        SDL_RenderFillRect(ren,&r1);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);//g
        SDL_RenderFillRect(ren,&r2);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);//r
        SDL_RenderFillRect(ren,&r3);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        int isevt = /*SDL_WaitEventTimeout(&evt, 500)*/AUX_WaitEventTimeoutCount(&evt,&espera);
        if (isevt) {
            if (evt.type == SDL_KEYDOWN) {//retângulo 2 - teclado
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:if (r2.y -5 >= 0)r2.y -= 5;break;
                    case SDLK_DOWN:if (r2.y+r2.h+5 <= 100)r2.y += 5;break;
                    case SDLK_LEFT:if(r2.x - 5 >= 0)r2.x -= 5;break;
                    case SDLK_RIGHT:if (r2.x + r2.w + 5 <=200)r2.x += 5;break;
                }
            }
            else if(evt.type == SDL_MOUSEMOTION){
            	r3.x = evt.motion.x;
            	r3.y = evt.motion.y;
	    }
	    else if(evt.type == SDL_QUIT) break;//permite fechar a janela
        }
        if (SDL_GetTicks() - tempo_ultimo >= 100){//a cada 0.1 segundos atualiza
        	if(xdir > 0 && r1.x+r1.w+xdir > 200) xdir = -xdir;
        	else if(r1.x+xdir < 0)xdir = -xdir;
        	if(ydir > 0 && r1.y+r1.h+ydir > 100) ydir = -ydir;
        	else if(r1.y+ydir < 0)ydir = -ydir;
        	r1.x += xdir;
        	r1.y += ydir;
        
        
        	tempo_ultimo = SDL_GetTicks();
        }
        
        
        
        
        
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
