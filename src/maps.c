#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "maps.h"

const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 560;
int FPS = 60;

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

void generate_random_base(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]){
    srand(time(0));
    bases[0].x = 60;
    bases[0].y = 60;
    bases[0].color = colors[0];
    bases[0].color2 = colors2[0];
    bases[0].id = 0;
    bases[0].number_of_soldiers = 0;
    bases[0].attacking_soldiers = 0;
    bases[0].potion = 0;
    bases[0].timer = 0;
    bases[0].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
    bases[0].max = 60;
    bases[0].is_attacking = false;
    int flag;
    int i = 1;
    int x, y;
    for(i; i < 5; i++) {
        flag = 0;
        x = rand() % 610 + 60;
        y = rand() % 430 + 60;
        if((x >= SCREEN_WIDTH / 2 - 50 && x <= SCREEN_WIDTH / 2 + 50) || (y >= SCREEN_HEIGHT / 2 - 30 && y <= SCREEN_HEIGHT / 2 + 50)) {
            i--;
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (pow(abs(x - bases[j].x),2) + pow(abs(y - bases[j].y),2) > 8000) {
                flag++;
                continue;
            }else
                break;
        }if(flag == i) {
            bases[i].x = x;
            bases[i].y = y;
            bases[i].color = colors[0];
            bases[i].color2 = colors2[0];
            bases[i].id = 0;
            bases[i].timer = 0;
            bases[i].potion = 0;
            bases[i].number_of_soldiers = 0;
            bases[i].attacking_soldiers = 0;
            bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
            bases[i].max = 60;
            bases[i].is_attacking = false;
        }else {
            i--;
        }
    }
    for(i; i < 15; i++){
        flag = 0;
        int z = 1 + rand()%3;
        x = rand() % 610 + 50;
        y = rand() % 430 + 50;
        if((x >= SCREEN_WIDTH / 2 - 60 && x <= SCREEN_WIDTH / 2 + 60) || (y >= SCREEN_HEIGHT / 2 - 40 && y <= SCREEN_HEIGHT / 2 + 60)) {
            i--;
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (pow(x - bases[j].x,2) + pow(y - bases[j].y,2) > 8000) {
                flag++;
                continue;
            }else
                break;
        }if(flag == i) {
            bases[i].x = x;
            bases[i].y = y;
            bases[i].color = colors[z];
            bases[i].color2 = colors2[z];
            bases[i].id = z;
            bases[i].potion = 0;
            bases[i].timer = 0;
            bases[i].number_of_soldiers = 0;
            bases[i].attacking_soldiers = 0;
            bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
            bases[i].max = 60;
            bases[i].is_attacking = false;
        }else {
            i--;
            flag = 0;
        }
    }
    for(i; i < 20; i++){
        flag = 0;
        x = rand() % 610 + 50;
        y = rand() % 430 + 50;
        if((x >= SCREEN_WIDTH / 2 - 60 && x <= SCREEN_WIDTH / 2 + 60) || (y >= SCREEN_HEIGHT / 2 - 40 && y <= SCREEN_HEIGHT / 2 + 60)) {
            i--;
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (pow(x - bases[j].x,2) + pow(y - bases[j].y,2) > 8000) {
                flag++;
                continue;
            }else
                break;
        }if(flag == i) {
            bases[i].x = x;
            bases[i].y = y;
            bases[i].color = colors[4];
            bases[i].color2 = colors2[4];
            bases[i].id = 4;
            bases[i].potion = 0;
            bases[i].timer = 0;
            bases[i].number_of_soldiers = 30;
            bases[i].attacking_soldiers = 0;
            bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
            bases[i].max = 60;
            bases[i].is_attacking = false;
        }else {
            i--;
            flag = 0;
        }
    }
}

