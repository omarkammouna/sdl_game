
#include "models.h"


int fullscreenFlagStatus = 0;
SDL_Surface *screen = NULL;
Button playButton, settingsButton, storeButton, exitButton, backButton;
Button volumeUpButton, volumeDownButton;
Button fullScreen;
SDL_Surface *volumeLevelIndicator = NULL;
BackgroundPLay backgroundplays;
SDL_Rect volumeLevelIndicatorRect;
TTF_Font *font = NULL;
SDL_Color textColor = {255, 255, 255,0};
MenuState currentMenu = {1, 0, 0};
Mix_Music *backgroundMusic = NULL;
Mix_Music *StoryAudio = NULL;
int musicVolume = MIX_MAX_VOLUME / 2;
SDL_Surface *backgroundFrames[BACKGROUND_FRAME_COUNT];
int currentBackgroundFrame = 1;
SDL_Surface *StoryFrames[STORY_FRAME_COUNT];
int currentStoryFrame = 1;

SDL_Surface* loadImage(const char *filename) {
    SDL_Surface* loadedImage = IMG_Load(filename);
    if (loadedImage == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
        return NULL;
    }
    return loadedImage;
}

void renderText(const char* text, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Rect destRect = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, screen, &destRect);

    SDL_FreeSurface(textSurface);
}

void toggleFullscreen() {
    if (fullscreenFlagStatus) {
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
        
    } else {
        SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	


   

    }
}

