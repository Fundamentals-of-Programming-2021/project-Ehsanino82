#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct Soldier{
    int x;
    int y;
    SDL_Point src;
    SDL_Point dest;
    SDL_Point dest2;
    int delay;
    bool is_attacking;
    int id;
};

struct Base{
    Sint16 x;
    Sint16 y;
    Uint32 color;
    Uint32 color2;
    int number_of_soldiers;
    int attacking_soldiers;
    struct Soldier soldiers[200];
    int id;
};

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

void generate_random_base(struct Base bases[10], Uint32 colors[5], Uint32 colors2[5]){
    srand(time(0));
    bases[0].x = 60;
    bases[0].y = 60;
    bases[0].color = colors[0];
    bases[0].color2 = colors2[0];
    bases[0].id = 0;
    bases[0].number_of_soldiers = 0;
    bases[0].attacking_soldiers = 0;
    int flag = 0;
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
            bases[i].number_of_soldiers = 0;
            bases[i].attacking_soldiers = 0;
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
            bases[i].number_of_soldiers = 0;
            bases[i].attacking_soldiers = 0;
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
            bases[i].number_of_soldiers = 30;
            bases[i].attacking_soldiers = 0;
        }else {
            i--;
            flag = 0;
        }
    }
}

void generate_bases1(struct Base bases[20], Uint32 colors[5], Uint32 colors2[5]) {
    for(int i = 0; i < 8; i++){
        bases[i].x = 200;
        bases[i].y = 35 + (i * 70);
        bases[i].color = colors[0];
        bases[i].color2 = colors2[0];
        bases[i].id = 0;
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
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
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
    }
    for(int i = 0; i < 8; i++){
        bases[i + 8].x = 580;
        bases[i + 8].y = 35 + (i * 70);
        bases[i + 8].color = colors[3];
        bases[i + 8].color2 = colors2[3];
        bases[i + 8].id = 3;
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
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
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
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
        bases[i + 5].number_of_soldiers = 0;
        bases[i + 5].attacking_soldiers = 0;
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
        bases[i + 10].number_of_soldiers = 0;
        bases[i + 10].attacking_soldiers = 0;
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
        bases[i + 15].number_of_soldiers = 30;
        bases[i + 15].attacking_soldiers = 0;
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
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
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
        bases[i + 4].number_of_soldiers = 0;
        bases[i + 4].attacking_soldiers = 0;
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
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
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
        bases[i + 12].number_of_soldiers = 0;
        bases[i + 12].attacking_soldiers = 0;
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
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
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
        bases[i].number_of_soldiers = 0;
        bases[i].attacking_soldiers = 0;
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
        bases[i + 4].number_of_soldiers = 0;
        bases[i + 4].attacking_soldiers = 0;
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
        bases[i + 8].number_of_soldiers = 0;
        bases[i + 8].attacking_soldiers = 0;
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
        bases[i + 12].number_of_soldiers = 0;
        bases[i + 12].attacking_soldiers = 0;
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
        bases[i + 16].number_of_soldiers = 30;
        bases[i + 16].attacking_soldiers = 0;
    }
}

void draw_bases(SDL_Renderer *sdlRenderer, struct Base base) {
    Sint16 vx[6] = {base.x-30, base.x-15,base.x+15, base.x+30, base.x+15, base.x-15};
    Sint16 vy[6] = {base.y, base.y - (15 * sqrt(3)), base.y - (15 * sqrt(3)), base.y, base.y + (15 * sqrt(3)), base.y + (15 * sqrt(3))};
    Sint16 vx2[4] = {base.x-10, base.x,base.x+10, base.x};
    Sint16 vy2[4] = {base.y, base.y - 10, base.y, base.y+10};
    filledPolygonColor(sdlRenderer, vx, vy, 6, base.color);
    filledPolygonColor(sdlRenderer, vx2, vy2, 4, base.color2);
    char soldiers[3];
    itoa(base.number_of_soldiers, soldiers, 10);
    stringColor(sdlRenderer, base.x -3, base.y + 13, soldiers, 0xffaa0000);
}

void produce_soldier(struct Base* base){
    base->number_of_soldiers++;
}

