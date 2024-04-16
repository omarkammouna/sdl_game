#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "main.h"
void initializeTic(TicTacToe* t) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();


    t->background = IMG_Load("img/board.png");
    t->playerX = IMG_Load("img/x.png");
    t->playerO = IMG_Load("img/o.png");


    int boxWidth = t->background->w / 3;
    int boxHeight = t->background->h / 3;
    for (int i = 0; i < 9; ++i) {
        t->tabPos[i].x = ((i % 3) * boxWidth)+12;
        t->tabPos[i].y = ((i / 3) * boxHeight)+10;
    }


    for (int i = 0; i < 9; ++i) {
        t->tabfollow[i] = 0;
    }


    t->round = 0;


    t->font = TTF_OpenFont("fonts/Arial.TTF", 45);
    t->textColor.r = 255;
    t->textColor.g = 206;
    t->textColor.b = 20;
}


void displayTic(TicTacToe t, SDL_Surface* screen) {
    SDL_BlitSurface(t.background, NULL, screen, NULL);

    for (int i = 0; i < 9; ++i) {
        if (t.tabfollow[i] == 1) {
            SDL_BlitSurface(t.playerO, NULL, screen, &t.tabPos[i]);
        } else if (t.tabfollow[i] == -1) {
            SDL_BlitSurface(t.playerX, NULL, screen, &t.tabPos[i]);
        }
    }

    
}


int whoIsWinner(int tabfollow[]) {
    int winningLines[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    
    for (int i = 0; i < 8; ++i) {
        int a = winningLines[i][0];
        int b = winningLines[i][1];
        int c = winningLines[i][2];

        if (tabfollow[a] != 0 && tabfollow[a] == tabfollow[b] && tabfollow[b] == tabfollow[c]) {
            return tabfollow[a];
        }
    }

    return 0;
}


void result(TicTacToe t, SDL_Surface* screen) {
    SDL_Surface* message;

    int winner = whoIsWinner(t.tabfollow);

    if (winner == 1) {
        strcpy(t.text, "bot wins!");
    } else if (winner == -1) {
        strcpy(t.text, "you wins!");
    } else {
        strcpy(t.text, "It's a draw!");
    }

    message = TTF_RenderText_Solid(t.font, t.text, t.textColor);
    t.textPos.x = (screen->w - message->w) / 3;
    t.textPos.y = (screen->h - message->h) / 3;
    
    SDL_BlitSurface(message, NULL, screen, &t.textPos);
    

 
    SDL_FreeSurface(message);
}


void freeTic(TicTacToe t) {
    SDL_FreeSurface(t.background);
    SDL_FreeSurface(t.playerX);
    SDL_FreeSurface(t.playerO);
    TTF_CloseFont(t.font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int minimax(int tabfollow[9], int player) {
    int winner = whoIsWinner(tabfollow);

    if (winner != 0) {
        if ((player == 1 && winner == 1) || (player == -1 && winner == -1)) {
            return 1;
        } else {
            return -1;
        }
    }

    int bestValue;
    if (player == 1) {
        bestValue = -9999;
    } else {
        bestValue = 9999;
    }

    for (int i = 0; i < 9; ++i) {
        if (tabfollow[i] == 0) {
            tabfollow[i] = player;
            int value = minimax(tabfollow, -player);
            tabfollow[i] = 0;

            if (player == 1) {
                if (value > bestValue) {
                    bestValue = value;
                }
            } else {
                if (value < bestValue) {
                    bestValue = value;
                }
            }
        }
    }

    return bestValue;
}


void calculateShot(int tabfollow[9]) {
    int bestValue = -9999;
    int bestShot = -1;

    for (int i = 0; i < 9; ++i) {
        if (tabfollow[i] == 0) {
            tabfollow[i] = 1;
            int value = minimax(tabfollow, -1);
            tabfollow[i] = 0;

            if (value > bestValue) {
                bestValue = value;
                bestShot = i;
            }
        }
    }

    if (bestShot != -1) {
        tabfollow[bestShot] = 1;
    }
}
