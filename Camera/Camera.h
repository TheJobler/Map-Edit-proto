#ifndef __CAMERA_H
#define __CAMERA_H

#include <SDL/SDL.h>
#include "../Define.h"

class Camera{
    private:
        Camera();
        Camera(Camera&);
        Camera* operator=(Camera&);

    public:
         enum TARGET_MODE{
            NORMAL = 0,
            CENTER
        };

    private:
        int x;
        int y;

        int dx;
        int dy;

        float* target_x;
        float* target_y;

    public:
        int target_mode;

    public:
        static Camera* Instance();

        void Move(int move_x, int move_y);
        void SetPosition(int x, int y);
        void SetTarget(float* x, float* y);

        int Get_x();
        int Get_y();

};

#endif
