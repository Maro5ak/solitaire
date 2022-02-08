#ifndef UTILS
#define UTILS
#include "card.h"

char *getCardName(int value);
char *getCardSuit(int suit);
char *getCardInfo(Card card);

void newContainer(Container **address, int size);
void newCards(Card **address, int size);

void resizeContainer(Container **address, int size);
void resizeCards(Card **address, int size);
#endif