#include <SDL/SDL.h>
#include "models.h"

int main() {
	
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }


    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("SDL_mixer initialization failed: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }


    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
    if (screen == NULL) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    if (TTF_Init() == -1) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    SDL_WM_SetCaption("Echoes of Eearth", NULL);


    font = TTF_OpenFont("../Arial.TTF", 28);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        TTF_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    loadStoryFrames();


    StoryAudio = Mix_LoadMUS("../Story/Audio.mp3");
    if (StoryAudio == NULL) {
        printf("Failed to load story audio: %s\n", Mix_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    Mix_PlayMusic(StoryAudio, 0);


    while (currentStoryFrame <= STORY_FRAME_COUNT) {
        renderStory();
        SDL_Delay(35);
        currentStoryFrame++;
        if (currentStoryFrame == 749) {
            Mix_FreeMusic(StoryAudio);
        }
    }


    for (int i = 0; i < STORY_FRAME_COUNT; ++i) {
        SDL_FreeSurface(StoryFrames[i]);
    }


    loadBackgroundFrames();


    backgroundMusic = Mix_LoadMUS("../sound2.mp3");
    if (backgroundMusic == NULL) {
        printf("Failed to load background music: %s\n", Mix_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    
	load_set_buttons();
    Mix_PlayMusic(backgroundMusic, -1);
	int prev_music_volume=musicVolume;
    int quit = 0;
    SDL_Event event;
    while (!quit) {
	
        while (SDL_PollEvent(&event)) {
            handleEvents(event);
        }

	if (currentMenu.gameplay){

		musicVolume = 0;
		Mix_VolumeMusic(musicVolume);
		renderPlayBackground();
		renderButtons();
		
		
		}
	else {
	renderButtons();
	if(
	currentMenu.main_menu){
	musicVolume = prev_music_volume;
	Mix_VolumeMusic(musicVolume);
	

	}
	if(currentMenu.settings_menu){
					
					prev_music_volume=musicVolume; 
					toggleFullscreen();
					
					

				      }
        renderBackground();
	if(currentMenu.main_menu){
        renderText("Echoes of Eearth", 50, 50);}
	else{renderText("settings", 50, 50);}
        renderButtons();
	
        SDL_Delay(100); 
        currentBackgroundFrame = (currentBackgroundFrame + 1) % BACKGROUND_FRAME_COUNT;
    }

}

    for (int i = 0; i < BACKGROUND_FRAME_COUNT; ++i) {
        SDL_FreeSurface(backgroundFrames[i]);
    }

    SDL_FreeSurface(playButton.normal);
    SDL_FreeSurface(playButton.selected);
    SDL_FreeSurface(settingsButton.normal);
    SDL_FreeSurface(settingsButton.selected);
    SDL_FreeSurface(storeButton.normal);
    SDL_FreeSurface(storeButton.selected);
    SDL_FreeSurface(exitButton.normal);
    SDL_FreeSurface(exitButton.selected);
    SDL_FreeSurface(backButton.normal);
    SDL_FreeSurface(backButton.selected);
    SDL_FreeSurface(volumeUpButton.normal);
    SDL_FreeSurface(volumeUpButton.selected);
    SDL_FreeSurface(volumeDownButton.normal);
    SDL_FreeSurface(volumeDownButton.selected);
    SDL_FreeSurface(backgroundplays.backgroundplay);
    SDL_FreeSurface(volumeLevelIndicator);
    Mix_FreeMusic(backgroundMusic);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

