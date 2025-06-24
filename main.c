#include <stdio.h>
#include <string.h>
#include "data_storage.h"
#include "utils.h"

typedef struct {
    int team1Index;
    int team2Index;
} Match;

// Function to find a player in the array
int findPlayer(Player players[], int playerCount, const char *name, const char *team) {
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].name, name) == 0 && strcmp(players[i].team, team) == 0) {
            return i; // Return the index of the player
        }
    }
    return -1; // Player not found
}

int main() {
    // Predetermined teams
    Team teams[3] = {
        {"Barcelona", 0, 0, 0},
        {"Emelec", 0, 0, 0},
        {"LDU Quito", 0, 0, 0}
    };
    int teamCount = 3;

    // Predetermined matches
    Match matches[3] = {
        {0, 1}, // Barcelona vs Emelec
        {1, 2}, // Emelec vs LDU Quito
        {2, 0}  // LDU Quito vs Barcelona
    };
    int matchCount = 3;

    // Array to store players
    Player players[50]; // Assuming a maximum of 50 players
    int playerCount = 0;

    // Ask the user for match results
    for (int match = 0; match < matchCount; match++) {
        printf("\nPartido %d:\n", match + 1);
        int team1Index = matches[match].team1Index;
        int team2Index = matches[match].team2Index;

        printf("%s vs %s\n", teams[team1Index].name, teams[team2Index].name);

        // Ask for goals scored by each team
        printf("Ingrese los goles anotados por %s: ", teams[team1Index].name);
        int goalsTeam1;
        scanf("%d", &goalsTeam1);
        teams[team1Index].gf += goalsTeam1;

        printf("Ingrese los goles anotados por %s: ", teams[team2Index].name);
        int goalsTeam2;
        scanf("%d", &goalsTeam2);
        teams[team2Index].gf += goalsTeam2;

        // Update goals against
        teams[team1Index].gc += goalsTeam2;
        teams[team2Index].gc += goalsTeam1;

        // Ask for players who scored goals for team 1
        for (int j = 0; j < goalsTeam1; j++) {
            printf("Ingrese el nombre del jugador que anotó el gol %d para %s: ", j + 1, teams[team1Index].name);
            char playerName[30];
            scanf("%s", playerName);

            int playerIndex = findPlayer(players, playerCount, playerName, teams[team1Index].name);
            if (playerIndex != -1) {
                // Player already exists, increment goals
                players[playerIndex].goals++;
            } else {
                // Add new player
                Player scorer;
                strcpy(scorer.name, playerName);
                strcpy(scorer.team, teams[team1Index].name);
                scorer.goals = 1;
                players[playerCount++] = scorer;
            }
        }

        // Ask for players who scored goals for team 2
        for (int j = 0; j < goalsTeam2; j++) {
            printf("Ingrese el nombre del jugador que anotó el gol %d para %s: ", j + 1, teams[team2Index].name);
            char playerName[30];
            scanf("%s", playerName);

            int playerIndex = findPlayer(players, playerCount, playerName, teams[team2Index].name);
            if (playerIndex != -1) {
                // Player already exists, increment goals
                players[playerIndex].goals++;
            } else {
                // Add new player
                Player scorer;
                strcpy(scorer.name, playerName);
                strcpy(scorer.team, teams[team2Index].name);
                scorer.goals = 1;
                players[playerCount++] = scorer;
            }
        }

        // Update points based on match result
        if (goalsTeam1 > goalsTeam2) {
            teams[team1Index].points += 3; // Team 1 wins
        } else if (goalsTeam1 < goalsTeam2) {
            teams[team2Index].points += 3; // Team 2 wins
        } else {
            teams[team1Index].points += 1; // Draw
            teams[team2Index].points += 1; // Draw
        }
    }

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