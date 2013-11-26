////////////////////////////////////////////////////////////////
/////*======================= Notes ======================*/////
////////////////////////////////////////////////////////////////
// Application.h                                              //
//                                                            //
// Author: Steven Shriver                                     //
//          with inspiration from {sdltutorials.com}          //
//                                                            //
//  Application is a singleton object and is the main point   //
//  of a basic game application                               //
//  Test Materials will be temporarily located at the bottom  //
//  of the file.                                              //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Define.h"
#include "../Events/Events.h"
#include "../Animation/Animation.h"
#include "../AppSurface/AppSurface.h"
#include "../FPSControl/FPSControl.h"
#include "../ApplicationManager/ApplicationStates.h"
#include "../ApplicationManager/ApplicationManager.h"


class Application : public Events{

    private://singleton constructors and assignment

        Application();
        Application(Application &app);
        Application& operator=(Application &app);

    private://variables

        //The main display for the application
        SDL_Surface* game_display;

        //is appllication running?
        bool running;

    public:

        //static instance of the application;
        static Application* Instance();

        int Execute();

        bool Initialize();

        void HandleEvent(SDL_Event* event_arg);
        void Exit();
        void Loop();
        void Render();
        void Cleanup();

////////////////////////////////////////////////////////////////
/////*================== TEST MATERIALS ==================*/////
////////////////////////////////////////////////////////////////

    public:
        //void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        //void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

////////////////////////////////////////////////////////////////
};

#endif
