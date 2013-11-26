#include "FPSControl.h"

FPSControl::FPSControl(){
    old_time = 0;
    previous_time = 0;
    speed_factor = 0;
    frames = 0;
    num_frames = 0;
}

FPSControl* FPSControl::Instance(){
    static FPSControl instance;
    return &instance;
}

void FPSControl::Loop(){
    if((unsigned)old_time + 1000 < SDL_GetTicks()){
        old_time = SDL_GetTicks();
        num_frames = frames;
        frames = 0;
    }

    speed_factor = ((SDL_GetTicks() - previous_time) / 1000.0f) * 32.0f;
    previous_time = SDL_GetTicks();
    frames++;
}

int FPSControl::GetFPS(){
    return num_frames;
}

float FPSControl::GetSpeed(){
    return speed_factor;
}
