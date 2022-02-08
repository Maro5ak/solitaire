#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "card.h"


typedef struct{
    bool flip3;
    bool infinite;
} Ruleset;

int init();
void openWindow(Table *table, Stock *stock, Goal *goal, Ruleset ruleset);
void flipCard(Ruleset ruleset, Stock *stock);
void loadAssets(char *assets);

#endif