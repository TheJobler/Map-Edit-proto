#ifndef __STATE_H
#define __STATE_H

#include "../Events/Events.h"

template<class _StateMaster>
class State : public Events{

    public:
        virtual ~State(){}

        virtual void Enter(_StateMaster*)=0;
        virtual void Execute(_StateMaster*)=0;
        virtual void Exit(_StateMaster*)=0;

        virtual void Render(SDL_Surface* display_surface)=0;

};

#endif