void generate_potion(struct Base bases[20], Uint32 colors[6], struct Potion potions[6]){
    srand(time(0));
    int flag, flag2, z, temp;
    int i = 0;
    int k =  2 + (rand() % 4);
    z = 2 + (rand() % 4);
    while(k == z)
        z = 2 + rand() % 4;
    if(k > z){
        temp = z;
        z = k;
        k = temp;
    }
    int x, y, counter = 0;
    for(i; i < 6; i++) {
        if(i < 2 || i == k || i == z) {
            flag = 0;
            flag2 = 0;
            x = rand() % 580;
            y = rand() % 360;
            if((x <= 200) || (y <= 200)) {
                i--;
                continue;
            }
            for (int j = 0; (j < counter && j < 3); j++) {
                if(j > 1)
                    j = k;
                if (pow(abs(x - potions[j].x), 2) + pow(abs(y - potions[j].y), 2) > 1000) {
                    flag++;
                    continue;
                } else
                    break;
            }
            if (flag != counter) {
                i--;
                continue;
            }
            for (int j = 0; j < 20; j++) {
                if (pow(abs(x - bases[j].x), 2) + pow(abs(y - bases[j].y), 2) > 9000) {
                    flag2++;
                    continue;
                } else
                    break;
            }
            if (flag2 == 20) {
                potions[i].x = x;
                potions[i].y = y;
                potions[i].is_on = true;
                potions[i].color = colors[i];
                counter++;
            } else {
                i--;
            }
        }else{
            potions[i].x = 0;
            potions[i].y = 0;
            potions[i].is_on = false;
            potions[i].color = colors[i];
        }
    }
}

void generate_bases1(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]) {
    for(int i = 0; i < 8; i++) {
        bases[i].x = 200;
        bases[i].y = 35 + (i * 70);
        bases[i].color = colors[0];
        bases[i].color2 = colors2[0];
        bases[i].id = 0;
        bases[i].potion = 0;
        bases[i].timer = 0;
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
        bases[i].soldiers = (struct Soldier *) (malloc(60 * sizeof(struct Soldier)));
        bases[i].max = 60;
        bases[i].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        bases[i + 16].x = 390;
        if(i < 2)
            bases[i + 16].y = 75 + (i * 70);
        else
            bases[i + 16].y = 275 + (i * 70);
        bases[i + 16].color = colors[4];
        bases[i + 16].color2 = colors2[4];
        bases[i + 16].id = 4;
        bases[i + 16].potion = 0;
        bases[i + 16].timer = 0;
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
        bases[i + 16].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 16].max = 60;
        bases[i + 16].is_attacking = false;
    }
    for(int i = 0; i < 8; i++){
        bases[i + 8].x = 580;
        bases[i + 8].y = 35 + (i * 70);
        bases[i + 8].color = colors[3];
        bases[i + 8].color2 = colors2[3];
        bases[i + 8].id = 3;
        bases[i + 8].potion = 0;
        bases[i + 8].timer = 0;
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
        bases[i + 8].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 8].max = 60;
        bases[i + 8].is_attacking = false;
    }
}

void generate_bases2(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]) {
    for(int i = 0; i < 5; i++){
        if(i < 2) {
            bases[i].x = 350 + ((i % 2) * 70);
            bases[i].y = 50;
        }else if(i == 2) {
            bases[i].x = 385;
            bases[i].y = 110;
        }else{
            bases[i].x = 350 + ((i % 2) * 70);
            bases[i].y = 170;
        }
        bases[i].color = colors[0];
        bases[i].color2 = colors2[0];
        bases[i].id = 0;
        bases[i].potion = 0;
        bases[i].timer = 0;
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
        bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i].max = 60;
        bases[i].is_attacking = false;
    }
    for(int i = 0; i < 5; i++){
        if(i < 2) {
            bases[i + 5].x = 50 + ((i % 2) * 70);
            bases[i + 5].y = 380;
        }else if(i == 2) {
            bases[i + 5].x = 85;
            bases[i + 5].y = 440;
        }else{
            bases[i + 5].x = 50 + ((i % 2) * 70);
            bases[i + 5].y = 500;
        }
        bases[i + 5].color = colors[1];
        bases[i + 5].color2 = colors2[1];
        bases[i + 5].id = 1;
        bases[i + 5].potion = 0;
        bases[i + 5].timer = 0;
        bases[i + 5].number_of_soldiers = 0;
        bases[i + 5].attacking_soldiers = 0;
        bases[i + 5].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 5].max = 60;
        bases[i + 5].is_attacking = false;
    }
    for(int i = 0; i < 5; i++){
        if(i < 2) {
            bases[i + 10].x = 660 + ((i % 2) * 70);
            bases[i + 10].y = 380;
        }else if(i == 2) {
            bases[i + 10].x = 695;
            bases[i + 10].y = 440;
        }else{
            bases[i + 10].x = 660 + ((i % 2) * 70);
            bases[i + 10].y = 500;
        }
        bases[i + 10].color = colors[2];
        bases[i + 10].color2 = colors2[2];
        bases[i + 10].id = 2;
        bases[i + 10].potion = 0;
        bases[i + 10].timer = 0;
        bases[i + 10].number_of_soldiers = 0;
        bases[i + 10].attacking_soldiers = 0;
        bases[i + 10].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 10].max = 60;
        bases[i + 10].is_attacking = false;
    }
    for(int i = 0; i < 5; i++){
        if(i < 3) {
            bases[i + 15].x = 325 + ((i % 3) * 70);
            bases[i + 15].y = 380;
        }else{
            bases[i + 15].x = 360 + ((i % 2) * 70);
            bases[i + 15].y = 440;
        }
        bases[i + 15].color = colors[4];
        bases[i + 15].color2 = colors2[4];
        bases[i + 15].id = 4;
        bases[i + 15].potion = 0;
        bases[i + 15].timer = 0;
        bases[i + 15].number_of_soldiers = 30;
        bases[i + 15].attacking_soldiers = 0;
        bases[i + 15].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 15].max = 60;
        bases[i + 15].is_attacking = false;
    }
}

