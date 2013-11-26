#include "Camera.h"

Camera::Camera(){
    this->x = 0; this->y = 0;
    this->dx = WWIDTH; //AREA_WIDTH * TILE_SIZE * 3
    this->dy = WHEIGHT;//AREA_HEIGHT* TILE_SIZE * 3
    this->target_x = nullptr;
    this->target_y = nullptr;
    this->target_mode = Camera::TARGET_MODE::NORMAL;
}

Camera* Camera::Instance(){
    static Camera instance;
    return &instance;
}

void Camera::Move(int move_x, int move_y){
    int new_x = this->x + move_x;
    int new_y = this->y + move_y;
    int max_x = AREA_WIDTH * TILE_SIZE * 3;
    int max_y = AREA_HEIGHT* TILE_SIZE * 3;

    //prevent camera from moving past the map
    if( (new_x + dx < max_x) && (new_x > 0) ){
        this->x = new_x;
    }
    if( (new_y + dy < max_y) && (new_y > 0) ){
        this->y = new_y;
    }

}


int Camera::Get_x(){
    if(target_x != nullptr){
        if(target_mode == Camera::TARGET_MODE::CENTER){
            return *target_x -(WWIDTH / 2);
        }
        return *target_x;
    }
    return x;
}

int Camera::Get_y(){
    if(target_x != nullptr){
        if(target_mode == Camera::TARGET_MODE::CENTER){
            return *target_y -(WHEIGHT / 2);
        }
        return *target_y;
    }
    return y;
}

void Camera::SetPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Camera::SetTarget(float* x, float* y){
    target_x = x;
    target_y = y;
}
