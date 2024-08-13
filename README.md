# SDL Tic-Tac-Toe Game

This is a simple Tic-Tac-Toe game implemented using SDL (Simple DirectMedia Layer) and SDL_TTF for rendering text. The game allows the player to play against a bot and displays the result after 3 round , for my uni project 

## Features

- Play Tic-Tac-Toe against a bot
- Supports both mouse and keyboard inputs
- Displays the result after 3 rounds with a visual effect
- Shows a message for 1 second and then clears it

## Prerequisites

- SDL
- SDL_image
- SDL_ttf
- SDL_gfx

## Installation

1. Make sure you have SDL and related libraries installed. On Ubuntu, you can install them using:
    ```bash
    sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev
    ```

2. Clone this repository:
    ```bash
    git clone https://github.com/omarkammouna/sdl-tic-tac-toe.git
    cd sdl-tic-tac-toe
    ```

3. Compile the code using the provided `Makefile`:
    ```bash
    make
    ```

## Usage

Run the compiled game:
```bash
./game