void generate_bases3(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]) {
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i].x = 120;
            bases[i].y = 50;
        }else if(i > 2) {
            bases[i].x = 120;
            bases[i].y = 170;
        }else{
            bases[i].x = 55 + ((i % 2) * 130);
            bases[i].y = 110;
        }
        bases[i].color = colors[0];
        bases[i].color2 = colors2[0];
        bases[i].id = 0;
        bases[i].potion = 0;
        bases[i].timer = 0;
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
        bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i].max = 60;
        bases[i].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 4].x = 120;
            bases[i + 4].y = 390;
        }else if(i > 2) {
            bases[i + 4].x = 120;
            bases[i + 4].y = 510;
        }else{
            bases[i + 4].x = 55  + ((i % 2) * 130);
            bases[i + 4].y = 450;
        }
        bases[i + 4].color = colors[1];
        bases[i + 4].color2 = colors2[1];
        bases[i + 4].id = 1;
        bases[i + 4].potion = 0;
        bases[i + 4].timer = 0;
        bases[i + 4].number_of_soldiers = 0;
        bases[i + 4].attacking_soldiers = 0;
        bases[i + 4].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 4].max = 60;
        bases[i + 4].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 8].x = 660;
            bases[i + 8].y = 50;
        }else if(i > 2) {
            bases[i + 8].x = 660;
            bases[i + 8].y = 170;
        }else{
            bases[i + 8].x = 595 + ((i % 2) * 130);
            bases[i + 8].y = 110;
        }
        bases[i + 8].color = colors[2];
        bases[i + 8].color2 = colors2[2];
        bases[i + 8].id = 2;
        bases[i + 8].potion = 0;
        bases[i + 8].timer = 0;
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
        bases[i + 8].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 8].max = 60;
        bases[i + 8].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 12].x = 660;
            bases[i + 12].y = 390;
        }else if(i > 2) {
            bases[i + 12].x = 660;
            bases[i + 12].y = 510;
        }else{
            bases[i + 12].x = 595  + ((i % 2) * 130);
            bases[i + 12].y = 450;
        }
        bases[i + 12].color = colors[3];
        bases[i + 12].color2 = colors2[3];
        bases[i + 12].id = 3;
        bases[i + 12].potion = 0;
        bases[i + 12].timer = 0;
        bases[i + 12].number_of_soldiers = 0;
        bases[i + 12].attacking_soldiers = 0;
        bases[i + 12].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 12].max = 60;
        bases[i + 12].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 16].x = 390;
            bases[i + 16].y = 110;
        }else if(i > 2) {
            bases[i + 16].x = 390;
            bases[i + 16].y = 450;
        }else{
            bases[i + 16].x = 120  + ((i % 2) * 540);
            bases[i + 16].y = 280;
        }
        bases[i + 16].color = colors[4];
        bases[i + 16].color2 = colors2[4];
        bases[i + 16].id = 4;
        bases[i + 16].potion = 0;
        bases[i + 16].timer = 0;
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
        bases[i + 16].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 16].max = 60;
        bases[i + 16].is_attacking = false;
    }
}

