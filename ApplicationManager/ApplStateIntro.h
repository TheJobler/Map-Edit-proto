
#ifndef __APPLICATION_STATE_INTRO_H
#define __APPLICATION_STATE_INTRO_H

#include "../StateMachine/State.h"
#include "../AppSurface/AppSurface.h"

class ApplicationManager;

class AppStateIntro : public State<ApplicationManager>{
    private:
        AppStateIntro();
        AppStateIntro(const AppStateIntro&);
        AppStateIntro* operator=(const AppStateIntro&);

    public:
        SDL_Surface* intro_surface;
        int start_time;

    public:
        static AppStateIntro* Instance();

        virtual void Enter(ApplicationManager* application_manager);
        virtual void Execute(ApplicationManager* application_manager);
        virtual void Exit(ApplicationManager* application_manager);

        virtual void Render(SDL_Surface* display_surface);

};

#endif
