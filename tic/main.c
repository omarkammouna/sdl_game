#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "main.h"


int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface* screen = SDL_SetVideoMode(300, 300, 32, SDL_SWSURFACE);
    TicTacToe t;
    initializeTic(&t);

    int continueGame = 1;
    int turn = 1;

    while (continueGame == 1) {
        displayTic(t, screen);

        if (t.round < 9 && whoIsWinner(t.tabfollow) == 0) {
            if (turn == 1) {
                calculateShot(t.tabfollow);
                t.round++;
                turn = -1;
            } else {
                SDL_Event event;
                SDL_WaitEvent(&event);
                if (event.type == SDL_MOUSEBUTTONUP) {
                    int x = event.button.x / (t.background->w / 3);
                    int y = event.button.y / (t.background->h / 3);
                    int shot = 3 * y + x;

                    if (t.tabfollow[shot] == 0) {
                        t.tabfollow[shot] = -1;
                        t.round++;
                        turn = 1;
                    }
                } else if (event.type == SDL_QUIT) {
                    continueGame = 0;
                }
            }
        } else {
            result(t, screen);
            continueGame = 0;
        }
SDL_Flip(screen);

    }

    freeTic(t);

    return 0;
}

