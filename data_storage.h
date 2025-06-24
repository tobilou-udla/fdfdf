#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <stdio.h>

// Structure for Team
typedef struct {
    char name[30];
    int points;
    int gf; // Goals For
    int gc; // Goals Against
} Team;

// Structure for Player
typedef struct {
    char name[30];
    char team[30];
    int goals;
} Player;

// Function to save team data to a .txt file
void saveTeamsToFile(const char *filename, Team *teams, int teamCount);

// Function to load team data from a .txt file
void loadTeamsFromFile(const char *filename, Team *teams, int *teamCount);

#endif // DATA_STORAGE_H