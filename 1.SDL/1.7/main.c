#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#define TEMPO_UPDATE 100

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	int temEvento = SDL_WaitEventTimeout(evt,*ms);
	(*ms) = (temEvento)?(*ms)-(SDL_GetTicks()-antes):TEMPO_UPDATE;
	(*ms) = ((*ms) > TEMPO_UPDATE)?TEMPO_UPDATE:(*ms);
	return temEvento;
}

void Y_drawRect(SDL_Renderer* ren, float x, float y, float w, float h){
	SDL_FRect r = {x,y,w,h};
	SDL_RenderFillRectF(ren,&r);
}

void Y_drawHead(SDL_Renderer* ren,float x, float y){
	
	
	
	
	/*SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);//preto
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
	Y_drawRect(ren,x+7.0 ,y+3.5 ,0.5 ,0.5 );*/
}
#define SCALEMICK 10
void Y_drawMick(SDL_Renderer* ren,SDL_Texture* img_head,SDL_Texture* img_body, float x , float y, int t){
	SDL_Rect r_head = {x,y,80,60}, c_head = {80*((t/2)%5),0,80,60};
	SDL_Rect r_body = {x+25,y+55,30,50}, c_body = {30*((t/4)%2),0,30,50};//alterar c_body quando o corpo estiver feito
	
	SDL_RenderCopy(ren,img_body,&c_body,&r_body);
	SDL_RenderCopy(ren,img_head,&c_head,&r_head);
	
	/*x /=SCALEMICK;y /=SCALEMICK;//ajusta as posções para somente se mover 1 pixel a cada 100ms
	
	SDL_RenderSetScale(ren,SCALEMICK,SCALEMICK);
	Y_drawHead(ren,x,y+2);//a cabeça é iniciada no ponto (0,2) no inicio do loop e movimentada de acordo com x e y
	SDL_SetRenderDrawColor(ren,0x00,0x00,0x00,0x00);
	Y_drawRect(ren,x+2.5,y+8,3,5);//o corpo começa em (2.5,8) e se move de acordo com x e y

	SDL_RenderSetScale(ren,1,1);
	SDL_RenderDrawLineF(ren,SCALEMICK*(x+4),SCALEMICK*(7+y),SCALEMICK*(7+x),SCALEMICK*(y+7));//a boca vai do ponto */
}

void Y_drawBackground(SDL_Renderer* ren,SDL_Texture* img_Areia,SDL_Texture* img_Sol, int t){
	SDL_Rect r_sol = {150,0 ,40,40}, c_sol = {0,0,40,40};
	SDL_Rect r_are = {0,60,200 ,40} , c_are = {0 + 200*((t/5)%2),0,200,40};
	
	SDL_SetRenderDrawColor(ren, 0xbb,0xbb,0xFF,0x00);//ceu, também limpa o fundo
    SDL_RenderClear(ren);
	
	SDL_RenderCopy(ren,img_Sol,&c_sol,&r_sol);
	SDL_RenderCopy(ren,img_Areia,&c_are,&r_are);
	/*SDL_SetRenderDrawColor(ren, 0xbb,0xbb,0xFF,0x00);//ceu, também limpa o fundo
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
	SDL_RenderDrawPoint(ren,80,77);*/
	
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("1.7",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img1 = IMG_LoadTexture(ren,"1.SDL\\1.7\\Mick.png");//carrega cabeça de Mick o rato
    assert(img1 != NULL);
    SDL_Texture* img2 = IMG_LoadTexture(ren,"1.SDL\\1.7\\Areia.png");//carrega a areia
    assert(img2 != NULL);
    SDL_Texture* img3 = IMG_LoadTexture(ren,"1.SDL\\1.7\\Sol.png");//carrega o sol
    assert(img3 != NULL);
    SDL_Texture* img4 = IMG_LoadTexture(ren,"1.SDL\\1.7\\Body.png");//carrega o corpo
    assert(img4 != NULL);

    /* EXECUÇÃO */

    int t = 0, x = 0, y = 0,r_dir = 1, ms = TEMPO_UPDATE, flag = 1;
    
    SDL_Event evt;
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
			Y_drawBackground(ren,img2,img3,t);
			//Y_drawBackground(ren);
    		Y_drawMick(ren,img1,img4,x,y,t);//função que controla o desenho do personagem
			t = (t+r_dir+40)%40;
			
			if(t%40 < 10) x += r_dir;//move-se 10 vezes para direita inicialmente
    		else if(t%40 < 20)y += r_dir;//10 vezes para baixo
    		else if(t%40 < 30)x-= r_dir;//10 vezes para a esquerda
    		else y -= r_dir;//10 vezes para cima, reinicia o loop
			
			SDL_RenderPresent(ren);
		}
	}
    
    /* FINALIZACAO */
    SDL_DestroyTexture(img4);
    SDL_DestroyTexture(img3);
    SDL_DestroyTexture(img2);
    SDL_DestroyTexture(img1);
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
