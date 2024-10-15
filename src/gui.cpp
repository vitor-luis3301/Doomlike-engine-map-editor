#include "gui.h"

void initImgui(SDL_Window *w, SDL_Renderer *r)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(w, r);
    ImGui_ImplSDLRenderer2_Init(r);
}

void createFrame(int test, SDL_Texture *texture)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("test");
    ImGui::Text("%d", test);
    ImGui::End();

    ImGui::Begin("image");
    ImGui::Image((ImTextureID)texture, ImVec2(998*2,772*2));
    ImGui::End();
}

void destroyImgui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}