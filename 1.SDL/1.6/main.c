#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <stdio.h>
#define TEMPO_UPDATE 100

SDL_Texture* AUX_CriarTexto(SDL_Renderer* ren,TTF_Font* fnt,char* str,SDL_Color clr){
    SDL_Surface* sfc = TTF_RenderText_Blended(fnt, str, clr);
    assert(sfc != NULL);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(ren, sfc);
    assert(txt != NULL);
    SDL_FreeSurface(sfc);
    return txt;
}

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
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("1.6",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    //carregar fontes
    TTF_Font* fnt = TTF_OpenFont("1.SDL\\1.6\\tiny.ttf", 20);//colocar 
    assert(fnt != NULL);
    SDL_Color c1 = {0x00,0x00,0xff,0x00};
    SDL_Color c2 = {0x00,0xff,0x00,0x00};
    SDL_Color c3 = {0xff,0x00,0x00,0x00};
    SDL_Texture* txt1 = AUX_CriarTexto(ren,fnt,"Azul Venceu",c1);
    SDL_Texture* txt2 = AUX_CriarTexto(ren,fnt,"Verde Venceu",c2);
    SDL_Texture* txt3 = AUX_CriarTexto(ren,fnt,"Vermelho  Venceu",c3);

    /* EXECUÇÃO */
    SDL_Rect r1 = {0,0,10,10};//tempo - azul
    SDL_Rect r2 = {0,45,10,10};//teclado - verde
    SDL_Rect r3 = {0,90,10,10};//mouse - vermelho
    Uint32 tempo_ultimo = 0;
    int ydir = 1,xdir = 1;
    Uint32 estado_1 = 0,estado_2 = 0,estado_3 = 0,pos = 1, game_state = 1,espera = TEMPO_UPDATE, winner = 0, tempo_inicial;
    while (game_state) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);//linha de chegada
        SDL_RenderDrawLine(ren,190,0,190,200);
        
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);//b
        SDL_RenderFillRect(ren,&r1);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);//g
        SDL_RenderFillRect(ren,&r2);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);//r
        SDL_RenderFillRect(ren,&r3);

        SDL_Event evt;
        SDL_Rect rt = {50,25,100,50};
        
        switch(game_state){
        	case 1://estado 1
        		if(AUX_WaitEventTimeoutCount(&evt, &espera)){
        			if (evt.type == SDL_KEYDOWN) {//retângulo 2 - teclado
                			switch (evt.key.keysym.sym) {
                    				case SDLK_LEFT:
                    					if(r2.x - 5 >= 0 && !estado_2)r2.x -= 5;break;
                    				case SDLK_RIGHT:
                    					if (r2.x + r2.w + 5 <=200 && !estado_2)r2.x += 5;break;
                			}
            			}
            			else if(evt.type == SDL_MOUSEMOTION){
            				if(!estado_3)r3.x = evt.motion.x;
	    			}
	    			else if(evt.type == SDL_QUIT) game_state  = 0;//permite fechar a janela
        		}
        		else if(!estado_1)r1.x += 5;
			
				if(r1.x >= 190 && !estado_1)estado_1 = pos++;
        		if(r2.x >= 190 && !estado_2)estado_2 = pos++;
        		if(r3.x >= 190 && !estado_3)estado_3 = pos++;
        		if(estado_1 && estado_2 && estado_3){
					pos = 1;
					winner = (estado_1 < estado_2 && estado_1 < estado_3)? 1: ((estado_2 < estado_3)? 2: 3);
					game_state = 2;
				}
        		break;
        	case 2:{
        		if (winner == 1)SDL_RenderCopy(ren,txt1,NULL,&rt);
        		if (winner == 2)SDL_RenderCopy(ren,txt2,NULL,&rt);
        		if (winner == 3)SDL_RenderCopy(ren,txt3,NULL,&rt);
        		
        		if(AUX_WaitEventTimeoutCount(&evt, &espera)){
        			if(evt.type == SDL_QUIT)game_state = 0;
        		}
        		else{
        			game_state = 1;//reinicia
        			r1.x = r2.x = r3.x = estado_1 = estado_2 = estado_3 = winner = 0;
        			pos = 1;
				}
        	
        		break;
        	}
        }

    	SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(txt3);
    SDL_DestroyTexture(txt2);
    SDL_DestroyTexture(txt1);
    TTF_CloseFont(fnt);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}
