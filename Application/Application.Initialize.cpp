#include "Application.h"


bool Application::Initialize(){

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    if(TTF_Init() < 0){
        return false;
    }

    //SDL_SetVideoMode sets the length and width of the screen
    //and initializes the buffering mode
    if((game_display
        = SDL_SetVideoMode(
            WWIDTH, //defined in Define.h
            WHEIGHT,//defined in Define.h
            32,
            SDL_HWSURFACE | SDL_DOUBLEBUF/* | SDL_FULLSCREEN*/)
        ) == nullptr){

        return false;
    }

    //Call tha state machine for the game
    ApplicationManager::Instance()->SetActiveState(ApplicationManager::STATE::INTRO);
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_DELAY/32);
    return true;

}
