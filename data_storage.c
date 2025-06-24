#include <stdio.h>
#include "data_storage.h"

void saveTeamsToFile(const char *filename, Team *teams, int teamCount) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < teamCount; i++) {
        fprintf(file, "%s,%d,%d,%d\n", teams[i].name, teams[i].points, teams[i].gf, teams[i].gc);
    }

    fclose(file);
}

void loadTeamsFromFile(const char *filename, Team *teams, int *teamCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    *teamCount = 0;
    while (fscanf(file, "%[^,],%d,%d,%d\n", teams[*teamCount].name, &teams[*teamCount].points, &teams[*teamCount].gf, &teams[*teamCount].gc) == 4) {
        (*teamCount)++;
    }

    fclose(file);
}