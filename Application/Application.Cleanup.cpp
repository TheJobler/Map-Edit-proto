//Clean up all of the initialized game assets before
//closing the application

#include "Application.h"

void Application::Cleanup(){

    ApplicationManager::Instance()->
        SetActiveState(ApplicationManager::STATE::NONE);

    SDL_FreeSurface(game_display);
    TTF_Quit();
    SDL_Quit();
}
