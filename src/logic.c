#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "maps.h"

void produce_soldier(struct Base* base){
    base->number_of_soldiers++;
}

void attack(struct Base* base){
    double teta;
    if((*((base->soldiers)+0)).dest.x - (*((base->soldiers)+0)).src.x != 0)
        teta = atan((*((base->soldiers)+0)).dest.y - (*((base->soldiers)+0)).src.y) * 1.0 / ((*((base->soldiers)+0)).dest.x - (*((base->soldiers)+0)).src.x);
    for(int i = 0; i < base->number_of_soldiers; i++) {
        (*((base->soldiers)+i)).is_attacking = true;
        (*((base->soldiers)+i)).delay = (i / 5 * 8);
        (*((base->soldiers)+i)).x = base->x + ((8 * sin(teta)) * (1 - (i % 5)));
        (*((base->soldiers)+i)).y = base->y + ((8 * cos(teta)) * (1 - (i % 5)));
        (*((base->soldiers)+i)).dest.x += ((8 * sin(teta)) * (1 - (i % 5)));
        (*((base->soldiers)+i)).dest.y += ((8 * cos(teta)) * (1 - (i % 5)));
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
        if(i % 4 == 0 && bases[i].id != 0 && bases[i].id != 4 && !bases[i].is_attacking) {
            x = rand() % 20;
            if (bases[i].number_of_soldiers >= 17) {
                if(bases[i].max / 2 < bases[i].number_of_soldiers || bases[i].max > bases[i].number_of_soldiers * 3) {
                    bases[i].soldiers = (struct Soldier *)realloc(bases[i].soldiers, bases[i].number_of_soldiers * 2 * sizeof(struct Soldier));
                    bases[i].max = 2 * bases[i].number_of_soldiers;
                }
                bases[i].is_attacking = true;
                for (int j = 0; j < bases[i].number_of_soldiers; j++) {
                    (*((bases[i].soldiers)+j)).speed = 3.5;
                    if(bases[i].potion == 3)
                        (*((bases[i].soldiers)+j)).speed = 7;
                    if(bases[i].potion == 4)
                        (*((bases[i].soldiers)+j)).speed = 2;
                    (*((bases[i].soldiers)+j)).src.x = bases[i].x;
                    (*((bases[i].soldiers)+j)).src.y = bases[i].y;
                    (*((bases[i].soldiers)+j)).dest.x = bases[x].x;
                    (*((bases[i].soldiers)+j)).dest.y = bases[x].y;
                    (*((bases[i].soldiers)+j)).dest2.x = bases[x].x;
                    (*((bases[i].soldiers)+j)).dest2.y = bases[x].y;
                }
                attack(&bases[i]);
                bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                bases[i].number_of_soldiers = 0;
            }
        }else if(i % 4 == 1 && bases[i].id != 0 && bases[i].id != 4 && !bases[i].is_attacking) {
            if (bases[i].number_of_soldiers >= 22) {
                if(bases[i].max / 2 < bases[i].number_of_soldiers || bases[i].max > bases[i].number_of_soldiers * 3) {
                    bases[i].soldiers = (struct Soldier *)realloc(bases[i].soldiers, bases[i].number_of_soldiers * 2 * sizeof(struct Soldier));
                    bases[i].max = 2 * bases[i].number_of_soldiers;
                }
                for (int j = 0; j < 20; j++) {
                    if (bases[j].number_of_soldiers <= (bases[i].number_of_soldiers / 2) && bases[j].id != bases[i].id) {
                        bases[i].is_attacking = true;
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            (*((bases[i].soldiers)+k)).speed = 3.5;
                            if(bases[i].potion == 3)
                                (*((bases[i].soldiers)+k)).speed = 7;
                            if(bases[i].potion == 4)
                                (*((bases[i].soldiers)+k)).speed = 2;
                            (*((bases[i].soldiers)+k)).src.x = bases[i].x;
                            (*((bases[i].soldiers)+k)).src.y = bases[i].y;
                            (*((bases[i].soldiers)+k)).dest.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest.y = bases[j].y;
                            (*((bases[i].soldiers)+k)).dest2.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(i % 4 == 2 && bases[i].id != 0 && bases[i].id != 4 && !bases[i].is_attacking){
            if(bases[i].number_of_soldiers >= 28){
                if(bases[i].max / 2 < bases[i].number_of_soldiers || bases[i].max > bases[i].number_of_soldiers * 3) {
                    bases[i].soldiers = (struct Soldier *)realloc(bases[i].soldiers, bases[i].number_of_soldiers * 2 * sizeof(struct Soldier));
                    bases[i].max = 2 * bases[i].number_of_soldiers;
                }
                for(int j = 0; j < 20; j++){
                    if(bases[j].number_of_soldiers <= (bases[i].number_of_soldiers / 2) && bases[j].id != bases[i].id) {
                        bases[i].is_attacking = true;
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            (*((bases[i].soldiers)+k)).speed = 3.5;
                            if(bases[i].potion == 3)
                                (*((bases[i].soldiers)+k)).speed = 7;
                            if(bases[i].potion == 4)
                                (*((bases[i].soldiers)+k)).speed = 2;
                            (*((bases[i].soldiers)+k)).src.x = bases[i].x;
                            (*((bases[i].soldiers)+k)).src.y = bases[i].y;
                            (*((bases[i].soldiers)+k)).dest.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest.y = bases[j].y;
                            (*((bases[i].soldiers)+k)).dest2.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(i % 4 == 3 && bases[i].id != 0 && bases[i].id != 4 && !bases[i].is_attacking){
            if(bases[i].number_of_soldiers >= 9) {
                if(bases[i].max / 2 < bases[i].number_of_soldiers || bases[i].max > bases[i].number_of_soldiers * 3) {
                    bases[i].soldiers = (struct Soldier *)realloc(bases[i].soldiers, bases[i].number_of_soldiers * 2 * sizeof(struct Soldier));
                    bases[i].max = 2 * bases[i].number_of_soldiers;
                }
                for (int j = 0; j < 20; j++) {
                    if (bases[j].number_of_soldiers <= bases[i].number_of_soldiers && bases[j].id != bases[i].id) {
                        bases[i].is_attacking = true;
                        for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                            (*((bases[i].soldiers)+k)).speed = 3.5;
                            if(bases[i].potion == 3)
                                (*((bases[i].soldiers)+k)).speed = 7;
                            if(bases[i].potion == 4)
                                (*((bases[i].soldiers)+k)).speed = 2;
                            (*((bases[i].soldiers)+k)).src.x = bases[i].x;
                            (*((bases[i].soldiers)+k)).src.y = bases[i].y;
                            (*((bases[i].soldiers)+k)).dest.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest.y = bases[j].y;
                            (*((bases[i].soldiers)+k)).dest2.x = bases[j].x;
                            (*((bases[i].soldiers)+k)).dest2.y = bases[j].y;
                        }
                        attack(&bases[i]);
                        bases[i].attacking_soldiers = bases[i].number_of_soldiers;
                        bases[i].number_of_soldiers = 0;
                        break;
                    }
                }
            }
        }else if(bases[i].id != 0 && bases[i].id != 4 && bases[i].number_of_soldiers >= 30 && !bases[i].is_attacking){
            if(bases[i].max / 2 < bases[i].number_of_soldiers || bases[i].max > bases[i].number_of_soldiers * 3) {
                bases[i].soldiers = (struct Soldier *)realloc(bases[i].soldiers, bases[i].number_of_soldiers * 2 * sizeof(struct Soldier));
                bases[i].max = 2 * bases[i].number_of_soldiers;
            }
            for (int j = 0; j < 20; j++) {
                if (bases[j].number_of_soldiers < bases[i].number_of_soldiers && bases[j].id != bases[i].id) {
                    bases[i].is_attacking = true;
                    for (int k = 0; k < bases[i].number_of_soldiers; k++) {
                        (*((bases[i].soldiers)+k)).speed = 3.5;
                        if(bases[i].potion == 3)
                            (*((bases[i].soldiers)+k)).speed = 7;
                        if(bases[i].potion == 4)
                            (*((bases[i].soldiers)+k)).speed = 2;
                        (*((bases[i].soldiers)+k)).src.x = bases[i].x;
                        (*((bases[i].soldiers)+k)).src.y = bases[i].y;
                        (*((bases[i].soldiers)+k)).dest.x = bases[j].x;
                        (*((bases[i].soldiers)+k)).dest.y = bases[j].y;
                        (*((bases[i].soldiers)+k)).dest2.x = bases[j].x;
                        (*((bases[i].soldiers)+k)).dest2.y = bases[j].y;
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
                if((*((bases[i].soldiers)+k)).is_attacking) {
                    for (int z = 0; z < bases[j].attacking_soldiers; z++) {
                        if((*((bases[j].soldiers)+z)).is_attacking) {
                            if (pow((*((bases[i].soldiers)+k)).y - (*((bases[j].soldiers)+z)).y, 2) +
                                pow((*((bases[i].soldiers)+k)).x - (*((bases[j].soldiers)+z)).x, 2) <= 6) {
                                (*((bases[i].soldiers)+k)).is_attacking = false;
                                (*((bases[j].soldiers)+z)).is_attacking = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void speed_up(struct Base* base){
    for(int i = 0; i < base->attacking_soldiers; i++){
        (*((base->soldiers)+i)).speed = 7;
    }
}

void speed_down(struct Base* base){
    for(int i = 0; i < base->attacking_soldiers; i++){
        (*((base->soldiers)+i)).speed = 2;
    }
}

void get_potion(struct Base bases[20], struct Potion potions[4]){
    for(int i = 0; i < 20; i++){
        if(bases[i].potion == 0) {
            for (int j = 0; j < 6; j++) {
                if (potions[j].is_on) {
                    for (int k = 0; k < bases[i].attacking_soldiers; k++) {
                        if ((*((bases[i].soldiers)+k)).is_attacking) {
                            if (pow((*((bases[i].soldiers)+k)).y - potions[j].y, 2) +
                                pow((*((bases[i].soldiers)+k)).x - potions[j].x, 2) <= 100) {
                                potions[j].is_on = false;
                                switch (j) {
                                    case 0:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id == bases[i].id) {
                                                bases[z].potion = 1;
                                                bases[z].timer = 500;
                                            }
                                        }
                                        break;
                                    case 1:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id == bases[i].id) {
                                                bases[z].potion = 2;
                                                bases[z].timer = 500;
                                            }
                                        }
                                        break;
                                    case 2:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id == bases[i].id) {
                                                bases[z].potion = 3;
                                                bases[z].timer = 500;
                                                speed_up(&bases[z]);
                                            }
                                        }
                                        break;
                                    case 3:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id != bases[i].id && bases[z].potion == 0) {
                                                bases[z].potion = 4;
                                                bases[z].timer = 500;
                                                speed_down(&bases[z]);
                                            }else{
                                                bases[z].potion = 5;
                                                bases[z].timer = 500;
                                            }
                                        }
                                        break;
                                    case 4:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id == bases[i].id) {
                                                bases[z].potion = 6;
                                                bases[z].timer = 500;
                                            }
                                        }
                                        break;
                                    case 5:
                                        for (int z = 0; z < 20; z++) {
                                            if (bases[z].id == bases[i].id) {
                                                bases[z].potion = 7;
                                                bases[z].timer = 500;
                                            }
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void check_attacking(struct Base* base){
    int flag = 0;
    for(int i = 0; i < base->attacking_soldiers; i++){
        if(!((*((base->soldiers)+i)).is_attacking))
            flag++;
        else
            break;
    }if(flag == base->attacking_soldiers)
        base->is_attacking = false;
}