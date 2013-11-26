#ifndef __APP_SURFACE_H
#define __APP_SURFACE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class AppSurface{
    private:
        AppSurface();
        AppSurface(AppSurface &surface);
        AppSurface* operator=(AppSurface &surface);

    public:

        static AppSurface* Instance();

        //loads image file
        static SDL_Surface* Load(char* file);

        //Takes the source surface and blits it
        //onto the destination surface
        static bool Draw(
            SDL_Surface* destination,
            SDL_Surface* source,
            int x,
            int y
        );

        //Takes a designated portion of the source
        //image and blits it onto the destination
        //surface
        static bool Draw(
            SDL_Surface* destination,
            SDL_Surface* source,
            int dest_x,
            int dest_y,
            int source_x,
            int source_y,
            int width,
            int height
        );
};

#endif
