#ifndef RENDERER_H
#define RENDERER_H

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "globalvars.h"

void R_Init(SDL_Window *window, game_state *state);
void R_Shutdown();
void R_Render(player *player, game_state *state, double fov);
void R_Draw_Walls(player *player, game_state *state);

#endif