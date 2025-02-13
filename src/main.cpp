#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

#include "gui.h"
#include "fileread.h"


int main(int argc, char** argv){
    fileRead fr = fileRead();

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    
    int test = 0;

    SDL_Rect source{0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect destination{0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2};

    SDL_Texture *texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_TARGET, 
        SCREEN_WIDTH*2, SCREEN_HEIGHT*2
    );

    SDL_Rect camera{0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    char *filename = "level.mp";
    fr.init(argv[0], filename);
    Global globalvars = fr.interpret(0);

    int pointCount = 0;
    for (int i = 0; i < globalvars.sectorCount; i++)
        for (int j = 0; j < globalvars.sectors[i].num_walls; j++)
            pointCount++;

    SDL_Point p[pointCount];
    int aux = 0;
    for (int i = 0; i < globalvars.sectorCount; i++)
    {
        for (int j = 0; j < globalvars.sectors[i].num_walls/2; j++)
        {
            p[aux].x = globalvars.walls[i][j*2];
            p[aux].y = globalvars.walls[i][j*2+1];
            aux++;
        }
    }

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        running = false;
                    
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                        camera.x--;
                    else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                        camera.x++;
                default:
                    break;
            }
            //ImGui_ImplSDL2_ProcessEvent(&event);
        }

        destination.x = destination.x - camera.x;
        destination.y = destination.y - camera.y;


        //put yout ImGui widgets here
        //ImGui::Render();
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        SDL_RenderDrawLines(renderer, p, aux);
        

        SDL_SetRenderTarget(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &source, &destination);
        //ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}