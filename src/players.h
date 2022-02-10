#ifndef MAIN_C_PLAYERS_H
#define MAIN_C_PLAYERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Player{
    char name[50];
    int point;
    struct Player* next;
};

struct Player* add_player(struct Player* head_players, char username[50], int p);
struct Player* search_player(char username[50], struct Player* head_players);
struct Player* read_datas(struct Player* head_players);
void add_datas(struct Player current, struct Player* head_players);
int find_best(char best[50], int bestie, struct Player* head_players);
void save_datas(struct Player* head_players);

#endif //MAIN_C_PLAYERS_H
