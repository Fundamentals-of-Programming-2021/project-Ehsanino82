#ifndef MAIN_C_LOGIC_H
#define MAIN_C_LOGIC_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "maps.h"

void produce_soldier(struct Base* base);
void attack(struct Base* base);
void fight(struct Base bases[20], struct Base* base, int n);
int check_win(struct Base bases[20]);
void artificial_intelligence(struct Base bases[20]);
void check_collision(struct Base bases[20]);
void speed_up(struct Base* base);
void speed_down(struct Base* base);
void get_potion(struct Base bases[20], struct Potion potions[4]);
void check_attacking(struct Base* base);

#endif //MAIN_C_LOGIC_H
