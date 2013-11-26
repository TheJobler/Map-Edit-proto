
#include "AppSurface.h"

AppSurface::AppSurface(){
}

AppSurface* AppSurface::Instance(){
    static AppSurface instance;
    return &instance;
}


SDL_Surface* AppSurface::Load(char* file){

    SDL_Surface* temp_surface   = nullptr;
    SDL_Surface* return_surface = nullptr;

    if( (temp_surface = IMG_Load(file)) == nullptr){
        return nullptr;
    }

    return_surface = SDL_DisplayFormatAlpha(temp_surface);
    SDL_FreeSurface(temp_surface);

    return return_surface;
}


bool AppSurface::Draw(SDL_Surface* destination, SDL_Surface* source, int x, int y){

    if(destination == nullptr || source == nullptr){
        return false;
    }

    SDL_Rect destination_rect;
    destination_rect.x = x;
    destination_rect.y = y;

    SDL_BlitSurface(source,nullptr,destination,&destination_rect);

    return true;
}

bool AppSurface::Draw(
SDL_Surface* destination, SDL_Surface* source,
int dest_x, int dest_y, int source_x, int source_y,
int width, int height)
{
    if(destination == nullptr || source == nullptr){
        return false;
    }

    SDL_Rect destination_rect;
    destination_rect.x = dest_x;
    destination_rect.y = dest_y;

    SDL_Rect source_rect;
    source_rect.x = source_x;
    source_rect.y = source_y;
    source_rect.w = width;
    source_rect.h = height;

    SDL_BlitSurface(source,&source_rect,destination,&destination_rect);

    return true;
}
