#include "gui.h"

void initImgui(SDL_Window *w, SDL_Renderer *r)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(w, r);
    ImGui_ImplSDLRenderer2_Init(r);
}

void createFrame(int test)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGui::NewFrame();
    ImGui::Begin("test");
    ImGui::Text("%d", test);
    ImGui::End();
}

void destroyImgui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}