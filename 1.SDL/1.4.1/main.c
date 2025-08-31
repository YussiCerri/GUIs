#include <SDL2/SDL.h>
#include<stdlib.h>

typedef struct Y_Rect{
	SDL_Rect rec;
	Uint8 r,g,b,a;
}Y_Rect;


int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    Y_Rect R[10];
    int qtd_rect = 0,i_edit = 0;

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        
        for(int i = 0; i < qtd_rect; i++){//retângulos fixos
		SDL_SetRenderDrawColor(ren,R[i].r,R[i].g,R[i].b,R[i].a);
		SDL_RenderFillRect(ren,&R[i].rec);
	}
	
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);//Retângulo que se move
        SDL_RenderFillRect(ren, &r);
        
        
        
        
        
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {//limita movimento
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    if(r.y - 5 >= 0)r.y -= 5;
                    break;
                case SDLK_DOWN:
                    if(r.y + r.h + 5 <= 100)r.y += 5;
                    break;
                case SDLK_LEFT:
                    if(r.x - 5 >= 0)r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    if(r.x + r.w + 5 <= 200)r.x += 5;
                    break;
            }
        }
        else if(evt.type == SDL_QUIT){//sai quando aperta x ou Alt-f4
        	break;
        }
        else if(evt.type == SDL_MOUSEBUTTONDOWN){
        	if (qtd_rect < 10) qtd_rect++;
        	//else continue;
        	R[i_edit].rec.x = evt.button.x;
        	R[i_edit].rec.y = evt.button.y;
        	R[i_edit].rec.h = rand()%(100-evt.button.y-1)+1;
        	R[i_edit].rec.w = rand()%(200-evt.button.x-1)+1;
        	R[i_edit].r = rand()%256;
        	R[i_edit].g = rand()%256;
        	R[i_edit].b = rand()%256;
        	R[i_edit].a = 0x00;
        
		i_edit = (i_edit+1)%10;
	}
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
