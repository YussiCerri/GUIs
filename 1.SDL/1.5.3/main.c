#include <SDL2/SDL.h>
#define TEMPO_UPDATE 100

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	int temEvento = SDL_WaitEventTimeout(evt,*ms);
	(*ms) = (temEvento)?(*ms)-(SDL_GetTicks()-antes):TEMPO_UPDATE;
	return temEvento;
}

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
#define SCALEMICK 10
void Y_drawMick(SDL_Renderer* ren, float x , float y){
	x /=SCALEMICK;y /=SCALEMICK;//ajusta as posções para somente se mover 1 pixel a cada 100ms
	
	SDL_RenderSetScale(ren,SCALEMICK,SCALEMICK);
	Y_drawHead(ren,x,y+2);//a cabeça é iniciada no ponto (0,2) no inicio do loop e movimentada de acordo com x e y
	SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);
	Y_drawRect(ren,x+2.5,y+8,3,5);//o corpo começa em (2.5,8) e se move de acordo com x e y

	SDL_RenderSetScale(ren,1,1);
	SDL_RenderDrawLineF(ren,SCALEMICK*(x+4),SCALEMICK*(7+y),SCALEMICK*(7+x),SCALEMICK*(y+7));//a boca vai do ponto 
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
    SDL_Window* win = SDL_CreateWindow("1.5.3",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */

    int t = 0, x = 0, y = 0,r_dir = 1, ms = TEMPO_UPDATE, flag = 1;
    SDL_Event evt;
    /*while( t < 240){//executa o loop 6 vezes
    	//A partir de um ponto (x,y) que se move em sentido horário pelos eixos x e y, é movido o personagem de acordo com o mesmo movimento
    	if(t%40 < 10) x++;//move-se 10 vezes para direita inicialmente
    	else if(t%40 < 20)y++;//10 vezes para baixo
    	else if(t%40 < 30)x--;//10 vezes para a esquerda
    	else y --;//10 vezes para cima, reinicia o loop
    	
    	Y_drawBackground(ren);
    	Y_drawMick(ren,x,y);//função que controla o desenho do personagem
    	t++;
    	SDL_Delay(100);//1 pixel em 100ms --> 10 pixels em 1 s
    	SDL_RenderPresent(ren);
    }*/
    while(flag){
    	if(AUX_WaitEventTimeoutCount(&evt,&ms)){
    		switch(evt.type){
    			case SDL_QUIT:
    				flag = 0;
    				break;
    			case SDL_KEYDOWN:
    				switch(evt.key.keysym.sym){
    					case SDLK_RIGHT: x++;break;//move para direita
    					case SDLK_LEFT : x--;break;//move para esquerda
    					case SDLK_UP: r_dir = - r_dir;break;//muda o sentido que roda a cabeça
					}
    				break;
			}
		}else{
			Y_drawBackground(ren);
    		Y_drawMick(ren,x,y);//função que controla o desenho do personagem
			t = (t+r_dir+40)%40;
			
			if(t%40 < 10) x += r_dir;//move-se 10 vezes para direita inicialmente
    		else if(t%40 < 20)y += r_dir;//10 vezes para baixo
    		else if(t%40 < 30)x-= r_dir;//10 vezes para a esquerda
    		else y -= r_dir;//10 vezes para cima, reinicia o loop
			
			SDL_RenderPresent(ren);
		}
	}
    
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