void generate_bases4(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]) {
    for(int i = 0; i < 4; i++){
        if(i < 2) {
            bases[i].x = 120 + ((i % 2) * 540);
            bases[i].y = 50;
        }else{
            bases[i].x = 120 + ((i % 2) * 540);
            bases[i].y = 510;
        }
        bases[i].color = colors[0];
        bases[i].color2 = colors2[0];
        bases[i].id = 0;
        bases[i].potion = 0;
        bases[i].timer = 0;
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
        bases[i].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i].max = 60;
        bases[i].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 2) {
            bases[i + 4].x = 220 + ((i % 2) * 340);
            bases[i + 4].y = 150;
        }else{
            bases[i + 4].x = 220 + ((i % 2) * 340);
            bases[i + 4].y = 410;
        }
        bases[i + 4].color = colors[1];
        bases[i + 4].color2 = colors2[1];
        bases[i + 4].id = 1;
        bases[i + 4].potion = 0;
        bases[i + 4].timer = 0;
        bases[i + 4].number_of_soldiers = 0;
        bases[i + 4].attacking_soldiers = 0;
        bases[i + 4].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 4].max = 60;
        bases[i + 4].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 8].x = 390;
            bases[i + 8].y = 50;
        }else if(i > 2) {
            bases[i + 8].x = 390;
            bases[i + 8].y = 510;
        }else{
            bases[i + 8].x = 120 + ((i % 2) * 540);
            bases[i + 8].y = 280;
        }
        bases[i + 8].color = colors[2];
        bases[i + 8].color2 = colors2[2];
        bases[i + 8].id = 2;
        bases[i + 8].potion = 0;
        bases[i + 8].timer = 0;
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
        bases[i + 8].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 8].max = 60;
        bases[i + 8].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 1) {
            bases[i + 12].x = 390;
            bases[i + 12].y = 150;
        }else if(i > 2) {
            bases[i + 12].x = 390;
            bases[i + 12].y = 410;
        }else{
            bases[i + 12].x = 220  + ((i % 2) * 340);
            bases[i + 12].y = 280;
        }
        bases[i + 12].color = colors[3];
        bases[i + 12].color2 = colors2[3];
        bases[i + 12].id = 3;
        bases[i + 12].potion = 0;
        bases[i + 12].timer = 0;
        bases[i + 12].number_of_soldiers = 0;
        bases[i + 12].attacking_soldiers = 0;
        bases[i + 12].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 12].max = 60;
        bases[i + 12].is_attacking = false;
    }
    for(int i = 0; i < 4; i++){
        if(i < 2) {
            bases[i + 16].x = 120 + ((i % 2) * 540);
            bases[i + 16].y = 150;
        }else{
            bases[i + 16].x = 120 + ((i % 2) * 540);
            bases[i + 16].y = 410;
        }
        bases[i + 16].color = colors[4];
        bases[i + 16].color2 = colors2[4];
        bases[i + 16].id = 4;
        bases[i + 16].potion = 0;
        bases[i + 16].timer = 0;
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
        bases[i + 16].soldiers = (struct Soldier*)(malloc(60 * sizeof(struct Soldier)));
        bases[i + 16].max = 60;
        bases[i + 16].is_attacking = false;
    }
}

void draw_potions(SDL_Renderer* sdlRenderer, struct Potion potion){
    Sint16 vx[6] = {potion.x - 3, potion.x - 3, potion.x + 3, potion.x + 3, potion.x + 9, potion.x - 9};
    Sint16 vy[6] = {potion.y, potion.y - 18, potion.y - 18, potion.y, potion.y + 9, potion.y + 9};
    filledPolygonColor(sdlRenderer, vx, vy, 6, potion.color);
}

