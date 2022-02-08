#include "card.h"
#include "utils.h"

int getRandom(int max){
    return rand() % max;
}

void shuffleDeck(Deck *deck){
    int j;
    Card temp;
    for(int i = MAX_DECK_SIZE-1; i > 0; i--){
        j = getRandom(i);
        temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void fillDeck(Deck *deck, Suit suit, int index, bool color){
    for(int i = 1; i <= 13; i++){
        deck->cards[index+i-1].value = i;
        deck->cards[index+i-1].suit = suit;
        deck->cards[index+i-1].color = color;
        deck->cards[index+i-1].visible = false;
    }
}

void createDeck(Deck *deck){
    //Color bool; 1 = RED, 0 = BLACK
    fillDeck(deck, Hearts, 0, 1); 
    fillDeck(deck, Diamonds, 13, 1); 
    fillDeck(deck, Clubs, 26, 0);
    fillDeck(deck, Spades, 39, 0);
}

void deckInit(Deck *deck){
    newCards(&deck->cards, MAX_DECK_SIZE);
    deck->size = MAX_DECK_SIZE;
    createDeck(deck);
}