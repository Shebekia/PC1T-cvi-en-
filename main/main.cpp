#include <stdio.h>
#include <stdlib.h>
#include "database.h"

int main() {
    int choice;
    loadDatabase();

    do {
        printf("\n--- Databaze hudebnich skupin ---\n");
        printf("1. Pridat skupinu\n");
        printf("2. Pridat hodnoceni\n");
        printf("3. Upravit skupinu\n");
        printf("4. Smazat skupinu\n");
        printf("5. Vypsat skupiny\n");
        printf("6. Ulozit a ukoncit\n");
        printf("Vyberte moznost: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBand();
            break;
        case 2:
            addRating();
            break;
        case 3:
            editBand();
            break;
        case 4:
            deleteBand();
            break;
        case 5:
            listBands();
            break;
        case 6:
            saveDatabase();
            printf("Data byla ulozena.\n");
            break;
        default:
            printf("Neplatna volba, zkuste znovu.\n");
        }
    } while (choice != 6);

    return 0;
}
