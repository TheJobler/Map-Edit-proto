//Application.Execute.h
///////////////////////////////////////////////////////
//This is the main loop of the game
//polls events, and calls the main functions of
//the application.
///////////////////////////////////////////////////////
#include "Application.h"

int Application::Execute(){
    if(this->Initialize() == false){
        return -1;
    }

    SDL_Event* event;

    while(running){
        while(SDL_PollEvent(event)){
              this->HandleEvent(event);
        }
        this->Loop();
        this->Render();
    }
    this->Cleanup();

    return 0;
}
