#ifndef MAIN_C_MAPS_H
#define MAIN_C_MAPS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Base{
    Sint16 x;
    Sint16 y;
    Uint32 color;
    Uint32 color2;
    int number_of_soldiers;
    int attacking_soldiers;
    int potion;
    int timer;
    struct Soldier* soldiers;
    int max;
    bool is_attacking;
    int id;
};

struct Potion{
    Sint16 x;
    Sint16 y;
    bool is_on;
    Uint32 color;
};

struct Soldier{
    int x;
    int y;
    float speed;
    SDL_Point src;
    SDL_Point dest;
    SDL_Point dest2;
    int delay;
    bool is_attacking;
    int id;
};

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int FPS;

SDL_Texture *getImageTexture(SDL_Renderer *sdlRenderer, char *image_path);
void generate_random_base(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]);
void generate_potion(struct Base bases[20], Uint32 colors[6], struct Potion potions[6]);
void generate_bases1(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]);
void generate_bases2(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]);
void generate_bases3(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]);
void generate_bases4(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]);
void draw_potions(SDL_Renderer* sdlRenderer, struct Potion potion);
void draw_bases(SDL_Renderer *sdlRenderer, struct Base base);
void draw_soldiers(SDL_Renderer *sdlRenderer, struct Base* base, struct Base bases[20]);

#endif //MAIN_C_MAPS_H
