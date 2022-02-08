#ifndef CARD
#define CARD

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DECK_SIZE 52

typedef enum{
    Hearts,
    Diamonds, 
    Clubs,
    Spades
} Suit;


typedef struct{
    int value;
    Suit suit;
    bool visible;
    bool color;
} Card;

typedef struct{
    Card *cards;
    int size;
} Deck;

typedef struct{
    Card *cards;
    int currentSize;
    int maxSize;
} Container;

typedef struct{
    Container *tableContainer;
    int size;
} Table;

typedef struct{
    Container *goalContainer;
    int size;
} Goal;

typedef struct{
    Container *stockContainer;
    int size;
} Stock;


void deckInit(Deck *deck);


#endif