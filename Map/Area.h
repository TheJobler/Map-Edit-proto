
#ifndef __AREA_H
#define __AREA_H

#include <SDL/SDL.h>
#include <vector>
#include <string>

#include "Tile.h"
#include "../AppSurface/AppSurface.h"

class Area{
    public:
        Area();

    private:
        std::string* area_name;

    public:
        SDL_Surface* tileset_surface;
        std::vector<Tile> tile_list;

    public:
        bool Load(char* file);
        bool Save(bool save = true);
        void Render(SDL_Surface* game_display, int area_x, int area_y);

        Tile* GetTile(int x, int y);
        void  SetTile(int x, int y, Tile new_tile);
};


#endif
