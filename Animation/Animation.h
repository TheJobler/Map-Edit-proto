#ifndef __ANIMATION_H
#define __ANIMATION_H

#include <SDL/SDL.h>

class Animation{
    public:
        Animation();

    private:
        int current_frame;////// current frame of the animation
        int frame_increment;//// Howmany frames to increase by
        int frame_rate;///////// how fast the animation shouls occur
        long previous_time;///// the time the previous animation took place

    public:
        bool oscillate;///////// is the animation oscillating or circular?
        int max_frames;///////// total number of frames in the animation

    public:
        void Animate();
        void SetFrameRate(int rate);
        void SetCurrentFrame(int frame);

        int GetCurrentFrame();
};

#endif
