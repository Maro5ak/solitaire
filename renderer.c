#include "game.h"
#include "card.h"
#include "utils.h"


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_Texture *loadTexture(char *path){
    SDL_Texture *texture = NULL;
    SDL_Surface *loadSurface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    if(texture == NULL){
        fprintf(stderr, "Couldn't load texture\n");
    }
    SDL_FreeSurface(loadSurface);

    return texture;
}


void loadAssets(char *assets){
    char *path = "/assets/";
    char *imgFile = "c_00_test.png";
    char *textures = malloc(20 * sizeof(char));
    strcat(path, imgFile);
    //textures[0] = path;
    memcpy(&assets, textures, 20 * sizeof(char));

    
}


void drawContainers(){
    const int stock = 2;
    const int goal = 4;
    const int table = 7;
    const int space = 58;
    const int offset = 8;
    const int goalOffset = 182;
    const int yBegin = 100;
    const int yHigherBegin = 15;
    const int h = 50, w = 36;
    SDL_Rect stockRect = {
        .h = h,
        .w = w
    };
    SDL_RenderSetScale(renderer, 3, 3);
        
    for(int i = 0; i < stock; i++){
    
        stockRect.x = offset + space * i;
        stockRect.y = yHigherBegin;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderDrawRect(renderer, &stockRect);
    }
    for(int i = 0; i < table; i++){
    
        stockRect.x = offset + space * i;
        stockRect.y = yBegin;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderDrawRect(renderer, &stockRect);
    }
    
    for(int i = 0; i < goal; i++){
        stockRect.x = goalOffset + space * i;
        stockRect.y = yHigherBegin;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderDrawRect(renderer, &stockRect);
    }
}

void drawCards(Table *tableS, Stock *stockS, Goal *goalS){
    SDL_Texture *texture;
    char *assets = malloc(20 * sizeof(char));
    int table = tableS->size;
    int stock = stockS->size;
    int goal = goalS->size;
    const int space = 58 * 3;
    const int offset = 8 * 3;
    const int goalOffset = 182 * 3;
    const int yBegin = 100 * 3;
    const int yHigherBegin = 15 * 3;
    const int yOffset = 21;
    int h = 150, w = 108;
    SDL_Rect card = {
        .h = h,
        .w = w
    };

    SDL_RenderSetScale(renderer, 1, 1);

    for(int i = 0; i < stock; i++){
        card.x = offset + space * i;
        card.y = yHigherBegin;
        texture = loadTexture("assets/c_00_test.png");
        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderCopy(renderer, texture, NULL, &card);
        //SDL_RenderFillRect(renderer, &card);
        SDL_RenderPresent(renderer);
    }
    
    for(int i = 0; i < table; i++){
        for(int j = 0; j < tableS->tableContainer[i].currentSize; j++){
            card.x = offset + space * i;
            card.y = yBegin + yOffset * j;

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
            SDL_RenderFillRect(renderer, &card);
        }
        
    }
    
    for(int i = 0; i < goal; i++){
        card.x = goalOffset + space * i;
        card.y = yHigherBegin;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(renderer, &card);
    }
}

void openWindow(Table *table, Stock *stock, Goal *goal, Ruleset ruleset){
    
    bool quit = false;
    SDL_Event e;
    window = SDL_CreateWindow(
        "TO JSOU TY KARTY",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1200,
        800,
        SDL_WINDOW_SHOWN
    );

    if(window == NULL){
        fprintf(stderr, "Couldn't open SDL Window.\n");
        exit(1);
    }
    //CREATE RENDERER
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        fprintf(stderr, "Couldn't create Renderer.\n");
        exit(1);
    }

    //int imgFlags = IMG_INIT_PNG;

    while(!quit){
        
        while(SDL_PollEvent(&e) != 0){
            
            if(e.type == SDL_QUIT){
                quit = true;
            } 
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE:  
                        quit = true;
                        break;
                }
            }
            
            SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
            SDL_RenderClear(renderer);
           

            drawContainers();
            drawCards(table, stock, goal);
            
            //Update screen
            SDL_RenderPresent(renderer);

        }

    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}