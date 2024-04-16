#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    SDL_Surface* background;
    SDL_Surface* playerX;
    SDL_Surface* playerO;
    int tabfollow[9];
    SDL_Rect tabPos[9];
    int round;
    TTF_Font* font;
    SDL_Color textColor;
    char text[20];
    SDL_Rect textPos;
} TicTacToe;

void initializeTic(TicTacToe* t);
void displayTic(TicTacToe t, SDL_Surface* screen);
int whoIsWinner(int tabfollow[]);
void result(TicTacToe t, SDL_Surface* screen);
void freeTic(TicTacToe t);
int minimax(int tabfollow[9], int player);
void calculateShot(int tabfollow[9]);


#endif
