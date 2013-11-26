#include "Application.h"

void Application::Render(){

    ApplicationManager::Instance()->Render(game_display);
    SDL_Flip(game_display);
}
