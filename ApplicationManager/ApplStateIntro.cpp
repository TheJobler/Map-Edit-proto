#include "ApplicationStates.h"
#include "ApplicationManager.h"

AppStateIntro::AppStateIntro(){
    this->intro_surface = nullptr;
}

AppStateIntro* AppStateIntro::Instance(){
    static AppStateIntro instance;
    return &instance;
}

void AppStateIntro::Enter(ApplicationManager* application_manager){
    intro_surface = AppSurface::Load("resources/gfx/gui/Crown.png");
    start_time = SDL_GetTicks();
}

void AppStateIntro::Execute(ApplicationManager* application_manager){
    if(start_time + 3000 < SDL_GetTicks()){
        application_manager->GetFSM()->ChangeState(AppStateEdit::Instance());
    }
}

void AppStateIntro::Exit(ApplicationManager* application_manager){
    if(intro_surface){
        SDL_FreeSurface(intro_surface);
    }
    intro_surface = nullptr;
}

void AppStateIntro::Render(SDL_Surface* display_surface){
    if(intro_surface){
        AppSurface::Draw(display_surface, intro_surface, 0, 0);
    }
}
