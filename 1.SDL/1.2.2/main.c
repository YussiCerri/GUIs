#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[]){
	/* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.2.2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,200, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	
	
	
	
	
	
	SDL_SetRenderDrawColor(ren,0x00,0x00,0xff,0x00);
	SDL_RenderClear(ren);
	
	rectangleColor(ren,40,3,3,40,0xaabbffff);//Rectangle --> retangulo perimetro
	boxColor(ren,40,3,80,80,0xff0000ff);//Box --> retangulo Preenchido
	filledCircleColor(ren,100,50,15,0xffff00ff);//circulo com preenchimento
	circleColor(ren,100,50,30,0x000000ff);//nenhum desenho visivel
	filledEllipseColor(ren,100,75,30,10,0xff00ffff);//ellipse preenchida
	pieColor(ren,150,60,40,0,120,0xffff00ff);//Contorno 
	filledTrigonColor(ren,50,50,100,60,75,100,0xff00aa);//nenhum desenho visivel
	SDL_RenderPresent(ren);
	
	SDL_Delay(5000);
	
	/* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
	return 0;
}