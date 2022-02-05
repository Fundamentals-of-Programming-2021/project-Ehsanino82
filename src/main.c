#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 560;
const int FPS = 60;

SDL_Texture *getImageTexture(SDL_Renderer *sdlRenderer, char *image_path) {
    SDL_Surface *image = SDL_LoadBMP(image_path);
    if (!image) {
        printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
        return 0;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_FreeSurface(image);
    image = NULL;
    return texture;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    //loading phase=====================================================================================================
    int load = 12;
    int stage = 0;
    char loading[3];
    itoa(load, loading, 10);
    //loading phase end=================================================================================================
    SDL_Window *sdlWindow = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Texture *sdlTexture = getImageTexture(sdlRenderer, "../loading screen.bmp");
    SDL_Texture *sdlTexture2 = getImageTexture(sdlRenderer, "../input name.bmp");
    SDL_Texture *sdlTexture3 = getImageTexture(sdlRenderer, "../game.bmp");
    SDL_Rect texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};
    char username[100] = "";
    SDL_StartTextInput();

    Sint16 x1 = 100, x2 = 110;
    Sint16 y1 = 350, y2 = 380;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);

        //loading page==================================================================================================
        if(stage == 0) {
            Uint32 color = 0xff8c6121;
            x2++;
            if (x2 == 130 || x2 == 170 || x2 == 200)
                SDL_Delay(1000);

            roundedBoxColor(sdlRenderer, x1, y1, x2, y2, 8, color);
            stringColor(sdlRenderer, 100, 395, "loading:", 0xff8c6121);
            stringColor(sdlRenderer, 165, 395, loading, 0xff8c6121);
            stringColor(sdlRenderer, 190, 395, "%", 0xff8c6121);
            load++;
            itoa(load, loading, 10);
            if(load == 101) {
                SDL_Delay(1000);
                sdlTexture = sdlTexture2;
                stage = 1;
            }
        }
        //loading page end==============================================================================================
        //get username page=============================================================================================
        else if(stage == 1){
            stringColor(sdlRenderer, 510, 355, "Enter your username below:", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 510, 375, 700, 405, 10, 0xff8c6121);
            stringColor(sdlRenderer, 570, 385, username, 0xff8c6121);
        }
        //get username page end=========================================================================================
        //menu page=====================================================================================================
        else if(stage == 2){
            roundedRectangleColor(sdlRenderer, 500, 340, 670, 370, 10, 0xff8c6121);
            stringColor(sdlRenderer, 555, 350, "New Game", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 500, 380, 670, 410, 10, 0xff8c6121);
            stringColor(sdlRenderer, 567, 390, "Maps", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 500, 420, 670, 450, 10, 0xff8c6121);
            stringColor(sdlRenderer, 543, 430, "Leaderboard", 0xff8c6121);
        }
        //menu page end=================================================================================================
        else if(stage == 3){
            // code must be completed to play the game
        }
        //maps page=====================================================================================================
        else if(stage == 4){
            roundedRectangleColor(sdlRenderer, 500, 310, 670, 340, 10, 0xff8c6121);
            stringColor(sdlRenderer, 567, 320, "Map 1", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 500, 350, 670, 380, 10, 0xff8c6121);
            stringColor(sdlRenderer, 567, 360, "Map 2", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 500, 390, 670, 420, 10, 0xff8c6121);
            stringColor(sdlRenderer, 567, 400, "Map 3", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 500, 430, 670, 460, 10, 0xff8c6121);
            stringColor(sdlRenderer, 567, 440, "Map 4", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
        //maps page end=================================================================================================
        //Leaderboard page==============================================================================================
        else if(stage == 5){
            // code must be completed to show the leaderboard
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
        //Leaderboard page end==========================================================================================
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            if(sdlEvent.type == SDL_QUIT)
                shallExit = SDL_TRUE;
            else if(sdlEvent.type == SDL_TEXTINPUT || sdlEvent.type == SDL_KEYDOWN) {
                system("cls");
                if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0)
                    username[strlen(username) - 1] = '\0';
                else if (sdlEvent.type == SDL_TEXTINPUT)
                    strcat(username, sdlEvent.text.text);
                else if (sdlEvent.key.keysym.sym == SDLK_RETURN)
                    stage = 2;
            }
            else if(sdlEvent.type == SDL_MOUSEBUTTONDOWN){
                if(stage == 2){
                    if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 340 <= sdlEvent.button.y && 370 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        // code must be completed to start the game
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 380 <= sdlEvent.button.y && 410 >= sdlEvent.button.y)
                        stage = 4;
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 420 <= sdlEvent.button.y && 450 >= sdlEvent.button.y)
                        stage = 5;
                }else if(stage == 3){
                    // code must be completed to start the game
                }else if(stage == 4){
                    if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 310 <= sdlEvent.button.y && 340 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        // code must be completed to start the game
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 350 <= sdlEvent.button.y && 380 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        // code must be completed to start the game
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 390 <= sdlEvent.button.y && 420 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        // code must be completed to start the game
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 430 <= sdlEvent.button.y && 460 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        // code must be completed to start the game
                    }
                    else if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y)
                        stage = 2;
                }else if(stage == 5){
                    if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y)
                        stage = 2;
                }
            }
        }
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_StopTextInput();
    SDL_DestroyWindow(sdlWindow);
    printf("Hello World\n");
    SDL_Quit();
    return 0;
}