void draw_bases(SDL_Renderer *sdlRenderer, struct Base base) {
    Sint16 vx[6] = {base.x-30, base.x-15,base.x+15, base.x+30, base.x+15, base.x-15};
    Sint16 vy[6] = {base.y, base.y - (15 * sqrt(3)), base.y - (15 * sqrt(3)), base.y, base.y + (15 * sqrt(3)), base.y + (15 * sqrt(3))};
    Sint16 vx2[4] = {base.x-10, base.x,base.x+10, base.x};
    Sint16 vy2[4] = {base.y, base.y - 10, base.y, base.y+10};
    filledPolygonColor(sdlRenderer, vx, vy, 6, base.color);
    filledPolygonColor(sdlRenderer, vx2, vy2, 4, base.color2);
    if(base.potion == 1 || base.potion == 2 || base.potion == 6 || base.potion == 7){
        Sint16 vx3[8] = {base.x-7, base.x,base.x+7, base.x+2, base.x+7, base.x, base.x-7, base.x-2};
        Sint16 vy3[8] = {base.y - 37, base.y - 32, base.y -37, base.y-30, base.y-23, base.y-28, base.y-23, base.y - 30};
        filledPolygonColor(sdlRenderer, vx3, vy3, 8, base.color2);
    }
    char soldiers[5];
    itoa(base.number_of_soldiers, soldiers, 10);
    stringColor(sdlRenderer, base.x -3, base.y + 13, soldiers, 0xffaa0000);
}

void fight(struct Base bases[20], struct Base* base, int n){
    for(int i = 0; i < 20; i++){
        if((*((base->soldiers)+n)).dest2.x == bases[i].x && (*((base->soldiers)+n)).dest2.y == bases[i].y) {
            if (base->id == bases[i].id) {
                bases[i].number_of_soldiers++;
            } else {
                bases[i].number_of_soldiers--;
                if(bases[i].potion == 6)
                    bases[i].number_of_soldiers++;
                if(bases[i].potion == 7) {
                    bases[i].number_of_soldiers++;
                    bases[i].number_of_soldiers++;
                }
                if (bases[i].number_of_soldiers < 0) {
                    bases[i].number_of_soldiers++;
                    bases[i].id = base->id;
                    bases[i].potion = base->potion;
                    bases[i].timer = base->timer;
                    bases[i].color = base->color;
                    bases[i].color2 = base->color2;
                }
            }
        }
    }
}

void draw_soldiers(SDL_Renderer *sdlRenderer, struct Base* base, struct Base bases[20]){
    double teta;
    for(int i = 0; i < base->attacking_soldiers; i++){
        if((*((base->soldiers)+i)).is_attacking) {
            (*((base->soldiers)+i)).delay--;
            if ((*((base->soldiers)+i)).delay <= -1) {
                if ((*((base->soldiers)+i)).dest.x - (*((base->soldiers)+i)).x != 0) {
                    teta = atan(((*((base->soldiers)+i)).dest.y - (*((base->soldiers)+i)).y) * 1.0 /
                                ((*((base->soldiers)+i)).dest.x - (*((base->soldiers)+i)).x));
                    if ((*((base->soldiers)+i)).x > (*((base->soldiers)+i)).dest.x) {
                        (*((base->soldiers)+i)).x -= (*((base->soldiers)+i)).speed * cos(teta);
                        (*((base->soldiers)+i)).y -= (*((base->soldiers)+i)).speed * sin(teta);
                    } else {
                        (*((base->soldiers)+i)).x += (*((base->soldiers)+i)).speed * cos(teta);
                        (*((base->soldiers)+i)).y += (*((base->soldiers)+i)).speed * sin(teta);
                    }
                } else {
                    if ((*((base->soldiers)+i)).y > (*((base->soldiers)+i)).dest.y)
                        (*((base->soldiers)+i)).y -= (*((base->soldiers)+i)).speed;
                    else
                        (*((base->soldiers)+i)).y += (*((base->soldiers)+i)).speed;
                }
            } else
                continue;
            if(base->potion <= 2 || base->potion >= 5)
                filledCircleColor(sdlRenderer, (*((base->soldiers)+i)).x, (*((base->soldiers)+i)).y, 3, base->color);
            else if(base->potion >= 3 && base->potion < 5)
                filledCircleColor(sdlRenderer, (*((base->soldiers)+i)).x, (*((base->soldiers)+i)).y, 3, base->color2);
            if (pow((*((base->soldiers)+i)).x - (*((base->soldiers)+i)).dest.x, 2) + pow((*((base->soldiers)+i)).y - (*((base->soldiers)+i)).dest.y, 2) <= 625) {
                (*((base->soldiers)+i)).x = (*((base->soldiers)+i)).dest2.x;
                (*((base->soldiers)+i)).y = (*((base->soldiers)+i)).dest2.y;
                fight(bases, base, i);
                (*((base->soldiers)+i)).is_attacking = false;
            }
        }else
            continue;
    }
}