#include <stdio.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

#include "gui.h"

int main(int argc, char** argv){
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

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_BGRA8888,
        SDL_TEXTUREACCESS_TARGET,
        300, 200
    );

    SDL_SetRenderTarget(renderer, texture);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 300, 200, 0, 0);

    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);

    initImgui(window, renderer);
    
    int test = 0;

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
                default:
                    break;
            }
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        
        createFrame(test);
        test++;

        ImGui::Begin("image");
        ImGui::Image((ImTextureID)texture, ImVec2(300, 200));
        ImGui::End();
        
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 120, 180, 255, 255);
        SDL_RenderClear(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);
    }

    destroyImgui();
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}