#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
char *getCardName(int value){
    char *val = malloc(3 * sizeof(int));
    switch (value){
        case 1:
            return "Ace";
        case 11: 
            return "Jack";
        case 12:
            return "Queen";
        case 13: 
            return "King";
        default:
            sprintf(val, "%d", value);
            return val;
    }
}

char *getCardSuit(int suit){
    switch(suit){
        case 0:
            return "Hearts";
        case 1:
            return "Diamonds";
        case 2:
            return "Clubs";
        case 3:
            return "Spades";
        deafult:
            return NULL;
    }
}

char *getCardInfo(Card card){
    char *cardInfo = malloc(20 * sizeof(char));
    sprintf(cardInfo, "%s of %s", getCardName(card.value), getCardSuit(card.suit));
    return cardInfo;
}

void newContainer(Container **address, int size){
    *address = malloc(size * sizeof(Container));
    if(*address == NULL) {
        fprintf(stderr, "Could not create array\n");
        exit(1);
    }
    
}

void newCards(Card **address, int size){
    *address = malloc(size * sizeof(Card));
    if(*address == NULL) {
        fprintf(stderr, "Could not create array\n");
        exit(1);
    }
    
}

void resizeContainer(Container **address, int size){
    *address = realloc(*address, size * sizeof(Container));
    if(*address == NULL) {
        fprintf(stderr, "Could not resize array\n");
        exit(1);
    }
}

void resizeCards(Card **address, int size){
    *address = realloc(*address, size * sizeof(Container));
    if(*address == NULL) {
        fprintf(stderr, "Could not resize array\n");
        exit(1);
    }
}