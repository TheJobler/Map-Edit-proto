#include "Animation.h"

Animation::Animation(){

    this->current_frame = 0;
    this->frame_increment = 1;
    this->frame_rate = 100;
    this->max_frames = 0;

    this->oscillate = false;
    this->previous_time = 0;

}

void Animation::Animate(){

    //make sure enough time has passed before updating the frame
    if(previous_time + frame_rate > SDL_GetTicks()){
        return;
    }

    previous_time = SDL_GetTicks();
    current_frame += frame_increment;

    //if a sprite oscillates make sure its animations reflect that
    if(oscillate){
        if(frame_increment > 0){
            if(current_frame >= max_frames){
                frame_increment = -frame_increment;
            }
        }
        else{
            if(current_frame <= 0){
                frame_increment = -frame_increment;
            }
        }
    }
    else{
        if(current_frame >= max_frames){
            current_frame = 0;
        }
    }
}

void Animation::SetFrameRate(int rate){
    frame_rate = rate;
}

void Animation::SetCurrentFrame(int frame){
    current_frame = frame;
}

int Animation::GetCurrentFrame(){
    return current_frame;
}
