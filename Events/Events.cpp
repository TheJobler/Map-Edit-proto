#include "events.h"

Events::Events(){
}

Events::~Events(){
}

void Events::HandleEvent(SDL_Event* event_arg){

    switch(event_arg->type){
        case SDL_ACTIVEEVENT:
        {
            switch(event_arg->active.state)
            {
                case SDL_APPMOUSEFOCUS:{
                    if(event_arg->active.gain){ OnMouseFocus(); }
                    else{ OnMouseBlur(); }
                    break;
                }
                case SDL_APPINPUTFOCUS:{
                    if(event_arg->active.gain){ OnInputFocus(); }
                    else{ OnInputBlur(); }
                    break;
                }
                case SDL_APPACTIVE:{
                    if(event_arg->active.gain){ Restore(); }
                    else{ Minimize(); }
                    break;
                }
            }
            break;
        }

        case SDL_KEYDOWN:
        {
            OnKeyDown(
                event_arg->key.keysym.sym,
                event_arg->key.keysym.mod,
                event_arg->key.keysym.unicode
            );
            break;
        }

        case SDL_KEYUP:
        {
            OnKeyUp(
                event_arg->key.keysym.sym,
                event_arg->key.keysym.mod,
                event_arg->key.keysym.unicode
            );
            break;
        }

        case SDL_MOUSEMOTION:
        {
            OnMouseMove(
                event_arg->motion.x,
                event_arg->motion.y,
                event_arg->motion.xrel,
                event_arg->motion.yrel,
                (event_arg->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
                (event_arg->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT))!= 0,
                (event_arg->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0
            );
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            switch(event_arg->button.button)
            {
                case SDL_BUTTON_LEFT:{
                    OnLButtonDown(event_arg->button.x, event_arg->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:{
                    OnRButtonDown(event_arg->button.x, event_arg->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:{
                    OnMButtonDown(event_arg->button.x, event_arg->button.y);
                    break;
                }
                break;
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            switch(event_arg->button.button)
            {
                case SDL_BUTTON_LEFT:{
                    OnLButtonUp(event_arg->button.x, event_arg->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:{
                    OnRButtonUp(event_arg->button.x, event_arg->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:{
                    OnMButtonUp(event_arg->button.x, event_arg->button.y);
                    break;
                }
                break;
            }
            break;
        }

        case SDL_JOYAXISMOTION:
        {
            OnJoyAxis(
                event_arg->jaxis.which,
                event_arg->jaxis.axis,
                event_arg->jaxis.value
            );
            break;
        }

        case SDL_JOYBALLMOTION:
        {
            OnJoyBall(
                event_arg->jball.which,
                event_arg->jball.ball,
                event_arg->jball.xrel,
                event_arg->jball.yrel
            );
            break;
        }

        case SDL_JOYHATMOTION:
        {
            OnJoyHat(
                event_arg->jhat.which,
                event_arg->jhat.hat,
                event_arg->jhat.value
            );
            break;
        }

        case SDL_JOYBUTTONDOWN:
        {
            OnJoyButtonDown(
                event_arg->jbutton.which,
                event_arg->jbutton.button
            );
            break;
        }

        case SDL_JOYBUTTONUP:
        {
            OnJoyButtonUp(
                event_arg->jbutton.which,
                event_arg->jbutton.button
            );
            break;
        }

        case SDL_QUIT:{
            Exit();
            break;
        }

        case SDL_SYSWMEVENT:{
            break;
        }

        case SDL_VIDEORESIZE:
        {
            Resize(
                event_arg->resize.w,
                event_arg->resize.h
            );
            break;
        }

        case SDL_VIDEOEXPOSE:{
            Expose();
            break;
        }

        default:
        {
            OnUser(
                event_arg->user.type,
                event_arg->user.code,
                event_arg->user.data1,
                event_arg->user.data2
            );
            break;
        }
    }
}


void Events::OnInputFocus(){
}

void Events::OnInputBlur(){
}

void Events::OnKeyDown(SDLKey key, SDLMod mod, Uint16 unicode){
}
void Events::OnKeyUp(SDLKey key, SDLMod, Uint16 unicode){
}
void Events::OnMouseFocus(){
}
void Events::OnMouseBlur(){
}
void Events::OnMouseMove(int x, int y, int rel_x, int rel_y, bool left, bool right, bool middle){
}
void Events::OnMouseWheel(bool up, bool down){
}
void Events::OnLButtonDown(int x, int y){
}
void Events::OnLButtonUp(int x, int y){
}
void Events::OnRButtonDown(int x, int y){
}
void Events::OnRButtonUp(int x, int y){
}
void Events::OnMButtonDown(int x, int y){
}
void Events::OnMButtonUp(int x, int y){
}
void Events::OnJoyAxis(Uint8 which, Uint8 axis, Uint8 value){
}
void Events::OnJoyButtonDown(Uint8 which, Uint8 button){
}
void Events::OnJoyButtonUp(Uint8 which, Uint8 button){
}
void Events::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value){
}
void Events::OnJoyBall(Uint8 which, Uint8 ball, Sint16 rel_x, Sint16 rel_y){
}
void Events::Minimize(){
}
void Events::Restore(){
}
void Events::Resize(int width, int height){
}
void Events::Expose(){
}
void Events::Exit(){
}
void Events::OnUser(Uint8 type, int code, void* data_1, void* data_2){
}

