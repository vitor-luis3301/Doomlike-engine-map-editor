#ifndef RENDERER_H
#define RENDERER_H

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "globalvars.h"

typedef struct _vec2
{
    double x;
    double y;
} vector2;

typedef struct _sector 
{
    int num_walls;
    int height;
    int elevation;
    unsigned int color;
    unsigned int floor_color;
    unsigned int ceiling_color;
} sector;

typedef struct _wall
{
    vector2 a;
    vector2 b;
    double portal_top_h;
    double portal_bottom_h;
    bool is_portal;
} wall;

void R_Init(SDL_Window *window, game_state *state);
void R_Shutdown();
void R_Render(player *player, game_state *state, double fov);
void R_Draw_Walls(player *player, game_state *state);

#endif