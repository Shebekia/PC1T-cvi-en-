#ifndef DATABASE_H
#define DATABASE_H

typedef struct Rating {
    int rating;
    char comment[200];
    struct Rating* next;
} Rating;

typedef struct Band {
    char name[50];
    char zanr[30];
    Rating* ratings;
    struct Band* next;
} Band;

void loadDatabase();
void saveDatabase();
void addBand();
void addRating();
void editBand();
void deleteBand();
void listBands();

#endif
