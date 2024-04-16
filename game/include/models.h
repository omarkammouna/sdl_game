// model.h
#ifndef MODEL_H
#define MODEL_H



#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH  750
#define SCREEN_HEIGHT 600
#define MENU_BUTTON_WIDTH 150
#define MENU_BUTTON_HEIGHT 150
#define BACKGROUND_FRAME_COUNT 150
#define STORY_FRAME_COUNT 750

typedef struct {
    int x, y, w, h;
    SDL_Rect rect;
    SDL_Surface *normal;
    SDL_Surface *selected;
    int selected_flag;
} Button;

typedef struct {
    int main_menu;
    int settings_menu;
    int gameplay;
} MenuState;
typedef struct {
	SDL_Surface *backgroundplay;
}BackgroundPLay;

extern int fullscreenFlagStatus;
extern SDL_Surface *screen;
extern Button playButton, settingsButton, storeButton, exitButton, backButton;
extern Button volumeUpButton, volumeDownButton;
extern Button fullScreen;
extern SDL_Surface *volumeLevelIndicator;
extern SDL_Rect volumeLevelIndicatorRect;
extern TTF_Font *font;
extern SDL_Color textColor;
extern MenuState currentMenu;
extern Mix_Music *backgroundMusic;
extern Mix_Music *StoryAudio;
extern int musicVolume;
extern SDL_Surface *backgroundFrames[BACKGROUND_FRAME_COUNT];
extern int currentBackgroundFrame;
extern SDL_Surface *StoryFrames[STORY_FRAME_COUNT];
extern int currentStoryFrame;
extern BackgroundPLay backgroundplays;
SDL_Surface* loadImage(const char *filename);
void renderText(const char* text, int x, int y);
void handleEvents(SDL_Event event);
void loadBackgroundFrames();
void loadStoryFrames();
void renderButtons();
void renderBackground();
void renderStory();
void renderPlayBackground();
void toggleFullscreen();
void load_set_buttons();

#endif // MODEL_H

