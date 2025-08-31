#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animacao Simples",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    while (r.x < 100) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);//O Buffer 1(atualmente back) é pintado de branco e apresentado
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);//troca os Buffers 1 e 2
        SDL_Delay(100);//adicionado para visualizar o bug
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);//No Buffer 2 é pintado o retângulo azul
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);//O buffer 2 é exibido e o buffer 1 volta para o back
        SDL_Delay(100);//adicionado para visualizar o bug
        r.x += 2;
        r.y += 2;
        /*
		Como o retângulo só está no buffer 2, 
		nos momentos de renderizar os buffers 1 e 2 pisca entre um frame sem o retângulo e um frame com o retângulo
		*/
    }
    SDL_Delay(2000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
