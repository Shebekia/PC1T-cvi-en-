#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

Band* head = NULL;

void loadDatabase() {
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Nepodarilo se otevrit soubor pro cteni. Mozna jeste neexistuje.\n");
        return;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Odebrání '\n' na konci

        Band* newBand = (Band*)malloc(sizeof(Band));
        if (newBand == NULL) {
            printf("Chyba alokace pameti.\n");
            fclose(file);
            return;
        }

        strcpy(newBand->name, buffer); // Název skupiny
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(newBand->zanr, buffer); // Žánr skupiny

        newBand->ratings = NULL;
        newBand->next = head;
        head = newBand;

        while (fgets(buffer, sizeof(buffer), file)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, "END") == 0) break;

            Rating* newRating = (Rating*)malloc(sizeof(Rating));
            if (newRating == NULL) {
                printf("Chyba alokace pameti.\n");
                fclose(file);
                return;
            }

            newRating->rating = atoi(buffer); // Hodnocení
            fgets(buffer, sizeof(buffer), file);
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(newRating->comment, buffer); // Komentáø

            newRating->next = newBand->ratings;
            newBand->ratings = newRating;
        }
    }

    fclose(file);
    printf("Databaze byla nactena ze souboru.\n");
}

void saveDatabase() {
    FILE* file = fopen("database.txt", "w");
    if (file == NULL) {
        printf("Nepodarilo se otevrit soubor pro zapis.\n");
        return;
    }

    Band* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n%s\n", current->name, current->zanr);

        Rating* rating = current->ratings;
        while (rating != NULL) {
            fprintf(file, "%d\n%s\n", rating->rating, rating->comment);
            rating = rating->next;
        }
        fprintf(file, "END\n"); // Ukonèení hodnocení pro tuto skupinu

        current = current->next;
    }

    fclose(file);
    printf("Databaze byla ulozena do souboru.\n");
}

void addBand() {
    Band* newBand = (Band*)malloc(sizeof(Band));
    if (newBand == NULL) {
        printf("Chyba alokace pameti.\n");
        return;
    }

    printf("Zadejte nazev skupiny: ");
    scanf("%s", newBand->name);
    printf("Zadejte zanr skupiny: ");
    scanf("%s", newBand->zanr);
    newBand->ratings = NULL;
    newBand->next = head;
    head = newBand;

    printf("Skupina byla pridana.\n");
}

void addRating() {
    char name[50];
    printf("Zadejte nazev skupiny, ktere chcete pridat hodnoceni: ");
    scanf("%s", name);

    Band* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            Rating* newRating = (Rating*)malloc(sizeof(Rating));
            if (newRating == NULL) {
                printf("Chyba alokace pameti.\n");
                return;
            }

            printf("Zadejte hodnoceni (0-10): ");
            scanf("%d", &newRating->rating);
            getchar(); // odstranìní '\n' ze vstupu
            printf("Zadejte komentar: ");
            fgets(newRating->comment, 200, stdin);
            newRating->comment[strcspn(newRating->comment, "\n")] = '\0'; // odstranìní '\n'

            newRating->next = current->ratings;
            current->ratings = newRating;

            printf("Hodnoceni bylo pridano.\n");
            return;
        }
        current = current->next;
    }

    printf("Skupina nenalezena.\n");
}

void editBand() {
    char name[50];
    printf("Zadejte nazev skupiny k uprave: ");
    scanf("%s", name);

    Band* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Novy nazev skupiny: ");
            scanf("%s", current->name);
            printf("Novy zanr skupiny: ");
            scanf("%s", current->zanr);
            printf("Skupina byla upravena.\n");
            return;
        }
        current = current->next;
    }

    printf("Skupina nenalezena.\n");
}

void deleteBand() {
    char name[50];
    printf("Zadejte nazev skupiny k odstraneni: ");
    scanf("%s", name);

    Band* current = head;
    Band* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }

            Rating* rating = current->ratings;
            while (rating != NULL) {
                Rating* temp = rating;
                rating = rating->next;
                free(temp);
            }

            free(current);
            printf("Skupina byla odstranena.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Skupina nenalezena.\n");
}

void listBands() {
    Band* current = head;
    printf("\n--- Seznam skupin ---\n");

    while (current != NULL) {
        printf("%s | Zanr: %s\n", current->name, current->zanr);
        Rating* rating = current->ratings;
        int i = 1;

        while (rating != NULL) {
            printf("  Hodnoceni %d: %d - %s\n", i++, rating->rating, rating->comment);
            rating = rating->next;
        }

        current = current->next;
    }
}
