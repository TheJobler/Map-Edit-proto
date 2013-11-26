#ifndef __FPS_CONTROL_H
#define __FPS_CONTROL_H

#include <SDL/SDL.h>

class FPSControl{
    private:
        FPSControl();
        FPSControl(const FPSControl&);
        FPSControl* operator=(FPSControl&);

    private:
        int old_time;
        int previous_time;
        int frames;
        int num_frames;

        float speed_factor;

    public:
        static FPSControl* Instance();
        void Loop();
        int GetFPS();
        float GetSpeed();
};

#endif
