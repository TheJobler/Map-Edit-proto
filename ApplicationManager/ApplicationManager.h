#ifndef __APPLICATION_MANAGER_H
#define __APPLICATION_MANAGER_H

#include "../StateMachine/StateMachine.h"

class ApplicationManager{
    private:
        ApplicationManager();
        ApplicationManager(const ApplicationManager&);
        ApplicationManager* operator=(const ApplicationManager&);

    public:
        enum STATE{
            NONE = 0,
            INTRO,
            EDIT,
            MENU,
            PAUSE,
            OPTIONS,
            SAVE,
            LOAD,
            RESET
        };

    public:
        StateMachine<ApplicationManager>* state_machine;

    public:
        static ApplicationManager* Instance();

        void Loop();
        void HandleEvent(SDL_Event* event);
        void Render(SDL_Surface* display_surface);

        void SetActiveState(int state_id);
        StateMachine<ApplicationManager>* GetFSM()const;

};

#endif
