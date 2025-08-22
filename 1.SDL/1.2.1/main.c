#include <SDL2/SDL.h>

void Y_drawRect(SDL_Renderer* ren, float x, float y, float w, float h){
	SDL_FRect r = {x,y,w,h};
	SDL_RenderFillRectF(ren,&r);
}
void Y_drawHead(SDL_Renderer* ren,float x, float y){
	SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);//preto
	Y_drawRect(ren,x+0,y+0,2,2);
	Y_drawRect(ren,x+6,y+0,2,2);
	Y_drawRect(ren,x+2,y+2,4,4);
	
	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xff,0x00);//branco
	Y_drawRect(ren,x+2.5,y+2.5,1,1.5);
	Y_drawRect(ren,x+4.5,y+2.5,1,1.5);
	
	SDL_SetRenderDrawColor(ren,0xAA,0xAA,0xAA,0x00);//cinza
	Y_drawRect(ren,x+2.5,y+2.5,1.0,1.0);
	Y_drawRect(ren,x+4.5,y+2.5,1.0,1.0);
	Y_drawRect(ren,x+3.0,y+4.0,4.0,2.0);
	
	SDL_SetRenderDrawColor(ren,0xFF,0x00,0x00,0x00);//vermelho
	Y_drawRect(ren,x+3.25,y+3.75,0.25,0.25);
	Y_drawRect(ren,x+5.25,y+3.75,0.25,0.25);
	Y_drawRect(ren,x+7.0 ,y+3.5 ,0.5 ,0.5 );
}

void Y_drawMick(SDL_Renderer* ren){
	SDL_RenderSetScale(ren,10,10);//aumenta a escala
	Y_drawHead(ren,0,2);//desenha cabeça
	SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);
	Y_drawRect(ren,2.5,8,3,10);//desenha corpo

	SDL_RenderSetScale(ren,1,1);
	SDL_RenderDrawLineF(ren,40 ,70,70 ,70);
}

void Y_drawBackground(SDL_Renderer* ren){
	SDL_SetRenderDrawColor(ren, 0xbb,0xbb,0xFF,0x00);//ceu, também limpa o fundo
    SDL_RenderClear(ren);
	
	SDL_SetRenderDrawColor(ren,0xff,0xff,0x00,0x00);//sol preenchimento
	Y_drawRect(ren,150,10,25,25);
	SDL_SetRenderDrawColor(ren,0xff,0x88,0x00,0x00);
	SDL_FRect r = {150,10,25,25};
	SDL_RenderDrawRectF(ren,&r);//sol contorno
	SDL_RenderDrawLine(ren,150,10,0,0);//raios solares
	SDL_RenderDrawLine(ren,150,35,0,100);
	SDL_RenderDrawLine(ren,175,35,200,100);
	SDL_RenderDrawLine(ren,175,10,200,0);
	
	SDL_SetRenderDrawColor(ren,0xaa,0xaa,0x00,0x00);//areia	
	Y_drawRect(ren,0,60,200,40);
	
	SDL_SetRenderDrawColor(ren,0x11,0x11,0x11,0x00);//detalhes na areia (0 -> 200, 60 -> 100)
	SDL_RenderDrawPoint(ren,10,80);
	SDL_RenderDrawPoint(ren,50,90);
	SDL_RenderDrawPoint(ren,150,70);
	SDL_RenderDrawPoint(ren,145,75);
	SDL_RenderDrawPoint(ren,180,95);
	SDL_RenderDrawPoint(ren,130,65);
	SDL_RenderDrawPoint(ren,20,97);
	SDL_RenderDrawPoint(ren,60,88);
	SDL_RenderDrawPoint(ren,100,68);
	SDL_RenderDrawPoint(ren,110,73);
	SDL_RenderDrawPoint(ren,121,89);
	SDL_RenderDrawPoint(ren,80,77);
	
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.2.1",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    Y_drawBackground(ren);
    Y_drawMick(ren);
    
    SDL_RenderPresent(ren);
    SDL_Delay(10000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