void attack(struct Base* base){
    double teta;
    if(base->soldiers[0].dest.x - base->soldiers[0].src.x != 0)
        teta = atan(base->soldiers[0].dest.y - base->soldiers[0].src.y) * 1.0 / (base->soldiers[0].dest.x - base->soldiers[0].src.x);
    for(int i = 0; i < base->number_of_soldiers; i++) {
        base->soldiers[i].is_attacking = true;
        base->soldiers[i].delay = (i/5 * 8);
        base->soldiers[i].x = base->x + ((8 * sin(teta)) * (1 - (i % 5)));
        base->soldiers[i].y = base->y + ((8 * cos(teta)) * (1 - (i % 5)));
        base->soldiers[i].dest.x += ((8 * sin(teta)) * (1 - (i % 5)));
        base->soldiers[i].dest.y += ((8 * cos(teta)) * (1 - (i % 5)));
    }
}

void fight(struct Base bases[20], struct Base* base, int n){
    for(int i = 0; i < 20; i++){
        if(base->soldiers[n].dest2.x == bases[i].x && base->soldiers[n].dest2.y == bases[i].y) {
            if (base->id == bases[i].id) {
                bases[i].number_of_soldiers++;
            } else {
                bases[i].number_of_soldiers--;
                if (bases[i].number_of_soldiers < 0) {
                    bases[i].number_of_soldiers++;
                    bases[i].id = base->id;
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
        if(base->soldiers[i].is_attacking) {
            base->soldiers[i].delay--;
            if (base->soldiers[i].delay <= -1) {
                if (base->soldiers[i].dest.x - base->soldiers[i].x != 0) {
                    teta = atan((base->soldiers[i].dest.y - base->soldiers[i].y) * 1.0 /
                                (base->soldiers[i].dest.x - base->soldiers[i].x));
                    if (base->soldiers[i].x > base->soldiers[i].dest.x) {
                        base->soldiers[i].x -= 3.5 * cos(teta);
                        base->soldiers[i].y -= 3.5 * sin(teta);
                    } else {
                        base->soldiers[i].x += 3.5 * cos(teta);
                        base->soldiers[i].y += 3.5 * sin(teta);
                    }
                } else {
                    if (base->soldiers[i].y > base->soldiers[i].dest.y)
                        base->soldiers[i].y -= 3.5;
                    else
                        base->soldiers[i].y += 3.5;
                }
            } else
                continue;
            filledCircleColor(sdlRenderer, base->soldiers[i].x, base->soldiers[i].y, 3, base->color);
            if (pow(base->soldiers[i].x - base->soldiers[i].dest.x, 2) + pow(base->soldiers[i].y - base->soldiers[i].dest.y, 2) <= 625) {
                base->soldiers[i].x = base->soldiers[i].dest2.x;
                base->soldiers[i].y = base->soldiers[i].dest2.y;
                fight(bases, base, i);
                base->soldiers[i].is_attacking = false;
            }
        }else
            continue;
    }
}

int check_win(struct Base bases[20]){
    int flag = 0;
    int flag2 = 0;
    for(int i = 0; i < 20; i++){
        if(bases[i].id == 0)
            flag++;
        if(bases[i].id >= 1 && bases[i].id <= 3)
            flag2++;
    }
    if(flag == 0)
        return 2;
    else if(flag2 == 0)
        return 1;
    else
        return 0;
}

void artificial_intelligence(struct Base bases[20]){
    srand(time(0));
    int x;
    for(int i = 0; i < 20; i++){
        if(i % 4 == 0 && bases[i].id != 0 && bases[i].id != 4) {
            x = rand() % 20;
            if (bases[i].number_of_soldiers >= 17) {
                for (int j = 0; j < bases[i].number_of_soldiers; j++) {
                    bases[i].soldiers[j].src.x = bases[i].x;
                    bases[i].soldiers[j].src.y = bases[i].y;
                    bases[i].soldiers[j].dest.x = bases[x].x;
                    bases[i].soldiers[j].dest.y = bases[x].y;
                    bases[i].soldiers[j].dest2.x = bases[x].x;
                    bases[i].soldiers[j].dest2.y = bases[x].y;
                }
                attack(&bases[i]);
                bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                bases[i].number_of_soldiers = 0;
            }
        }else if(i % 4 == 1 && bases[i].id != 0 && bases[i].id != 4) {
            if (bases[i].number_of_soldiers >= 22) {
                for (int j = 0; j < 20; j++) {
                    if (bases[j].number_of_soldiers <= (bases[i].number_of_soldiers / 2) && bases[j].id != bases[i].id) {
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            bases[i].soldiers[k].src.x = bases[i].x;
                            bases[i].soldiers[k].src.y = bases[i].y;
                            bases[i].soldiers[k].dest.x = bases[j].x;
                            bases[i].soldiers[k].dest.y = bases[j].y;
                            bases[i].soldiers[k].dest2.x = bases[j].x;
                            bases[i].soldiers[k].dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(i % 4 == 2 && bases[i].id != 0 && bases[i].id != 4){
            if(bases[i].number_of_soldiers >= 28){
                for(int j = 0; j < 20; j++){
                    if(bases[j].number_of_soldiers <= (bases[i].number_of_soldiers / 2) && bases[j].id != bases[i].id) {
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            bases[i].soldiers[k].src.x = bases[i].x;
                            bases[i].soldiers[k].src.y = bases[i].y;
                            bases[i].soldiers[k].dest.x = bases[j].x;
                            bases[i].soldiers[k].dest.y = bases[j].y;
                            bases[i].soldiers[k].dest2.x = bases[j].x;
                            bases[i].soldiers[k].dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(i % 4 == 3 && bases[i].id != 0 && bases[i].id != 4){
            if(bases[i].number_of_soldiers >= 9) {
                for (int j = 0; j < 20; j++) {
                    if (bases[j].number_of_soldiers <= bases[i].number_of_soldiers && bases[j].id != bases[i].id) {
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            bases[i].soldiers[k].src.x = bases[i].x;
                            bases[i].soldiers[k].src.y = bases[i].y;
                            bases[i].soldiers[k].dest.x = bases[j].x;
                            bases[i].soldiers[k].dest.y = bases[j].y;
                            bases[i].soldiers[k].dest2.x = bases[j].x;
                            bases[i].soldiers[k].dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(bases[i].id != 0 && bases[i].id != 4 && bases[i].number_of_soldiers >= 30){
            for (int j = 0; j < 20; j++) {
                if (bases[j].number_of_soldiers < bases[i].number_of_soldiers && bases[j].id != bases[i].id) {
                    for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                        bases[i].soldiers[k].src.x = bases[i].x;
                        bases[i].soldiers[k].src.y = bases[i].y;
                        bases[i].soldiers[k].dest.x = bases[j].x;
                        bases[i].soldiers[k].dest.y = bases[j].y;
                        bases[i].soldiers[k].dest2.x = bases[j].x;
                        bases[i].soldiers[k].dest2.y = bases[j].y;
                    }
                    attack(&bases[i]);
                    bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                    bases[i].number_of_soldiers = 0;
                    break;
                }
            }
        }
    }
}

void check_collision(struct Base bases[20]){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(bases[i].id == bases[j].id)
                continue;
            for(int k = 0; k < bases[i].attacking_soldiers; k++){
                if(bases[i].soldiers[k].is_attacking) {
                    for (int z = 0; z < bases[j].attacking_soldiers; z++) {
                        if(bases[j].soldiers[z].is_attacking) {
                            if (pow(bases[i].soldiers[k].y - bases[j].soldiers[z].y, 2) +
                                pow(bases[i].soldiers[k].x - bases[j].soldiers[z].x, 2) <= 6) {
                                bases[i].soldiers[k].is_attacking = false;
                                bases[j].soldiers[z].is_attacking = false;
                            }
                        }
                    }
                }
            }
        }
    }
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
    SDL_Texture *sdlTexture2 = getImageTexture(sdlRenderer, "../menu.bmp");
    SDL_Texture *sdlTexture3 = getImageTexture(sdlRenderer, "../game.bmp");
    SDL_Texture *sdlTexture4 = getImageTexture(sdlRenderer, "../victory.bmp");
    SDL_Texture *sdlTexture5 = getImageTexture(sdlRenderer, "../loose.bmp");
    SDL_Rect texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};
    SDL_Rect texture_rect2 = {.x=20, .y=20, .w=510, .h=500};
    char username[100] = "";
    SDL_StartTextInput();

    struct Base bases[20];
    Uint32 colors[5] = {0xff0000ff, 0xff00ffff, 0xff00ff00, 0xffffff00, 0xff6e6d6f};
    Uint32 colors2[5] = {0xff000080, 0xff008080, 0xff008000, 0xff808000, 0xff6e6d6f};
    Sint16 x1 = 100, x2 = 110;
    Sint16 y1 = 350, y2 = 380;
    Sint16 x3 = 390;
    Sint16 y3 = 280;
    int t=0;
    int flag = 0;
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
        else if(stage == 3){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            artificial_intelligence(bases);
            if(t % 50 == 0) {
                for (int i = 0; i < 20; i++) {
                    if (bases[i].number_of_soldiers < 30 && bases[i].id != 4)
                        produce_soldier(&bases[i]);
                }
            }
            for(int i = 0; i < 20; i++) {
                draw_bases(sdlRenderer, bases[i]);
                check_collision(bases);
                draw_soldiers(sdlRenderer, &bases[i], bases);
            }
            switch (check_win(bases)) {
                case 0:
                    break;
                case 1:
                    sdlTexture = sdlTexture4;
                    stage = 6; //win
                    break;
                case 2:
                    sdlTexture = sdlTexture5;
                    stage = 7; //loose
                    break;
                default:
                    break;
            }
            // code must be completed to play the game
        }
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
        //Leaderboard page==============================================================================================
        else if(stage == 5){
            // code must be completed to show the leaderboard
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect2);
            stringColor(sdlRenderer, 580, 265, "Best Of Bests:", 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 545, 285, 735, 315, 10, 0xff8c6121);
            roundedRectangleColor(sdlRenderer, 630, 490, 770, 520, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 500, "Back to menu", 0xff8c6121);
        }
        //Leaderboard page end==========================================================================================
        else if(stage == 6){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
        else if(stage == 7){
            SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            roundedRectangleColor(sdlRenderer, 630, 520, 770, 550, 10, 0xff8c6121);
            stringColor(sdlRenderer, 655, 530, "Back to menu", 0xff8c6121);
        }
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
                        generate_random_base(bases, colors, colors2);
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 380 <= sdlEvent.button.y && 410 >= sdlEvent.button.y)
                        stage = 4;
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 420 <= sdlEvent.button.y && 450 >= sdlEvent.button.y)
                        stage = 5;
                }else if(stage == 3){
                    for(int i = 0; i < 20; i++){
                        if(bases[i].x-30 <= sdlEvent.button.x && bases[i].x+30 >= sdlEvent.button.x && bases[i].y-25 <= sdlEvent.button.y && bases[i].y+25 >= sdlEvent.button.y){
                            if(flag == 0 && bases[i].id == 0){
                                flag++;
                                first = i;
                            }else if(flag == 1 && i != first){
                                for(int j = 0; j < bases[first].number_of_soldiers; j++) {
                                    bases[first].soldiers[j].src.x = bases[first].x;
                                    bases[first].soldiers[j].src.y = bases[first].y;
                                    bases[first].soldiers[j].dest.x = bases[i].x;
                                    bases[first].soldiers[j].dest.y = bases[i].y;
                                    bases[first].soldiers[j].dest2.x = bases[i].x;
                                    bases[first].soldiers[j].dest2.y = bases[i].y;
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
                    if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 310 <= sdlEvent.button.y && 340 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases1(bases, colors, colors2);
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 350 <= sdlEvent.button.y && 380 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases2(bases, colors, colors2);
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 390 <= sdlEvent.button.y && 420 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases3(bases, colors, colors2);
                    }
                    else if(500 <= sdlEvent.button.x && 670 >= sdlEvent.button.x && 430 <= sdlEvent.button.y && 460 >= sdlEvent.button.y) {
                        stage = 3;
                        sdlTexture = sdlTexture3;
                        generate_bases4(bases, colors, colors2);
                    }
                    else if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y)
                        stage = 2;
                }else if(stage == 5){
                    if(630 <= sdlEvent.button.x && 770 >= sdlEvent.button.x && 520 <= sdlEvent.button.y && 550 >= sdlEvent.button.y)
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
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        t++;
    }

    SDL_StopTextInput();
    SDL_DestroyWindow(sdlWindow);
    printf("Hello World\n");
    SDL_Quit();
    return 0;
}