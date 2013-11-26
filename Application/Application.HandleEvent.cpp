#include "Application.h"

void Application::HandleEvent(SDL_Event* event_arg){
    Events::HandleEvent(event_arg);
    ApplicationManager::Instance()->HandleEvent(event_arg);
}

