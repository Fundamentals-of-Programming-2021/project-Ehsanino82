#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "players.h"


struct Player* add_player(struct Player* head_players, char username[50], int p){
    struct Player* link = (struct Player*)(malloc(sizeof(struct Player)));
    link->point = p;
    strcpy(link->name, username);
    link->next = head_players;
    return link;
}

struct Player* search_player(char username[50], struct Player* head_players){
    int flag = 0;
    struct Player* user;
    user = head_players;
    while(user != NULL){
        if(strcmp(user->name, username) == 0)
            flag++;
        if(flag)
            return user;
        user = user->next;
    }
    return NULL;
}

struct Player* read_datas(struct Player* head_players){
    FILE* fp;
    fp = fopen("players.txt", "r");
    char line[100];
    char username[100];
    int point;
    while(fscanf(fp, "%[^\n]s", line) != EOF) {
        sscanf(line, "%s %d", username, &point);
        head_players = add_player(head_players, username, point);
        fscanf(fp, "\n");
    }
    return head_players;
}

void add_datas(struct Player current, struct Player* head_players){
    while(head_players->next != NULL){
        if(strcmp(head_players->name, current.name) == 0) {
            head_players->point = current.point;
            break;
        }
        head_players = head_players->next;
    }
}

int find_best(char best[50], int bestie, struct Player* head_players){
    struct Player* user;
    user = head_players;
    while(user->next != NULL){
        if(bestie <= user->point){
            bestie = user->point;
            strcpy(best, user->name);
        }
        user = user->next;
    }
    return bestie;
}

void save_datas(struct Player* head_players){
    FILE* fp;
    fp = fopen("players.txt", "w");
    struct Player* user;
    user = head_players;
    while(user->next != NULL) {
        fprintf(fp, "%s %d\n", user->name, user->point);
        user = user->next;
    }
}