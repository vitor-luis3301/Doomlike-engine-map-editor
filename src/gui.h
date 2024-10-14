#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL.h>

void initImgui(SDL_Window *w, SDL_Renderer *r);
void createFrame(int test);
void destroyImgui();