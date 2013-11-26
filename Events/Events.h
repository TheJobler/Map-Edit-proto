#ifndef __EVENTS_H
#define __EVENTS_H

#include <SDL/SDL.h>

class Events{

    public:
        Events();
        virtual ~Events();

    public:
        virtual void HandleEvent(SDL_Event* event_arg);
        virtual void OnInputFocus();
        virtual void OnInputBlur();
        virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);
        virtual void OnMouseFocus();
        virtual void OnMouseBlur();

        virtual void OnMouseMove(
            int x,
            int y,
            int rel_x,
            int rel_y,
            bool left,
            bool right,
            bool middle
        );

        virtual void OnMouseWheel(bool up, bool down);
        virtual void OnLButtonDown(int x, int y);
        virtual void OnRButtonDown(int x, int y);
        virtual void OnMButtonDown(int x, int y);
        virtual void OnLButtonUp(int x, int y);
        virtual void OnRButtonUp(int x, int y);
        virtual void OnMButtonUp(int x, int y);
        virtual void OnJoyAxis(Uint8 which, Uint8 axis, Uint8 value);
        virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
        virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
        virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);

        virtual void OnJoyBall(
            Uint8 which,
            Uint8 ball,
            Sint16 rel_x,
            Sint16 rel_y
        );

        virtual void Minimize();
        virtual void Restore();
        virtual void Resize(int width, int height);
        virtual void Expose();
        virtual void Exit();

        virtual void OnUser(
            Uint8 type,
            int code,
            void* data_1,
            void* data_2
        );

};

#endif