void handleEvents(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {

        int x = event.button.x;
        int y = event.button.y;

        if (currentMenu.main_menu) {
            if (x >= playButton.rect.x && x <= playButton.rect.x + playButton.rect.w &&
                y >= playButton.rect.y && y <= playButton.rect.y + playButton.rect.h) {
                currentMenu.main_menu = 0;	
        		currentMenu.gameplay = 1;
            } else if (x >= settingsButton.rect.x && x <= settingsButton.rect.x + settingsButton.rect.w &&
                       y >= settingsButton.rect.y && y <= settingsButton.rect.y + settingsButton.rect.h) {
                printf("Settings button clicked!\n");
                currentMenu.main_menu = 0;
                currentMenu.settings_menu = 1;
            } else if (x >= storeButton.rect.x && x <= storeButton.rect.x + storeButton.rect.w &&
                       y >= storeButton.rect.y && y <= storeButton.rect.y + storeButton.rect.h) {
                printf("Credits button clicked!\n");
            } else if (x >= exitButton.rect.x && x <= exitButton.rect.x + exitButton.rect.w &&
                       y >= exitButton.rect.y && y <= exitButton.rect.y + exitButton.rect.h) {
                printf("Exit button clicked!\n");
                SDL_Quit();
                exit(0);
            }
        } else if (currentMenu.settings_menu) {
            if (x >= backButton.rect.x && x <= backButton.rect.x + backButton.rect.w &&
                y >= backButton.rect.y && y <= backButton.rect.y + backButton.rect.h) {
                printf("Back button clicked!\n");
                currentMenu.main_menu = 1;
                currentMenu.settings_menu = 0;
            }
          else if (x >= volumeUpButton.rect.x && x <= volumeUpButton.rect.x + volumeUpButton.rect.w &&
                y >= volumeUpButton.rect.y && y <= volumeUpButton.rect.y + volumeUpButton.rect.h) {
                musicVolume += 10;
                if (musicVolume > MIX_MAX_VOLUME)
                    musicVolume = MIX_MAX_VOLUME;
                Mix_VolumeMusic(musicVolume);
                
            }
          else if (x >= volumeDownButton.rect.x && x <= volumeDownButton.rect.x +volumeDownButton.rect.w && y >= volumeDownButton.rect.y && y <= volumeDownButton.rect.y + volumeDownButton.rect.h) {
               
                 musicVolume -= 10;
                if (musicVolume < 0)
                    musicVolume = 0;
                Mix_VolumeMusic(musicVolume);
                
            }
          else if (x >= fullScreen.rect.x && x <= fullScreen.rect.x + fullScreen.rect.w &&
                y >= fullScreen.rect.y && y <= fullScreen.rect.y + fullScreen.rect.h) {
		fullScreen.selected = loadImage("../menu assets/Back to normal screen.png");
               
                if(fullscreenFlagStatus){
		fullscreenFlagStatus=0;

	}
		else{fullscreenFlagStatus=1;}
fullScreen.selected = (x >= fullScreen.rect.x && x <= fullScreen.rect.x + fullScreen.rect.w &&
                               y >= fullScreen.rect.y && y <= fullScreen.rect.y + fullScreen.rect.h) ? fullScreen.selected : fullScreen.normal;
          
        }
 	
      else if (currentMenu.gameplay)
      {
         if (x >= backButton.rect.x && x <= backButton.rect.x + backButton.rect.w &&
                y >= backButton.rect.y && y <= backButton.rect.y + backButton.rect.h) {
                printf("Back button clicked!\n");
                currentMenu.main_menu = 1;
                currentMenu.gameplay = 0;
		
            }
        
      }	
    }}  else if (event.type == SDL_MOUSEMOTION) {

    int x = event.motion.x;
    int y = event.motion.y;

    if (currentMenu.main_menu) {
	 playButton.selected = loadImage("../menu assets/Hovered Play.png");
	 settingsButton.selected = loadImage("../menu assets/Hovered Settings.png");
	 storeButton.selected = loadImage("../menu assets/credits hovered.png");
	 exitButton.selected = loadImage("../menu assets/Hovered Quit.png");

        playButton.selected = (x >= playButton.rect.x && x <= playButton.rect.x + playButton.rect.w &&
                               y >= playButton.rect.y && y <= playButton.rect.y + playButton.rect.h) ? playButton.selected : playButton.normal;
        settingsButton.selected = (x >= settingsButton.rect.x && x <= settingsButton.rect.x + settingsButton.rect.w &&
                                   y >= settingsButton.rect.y && y <= settingsButton.rect.y + settingsButton.rect.h) ? settingsButton.selected : settingsButton.normal;
        storeButton.selected = (x >= storeButton.rect.x && x <= storeButton.rect.x + storeButton.rect.w &&
                                y >= storeButton.rect.y && y <= storeButton.rect.y + storeButton.rect.h) ? storeButton.selected : storeButton.normal;
        exitButton.selected = (x >= exitButton.rect.x && x <= exitButton.rect.x + exitButton.rect.w &&
                               y >= exitButton.rect.y && y <= exitButton.rect.y + exitButton.rect.h) ? exitButton.selected : exitButton.normal;
    } else if (currentMenu.settings_menu) {
	backButton.selected = loadImage("../menu assets/Arrow hovered.png");
    
        backButton.selected = (x >= backButton.rect.x && x <= backButton.rect.x + backButton.rect.w &&
                               y >= backButton.rect.y && y <= backButton.rect.y + backButton.rect.h) ? backButton.selected : backButton.normal;

   

    }
      
      else if (currentMenu.gameplay) {
    	backButton.selected = loadImage("../menu assets/Arrow hovered.png");
        backButton.selected = (x >= backButton.rect.x && x <= backButton.rect.x + backButton.rect.w &&
                               y >= backButton.rect.y && y <= backButton.rect.y + backButton.rect.h) ? backButton.selected : backButton.normal;
        
      }
}else if (event.type == SDL_KEYDOWN) {

        if (currentMenu.settings_menu) {
            if (event.key.keysym.sym == SDLK_UP) {
                musicVolume += 10;
                if (musicVolume > MIX_MAX_VOLUME)
                    musicVolume = MIX_MAX_VOLUME;
                Mix_VolumeMusic(musicVolume);
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                musicVolume -= 10;
                if (musicVolume < 0)
                    musicVolume = 0;
                Mix_VolumeMusic(musicVolume);
            }
          else if(event.key.keysym.sym == SDLK_ESCAPE)
          {
            currentMenu.settings_menu=0;
            currentMenu.main_menu=1;
            
          }
        }
      else if(currentMenu.gameplay){
         if(event.key.keysym.sym == SDLK_ESCAPE)
          {
            currentMenu.gameplay=0;
            currentMenu.main_menu=1;
            
          }
          
        
      }
    }
}
void loadBackgroundFrames() {
    for (int i = 1; i < BACKGROUND_FRAME_COUNT; ++i) {
        char filename[150]; 
        sprintf(filename, "../background/Menu_design 2_0000%d.png", i);
        backgroundFrames[i] = IMG_Load(filename);
        if (backgroundFrames[i] == NULL) {
            printf("Unable to load background frame %d! SDL_image Error: %s\n", i, IMG_GetError());
        }
    }
}
void loadStoryFrames() {
    for (int i = 1; i < STORY_FRAME_COUNT; ++i) {
        char filename[256]; 
        sprintf(filename, "../Story/Story sequence/story_0000%d.png", i);
        StoryFrames[i] = IMG_Load(filename);
        if (StoryFrames[i] == NULL) {
            printf("Unable to load background frame %d! SDL_image Error: %s\n", i, IMG_GetError());
        }
    }
}

