#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "maps.h"
#include "logic.h"
#include "players.h"

int main() {
    srand(time(0));
    long long int z;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    //players phase=====================================================================================================
    struct Player* head_players = (struct Player*)(malloc(sizeof(struct Player)));
    head_players->next = NULL;
    head_players = read_datas(head_players);
    struct Player current;
    char best[50];
    int bestie = 0;
    //players end=======================================================================================================
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
    SDL_Texture *sdlTexture2 = getImageTexture(sdlRenderer, "../menu.bmp");
    SDL_Texture *sdlTexture3 = getImageTexture(sdlRenderer, "../game.bmp");
    SDL_Texture *sdlTexture4 = getImageTexture(sdlRenderer, "../victory.bmp");
    SDL_Texture *sdlTexture5 = getImageTexture(sdlRenderer, "../lose.bmp");
    SDL_Rect texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};
    SDL_Rect texture_rect2 = {.x=20, .y=20, .w=510, .h=500};
    char username[100] = "";
    SDL_StartTextInput();

    struct Base bases[20];
    struct Potion potions[6];
    Uint32 colors[5] = {0xff0000ff, 0xff00ffff, 0xff00ff00, 0xffffff00, 0xff6e6d6f};
    Uint32 colors2[5] = {0xff000080, 0xff008080, 0xff008000, 0xff808000, 0xff6e6d6f};
    Uint32 colors3[6] = {0xff004aba, 0xff83346c, 0xfffefefd, 0xffe800e4, 0xffffbd00, 0xff03981e};
    Sint16 x1 = 100, x2 = 110;
    Sint16 y1 = 350, y2 = 380;
    long long int t=0;
    int flag = 0;
    int flag2 = 0;
    int first = 0;
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);

        //loading page==================================================================================================
        if(stage == 0) {
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            Uint32 color = 0xff8c6121;
            x2++;
            if (x2 == 130 || x2 == 200)
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
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect2);
            stringColor(sdlRenderer, 540, 285, "Enter your username below:", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 545, 305, 735, 335, 10, 0xff8c6121);
            stringColor(sdlRenderer, 600, 315, username, 0xff8c6121);
        }
            //get username page end=========================================================================================
            //menu page=====================================================================================================
        else if(stage == 2){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect2);
            roundedRectangleColor(sdlRenderer, 560, 265, 730, 295, 10, 0xff8c6121);
            stringColor(sdlRenderer, 615, 275, "New Game", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 560, 305, 730, 335, 10, 0xff8c6121);
            stringColor(sdlRenderer, 627, 315, "Maps", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 560, 345, 730, 375, 10, 0xff8c6121);
            stringColor(sdlRenderer, 603, 355, "Leaderboard", 0xff8c6121);
        }
            //menu page end=================================================================================================
            //game page=====================================================================================================
        else if(stage == 3){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            artificial_intelligence(bases);
            if(t % 50 == 0) {
                for (int i = 0; i < 20; i++) {
                    if ((bases[i].number_of_soldiers < 30 || bases[i].potion == 2) && bases[i].id != 4){
                        produce_soldier(&bases[i]);
                        if(bases[i].potion == 1 && bases[i].number_of_soldiers < 30)
                            produce_soldier(&bases[i]);
                    }
                }
            }
            if(t % z == 0 && flag2 == 0){
                generate_potion(bases, colors3, potions);
                flag2++;
            }
            for(int i = 0; i < 20; i++) {
                if(i < 6 && potions[i].is_on) {
                    draw_potions(sdlRenderer, potions[i]);
                }
                draw_bases(sdlRenderer, bases[i]);
                get_potion(bases, potions);
                check_collision(bases);
                check_attacking(&bases[i]);
                draw_soldiers(sdlRenderer, &bases[i], bases);
                if(bases[i].timer > 0){
                    bases[i].timer--;
                }if(bases[i].timer == 0){
                    bases[i].potion = 0;
                }
            }
            switch (check_win(bases)) {
                case 0:
                    break;
                case 1:
                    current.point += 10;
                    add_datas(current, head_players);
                    printf("f");
                    for(int i = 0; i < 20; i++){
                        free(bases[i].soldiers);
                    }
                    sdlTexture = sdlTexture4;
                    stage = 6; //win
                    break;
                case 2:
                    current.point -= 5;
                    if(current.point < 0)
                        current.point = 0;
                    add_datas(current, head_players);
                    printf("x");
                    for(int i = 0; i < 20; i++){
                        free(bases[i].soldiers);
                    }
                    sdlTexture = sdlTexture5;
                    stage = 7; //loose
                    break;
                default:
                    break;
            }
        }
            //game page end=================================================================================================
            //maps page=====================================================================================================
        else if(stage == 4){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect2);
            roundedRectangleColor(sdlRenderer, 560, 250, 730, 280, 10, 0xff8c6121);
            stringColor(sdlRenderer, 627, 260, "Map 1", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 560, 290, 730, 320, 10, 0xff8c6121);
            stringColor(sdlRenderer, 627, 300, "Map 2", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 560, 330, 730, 360, 10, 0xff8c6121);
            stringColor(sdlRenderer, 627, 340, "Map 3", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 560, 370, 730, 400, 10, 0xff8c6121);
            stringColor(sdlRenderer, 627, 380, "Map 4", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 630, 490, 770, 520, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 500, "Back to menu", 0xff8c6121);
        }
            //maps page end=================================================================================================
            // Leaderboard page=============================================================================================
        else if(stage == 5){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect2);
            stringColor(sdlRenderer, 580, 265, "Best Of Bests:", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 545, 285, 735, 315, 10, 0xff8c6121);
            stringColor(sdlRenderer, 570, 295, best, 0xff8c6121);
            char p[4];
            itoa(bestie, p, 10);
            stringColor(sdlRenderer, 690, 295, p, 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 630, 490, 770, 520, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 500, "Back to menu", 0xff8c6121);
        }
            //Leaderboard page end==========================================================================================
            // victory page==================================================================================================
        else if(stage == 6){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
            //victory page end==============================================================================================
            //lose page=====================================================================================================
        else if(stage == 7){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
        //lose page end=================================================================================================
        //event handling================================================================================================
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
                else if (sdlEvent.key.keysym.sym == SDLK_RETURN){
                    if(search_player(username, head_players) == NULL){
                        head_players = add_player(head_players, username, 0);
                        strcpy(current.name, username);
                        current.point = 0;
                    }else{
                        strcpy(current.name, username);
                        current.point = search_player(username, head_players)->point;
                    }
                    stage = 2;
                }
            }
            else if(sdlEvent.type == SDL_MOUSEBUTTONDOWN){
                if(stage == 2){
                    if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 265 <= sdlEvent.button.y && 295 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_random_base(bases, colors, colors2);
                    }
                    else if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 305 <= sdlEvent.button.y && 335 >= sdlEvent.button.y)
                        stage = 4;
                    else if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 345 <= sdlEvent.button.y && 375 >= sdlEvent.button.y) {
                        bestie = 0;
                        bestie = find_best(best, bestie, head_players);
                        stage = 5;
                    }
                }else if(stage == 3){
                    for(int i = 0; i < 20; i++){
                        if(bases[i].x-30 <= sdlEvent.button.x && bases[i].x+30 >= sdlEvent.button.x && bases[i].y-25 <= sdlEvent.button.y && bases[i].y+25 >= sdlEvent.button.y){
                            if(flag == 0 && bases[i].id == 0){
                                flag++;
                                first = i;
                            }else if(flag == 1 && i != first && !bases[first].is_attacking){
                                if(bases[first].max / 2 < bases[first].number_of_soldiers || bases[first].max > bases[first].number_of_soldiers * 3) {
                                    bases[first].soldiers = (struct Soldier *)realloc(bases[first].soldiers, bases[first].number_of_soldiers * 2 * sizeof(struct Soldier));
                                    bases[first].max = 2 * bases[first].number_of_soldiers;
                                }
                                bases[first].is_attacking = true;
                                for(int j = 0; j < bases[first].number_of_soldiers; j++) {
                                    (*((bases[first].soldiers)+j)).speed = 3.5;
                                    if (bases[first].potion == 3)
                                        (*((bases[first].soldiers)+j)).speed = 7;
                                    if (bases[first].potion == 4)
                                        (*((bases[first].soldiers)+j)).speed = 2;
                                    (*((bases[first].soldiers)+j)).src.x = bases[first].x;
                                    (*((bases[first].soldiers)+j)).src.y = bases[first].y;
                                    (*((bases[first].soldiers)+j)).dest.x = bases[i].x;
                                    (*((bases[first].soldiers)+j)).dest.y = bases[i].y;
                                    (*((bases[first].soldiers)+j)).dest2.x = bases[i].x;
                                    (*((bases[first].soldiers)+j)).dest2.y = bases[i].y;
                                }
                                attack(&bases[first]);
                                bases[first].attacking_soldiers = bases[first].number_of_soldiers;
                                bases[first].number_of_soldiers = 0;
                                flag--;
                                first = 0;
                            }
                        }
                    }
                }else if(stage == 4){
                    if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 250 <= sdlEvent.button.y && 280 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases1(bases, colors, colors2);
                    }
                    else if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 290 <= sdlEvent.button.y && 320 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases2(bases, colors, colors2);
                    }
                    else if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 330 <= sdlEvent.button.y && 360 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases3(bases, colors, colors2);
                    }
                    else if(560 <= sdlEvent.button.x && 730 >= sdlEvent.button.x && 370 <= sdlEvent.button.y && 400 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases4(bases, colors, colors2);
                    }
                    else if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 490 <= sdlEvent.button.y && 520 >= sdlEvent.button.y)
                        stage = 2;
                }else if(stage == 5){
                    if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 490 <= sdlEvent.button.y && 520 >= sdlEvent.button.y)
                        stage = 2;
                }else if(stage == 6) {
                    if (630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y) {
                        sdlTexture = sdlTexture2;
                        stage = 2;
                    }
                }else if(stage == 7) {
                    if (630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y) {
                        sdlTexture = sdlTexture2;
                        stage = 2;
                    }
                }
            }
        }
        //event handling end============================================================================================
        if(t % 3500 == 0){
            z = rand() % 1000;
            flag2 = 0;
        }
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        t++;
    }
    save_datas(head_players);
    SDL_StopTextInput();
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}