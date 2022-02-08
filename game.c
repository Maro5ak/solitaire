#include "card.h"
#include "utils.h"
#include "game.h"

void flipCard(Ruleset ruleset, Stock *stock){
    
    //Check ruleset, cards flip from the top of the STOCK dependning on that, either 1 or 3
    int flip = ruleset.flip3 ? 3 : 1;
    //variables for visibility
    int stock0Size = stock->stockContainer[0].currentSize;
    int stock1Size = stock->stockContainer[1].currentSize;
    if(stock0Size == 0){
        if(ruleset.infinite){
            //Set STOCK 0 to be STOCK 1 size, basically just swap them
            stock->stockContainer[0].currentSize = stock1Size;
            stock0Size = stock1Size;
            stock1Size--;
            resizeCards(&stock->stockContainer[0].cards, stock0Size);
            for(int i = stock1Size; i >= 0; i--){
                stock->stockContainer[0].cards[stock0Size - i] = stock->stockContainer[1].cards[i-1];
                stock->stockContainer[0].cards[stock0Size - i].visible = false;
                
            }
            resizeCards(&stock->stockContainer[1].cards, stock1Size);

        }
        else exit(-1);
    }
     for(int i = flip; i >= 0; i--){
        //Check needed because of 3 card flip, prevents to flip negative
        if(stock0Size == 0) break;
        //Remove TOP (last) card from STOCK 0 and move it to the BOTTOM (first) position of STOCK 1 and update visibility
        stock1Size++;
        stock0Size--;
        resizeCards(&stock->stockContainer[1].cards, stock1Size);
        stock->stockContainer[1].cards[stock1Size-1] = stock->stockContainer[0].cards[stock0Size];
        stock->stockContainer[1].cards[stock1Size-1].visible = true;
        resizeCards(&stock->stockContainer[0].cards, stock0Size);
        
    } 
    
    //update struct variables
    stock->stockContainer[0].currentSize = stock0Size;
    stock->stockContainer[1].currentSize = stock1Size;
}


void beginGameLoop(Table *table, Stock *stock, Goal *goal, Ruleset ruleset){
    flipCard(ruleset, stock);
    openWindow(table, stock, goal, ruleset);
}


void fillContainer(Container table, Container stock){
    for(int i = 0; i < table.currentSize; i++){
        //Grab last element from STOCK and add it to the selected TABLE container 
        table.cards[i] = stock.cards[stock.currentSize-1-i];
    }
    table.cards[table.currentSize-1].visible = true;
}

void deal(Table *table, Stock *stock){
    int initialSize = 1;
    for(int i = 0; i < table->size; i++){
        //Assign default states to each TABLE CONTAINER
        table->tableContainer[i].maxSize = MAX_DECK_SIZE;
        table->tableContainer[i].currentSize = initialSize;
        //Allocate memory to a stack of cards that is going to sit on the TABLE CONTAINER
        newCards(&table->tableContainer[i].cards, initialSize);
        //Fills in the correct ammounts of cards to a TABLE CONTAINER from the STOCK
        fillContainer(table->tableContainer[i], stock->stockContainer[0]);
        //resize STOCK based on the cards removed
        stock->stockContainer[0].currentSize -= initialSize;
        //stock->stockContainer[0].cards = realloc(stock->stockContainer[0].cards, stock->stockContainer[0].currentSize * sizeof(Card));
        resizeCards(&stock->stockContainer[0].cards, stock->stockContainer[0].currentSize);
        initialSize++;
    }
}

void printTable(Table *table, Stock *stock){
    for(int i = 0; i < table->size; i++){
        printf("Table container[%d]: \n", i);
        for(int j = 0; j < table->tableContainer[i].currentSize; j++){
            if(table->tableContainer[i].cards[j].visible) printf("%s\n", getCardInfo(table->tableContainer[i].cards[j]));
            else printf("Unknown\n");
        }
        printf("\n");
    }
    
    printf("Cards left in stock: %d\n", stock->stockContainer[0].currentSize);
}

int init(){
    //Init things
    srand(time(0));
    //Memory allocation and setting up of inital states
    Ruleset ruleset = {.flip3 = 0, .infinite = 1};
    Deck *deck = malloc(sizeof(Deck));
    Table *table = malloc(sizeof(Table));
    Stock *stock = malloc(sizeof(Stock));
    Goal *goal = malloc(sizeof(Goal));
    if(table == NULL || stock == NULL || goal == NULL || deck == NULL) {
        fprintf(stderr, "Couldn't create array.");
        return 1;
    }
    stock->size = 2;
    goal->size = 4;
    table->size = 7;

    //Create a deck, fill with cards and shuffle
    deckInit(deck);
    //Allocate memory for all the needed containers
    newContainer(&stock->stockContainer, stock->size);
    newContainer(&goal->goalContainer, goal->size);    
    newContainer(&table->tableContainer, table->size);
    //Allocate memory for first STOCK container which contains the initial deck and all the deck changes after
    newCards(&stock->stockContainer[0].cards, MAX_DECK_SIZE);
    //STOCK container max sizes - get from max deck size which is 52
    stock->stockContainer[0].maxSize = MAX_DECK_SIZE;
    stock->stockContainer[1].maxSize = MAX_DECK_SIZE;
    stock->stockContainer[1].currentSize = 0;
    
    //copy the initial deck to the first STOCK container for ease of access and rendering
    memcpy(stock->stockContainer[0].cards, deck->cards, sizeof(Card) * MAX_DECK_SIZE);
    stock->stockContainer[0].currentSize = MAX_DECK_SIZE;
    //Distribute cards on the table according to the rules of Solitaire https://en.wikipedia.org/wiki/Klondike_(solitaire)
    deal(table, stock);
    printTable(table, stock);

    free(deck->cards);
    free(deck);

    beginGameLoop(table, stock, goal, ruleset);

    return 0;
}