void renderButtons() {
    
    if (currentMenu.main_menu) {
        SDL_BlitSurface(playButton.selected ? playButton.selected : playButton.normal, NULL, screen, &playButton.rect);
        SDL_BlitSurface(settingsButton.selected ? settingsButton.selected : settingsButton.normal, NULL, screen, &settingsButton.rect);
        SDL_BlitSurface(storeButton.selected ? storeButton.selected : storeButton.normal, NULL, screen, &storeButton.rect);
        SDL_BlitSurface(exitButton.selected ? exitButton.selected : exitButton.normal, NULL, screen, &exitButton.rect);
    }
    else if (currentMenu.settings_menu) {
        SDL_BlitSurface(backButton.selected ? backButton.selected : backButton.normal, NULL, screen, &backButton.rect);

        
        SDL_BlitSurface(volumeUpButton.selected ? volumeUpButton.selected : volumeUpButton.normal, NULL, screen, &volumeUpButton.rect);
        
        SDL_BlitSurface(volumeDownButton.selected ? volumeDownButton.selected : volumeDownButton.normal, NULL, screen, &volumeDownButton.rect);
       
        SDL_BlitSurface(volumeLevelIndicator, NULL, screen, &volumeLevelIndicatorRect);
        SDL_BlitSurface(fullScreen.selected ? fullScreen.selected : fullScreen.normal, NULL, screen, &fullScreen.rect);
        
    }
  else if (currentMenu.gameplay){
    
        SDL_BlitSurface(backButton.selected ? backButton.selected : backButton.normal, NULL, screen, &backButton.rect);

  }
    SDL_Flip(screen);
}
void renderBackground() {
    SDL_BlitSurface(backgroundFrames[currentBackgroundFrame], NULL, screen, NULL);
    SDL_Flip(screen);
}
void renderStory() {
    SDL_BlitSurface(StoryFrames[currentStoryFrame], NULL, screen, NULL);
    SDL_Flip(screen);
    
}
void renderPlayBackground() {
    backgroundplays.backgroundplay = loadImage("../menu assets/play.png");
    SDL_BlitSurface(backgroundplays.backgroundplay, NULL, screen, NULL);
    SDL_Flip(screen);
}



void load_set_buttons(){

    playButton.normal = loadImage("../menu assets/Play.png");

    playButton.rect.x = 300;
    playButton.rect.y = 150;
    playButton.rect.w = MENU_BUTTON_WIDTH;
    playButton.rect.h = MENU_BUTTON_HEIGHT;

    settingsButton.normal = loadImage("../menu assets/Settings.png");

    settingsButton.rect.x = 300;
    settingsButton.rect.y = 250;
    settingsButton.rect.w = MENU_BUTTON_WIDTH;
    settingsButton.rect.h = MENU_BUTTON_HEIGHT;

    storeButton.normal = loadImage("../menu assets/credits.png");

    storeButton.rect.x = 300;
    storeButton.rect.y = 350;
    storeButton.rect.w = MENU_BUTTON_WIDTH;
    storeButton.rect.h = MENU_BUTTON_HEIGHT;

    exitButton.normal = loadImage("../menu assets/Quit.png");

    exitButton.rect.x = 300;
    exitButton.rect.y = 450;
    exitButton.rect.w = MENU_BUTTON_WIDTH;
    exitButton.rect.h = MENU_BUTTON_HEIGHT;

    backButton.normal = loadImage("../menu assets/Arrow.png");

    backButton.rect.x = 540;
    backButton.rect.y = 450;
    backButton.rect.w = MENU_BUTTON_WIDTH;
    backButton.rect.h = MENU_BUTTON_HEIGHT;

    volumeUpButton.normal = loadImage("../menu assets/+.png");
    
    volumeUpButton.rect.x = 100; 
    volumeUpButton.rect.y = 200;
    volumeUpButton.rect.w = MENU_BUTTON_WIDTH;
    volumeUpButton.rect.h = MENU_BUTTON_HEIGHT;

    volumeDownButton.normal = loadImage("../menu assets/-.png");
    
    volumeDownButton.rect.x = 100; 
    volumeDownButton.rect.y = 300;
    volumeDownButton.rect.w = MENU_BUTTON_WIDTH;
    volumeDownButton.rect.h = MENU_BUTTON_HEIGHT;
  
    fullScreen.normal = loadImage("../menu assets/Full screen.png");
    
    fullScreen.rect.x = 550; 
    fullScreen.rect.y = 225;
    fullScreen.rect.w = MENU_BUTTON_WIDTH;
    fullScreen.rect.h = MENU_BUTTON_HEIGHT;
  
    volumeLevelIndicator = loadImage("../menu assets/Sound logo.png"); 
    volumeLevelIndicatorRect.x = 50; 
    volumeLevelIndicatorRect.y = 225;
    volumeLevelIndicatorRect.w = MENU_BUTTON_WIDTH;
    volumeLevelIndicatorRect.h = MENU_BUTTON_HEIGHT;
    backgroundplays.backgroundplay = loadImage("../menu assets/play.png");
    


}




