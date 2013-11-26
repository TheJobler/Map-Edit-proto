
#ifndef __APPLICATION_STATES_H
#define __APPLICATION_STATES_H

#include "../StateMachine/State.h"
#include "../AppSurface/AppSurface.h"
#include "../Camera/Camera.h"
#include "../Map/Map.h"
#include "../Events/Events.h"
#include "../Menu/Menu.h"


class ApplicationManager;


//////////////////////////////////////////////////////////////////////////
/////*======================= APP STATE INTRO ======================*/////
//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////
/////*======================= APP STATE EDIT =======================*/////
//////////////////////////////////////////////////////////////////////////

class AppStateEdit : public State<ApplicationManager>{
    private:
        AppStateEdit();
        AppStateEdit(const AppStateEdit&);
        AppStateEdit* operator=(const AppStateEdit&);

    public:
        SDL_Surface* intro_surface;
        int start_time;

    public:
        static AppStateEdit* Instance();

        virtual void Enter(ApplicationManager* application_manager);
        virtual void Execute(ApplicationManager* application_manager);
        virtual void Exit(ApplicationManager* application_manager);

        virtual void Render(SDL_Surface* display_surface);

        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        void OnMouseMove(
            int x,
            int y,
            int rel_x,
            int rel_y,
            bool left,
            bool right,
            bool middle
        );
        void OnLButtonDown(int x, int y);
        void OnLButtonUp(int x, int y);
        void OnMouseWheel(bool up, bool down);


};


#endif
