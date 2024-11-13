#include <stdio.h>
#include <string.h>

#define NUM_TEAMS 10
#define SQUAD_SIZE 11
#define MAX_PLAYER_NAME_SIZE 25
#define MAX_TEAM_NAME_SIZE 20
#define MAX_PLAYER_POSITION_SIZE 20

typedef struct {
    int day;
    int month;
    int year;
} age_t;

typedef struct {
    char player_name[MAX_PLAYER_NAME_SIZE];
    int kit_number;
    char team_name[MAX_TEAM_NAME_SIZE];
    age_t age;
    char player_position[MAX_PLAYER_POSITION_SIZE]; 
} player_t;

typedef struct {
    char team_name[MAX_TEAM_NAME_SIZE];
    player_t players[SQUAD_SIZE];
    int ActiveSize;
} team_t;

team_t teams[NUM_TEAMS];
int team_count = 0;

void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error();

int main() {

    int choice;
    display_menu();

   // switch case to choose
switch (choice)












}