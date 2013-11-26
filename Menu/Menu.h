#ifndef __MENU_H
#define __MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <functional>

#include "../Map/Map.h"
#include "../AppSurface/AppSurface.h"
#include "../Camera/Camera.h"

#define MAX(a,b) ((a > b)? a:b)
#define MIN(a,b) ((a < b)? a:b)

class Menu{
    private:
        Menu();
        Menu(const Menu&);
        Menu* operator=(const Menu&);

    private:

        struct pos{
            int x;
            int y;
        };

        std::vector< std::vector<Tile*> > mMap;
        Tile ActiveTile;

        //Onscreen Text and text formatting
//////////////////////////////////////////////////////////////
        TTF_Font* menu_font;
        SDL_Color font_color;

        std::string active_tile;
        std::string tile_id;
        std::string tile_type;
        std::string tile_coords;
        std::string mouse_coords;

        SDL_Surface* mouse_coordinates_txt;
        SDL_Surface* tile_coordinates_txt;
        SDL_Surface* tile_type_txt;
        SDL_Surface* tile_id_txt;
        SDL_Surface* active_tile_txt;
//////////////////////////////////////////////////////////////

        SDL_Surface* tileset_surface;
        SDL_Surface* bg_surface;
        SDL_Surface* tile_highlight;



    public:
        bool show_menu;
        bool edit_mode;
        bool scroll_mode;
        bool add_mode;
        bool zoom_in;
        bool zoom_out;

        pos position;

        SDL_Surface* zoomOut;

    public:
        static Menu* Instance();

        bool LoadFont(char* file, int font_num = 0);
        void LoadMap();
        void SetTile(int x, int y);
        void SetActiveTile(int tile_id);
        void SetCoords(int rel_x, int rel_y);
        void Loop();
        void Render(SDL_Surface* display_surface);
        void Cleanup();

        //SDL_Surface* ScaleSurface(SDL_Surface* display_surface, Uint16 Width, Uint16 Height);

};

#endif
