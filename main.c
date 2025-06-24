#include <stdio.h>
#include "data_storage.h"
#include "utils.h"

int main() {
    // Example team data
    Team teams[3] = {
        {"Barcelona", 4, 4, 3},
        {"Emelec", 0, 1, 3},
        {"LDU Quito", 4, 3, 2}
    };
    int teamCount = 3;

    // Example player data
    Player players[5] = {
        {"Diaz", "Barcelona", 2},
        {"Mena", "Emelec", 3},
        {"Alzugaray", "LDU Quito", 1},
        {"Martinez", "Barcelona", 1},
        {"Cevallos", "LDU Quito", 2}
    };
    int playerCount = 5;

    // Open a file to write the output
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // Display the standings and write to file
    printf("Tabla de Posiciones:\n");
    fprintf(outputFile, "Tabla de Posiciones:\n");
    printf("Equipo           Puntos GF GC\n");
    fprintf(outputFile, "Equipo           Puntos GF GC\n");
    for (int i = 0; i < teamCount; i++) {
        printf("%-16s %d      %d  %d\n", teams[i].name, teams[i].points, teams[i].gf, teams[i].gc);
        fprintf(outputFile, "%-16s %d      %d  %d\n", teams[i].name, teams[i].points, teams[i].gf, teams[i].gc);
    }

    // Display the top scorers and write to file
    printf("\nGoleadores del Torneo:\n");
    fprintf(outputFile, "\nGoleadores del Torneo:\n");
    printf("Jugador         Equipo          Goles\n");
    fprintf(outputFile, "Jugador         Equipo          Goles\n");
    for (int i = 0; i < playerCount; i++) {
        printf("%-15s %-15s %d\n", players[i].name, players[i].team, players[i].goals);
        fprintf(outputFile, "%-15s %-15s %d\n", players[i].name, players[i].team, players[i].goals);
    }

    // Calculate MVP and write to file
    Player mvp = players[0];
    for (int i = 1; i < playerCount; i++) {
        if (players[i].goals > mvp.goals) {
            mvp = players[i];
        }
    }
    printf("\n🏅 MVP del Torneo: %s (%s) con %d goles.\n", mvp.name, mvp.team, mvp.goals);
    fprintf(outputFile, "\n🏅 MVP del Torneo: %s (%s) con %d goles.\n", mvp.name, mvp.team, mvp.goals);

    // Close the file
    fclose(outputFile);

    return 0;
}