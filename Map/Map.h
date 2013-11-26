
#ifndef __MAP_H
#define __MAP_H

#include "Area.h"

class Map{
    private:
        Map();
        Map(const Map&);
        Map* operator=(const Map&);
        //typedef std::map<char*, char*> std::map<area_f, tileset_f>;

    public:
        static Map* Instance();
        std::vector<Area> area_list;
        //std::map<area_f, tileset_f> area_map;
        int map_size;

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//  I plan on making a change to the format of the map files                           //
//  from:                                                                              //
//                                                                                     //
//      tileset_file\n                                                                 //
//      map_size                                                                       //
//      area_file area_file ... area_file"\n"                                          //
//      ...       ...       ... area_file"\n"                                          //
//      area_file area_file ... area_file"\n"                                          //
//                                                                                     //
//  To:                                                                                //
//                                                                                     //
//      map_size                                                                       //
//      area_file:tileset_file area_file:tileset_file ... area_file:tileset_file       //
//      area_file:tileset_file area_file:tileset_file ... area_file:tileset_file       //
//      ...                                                                            //
//      area_file:tileset_file area_file:tileset_file ... area_file:tileset_file       //
//                                                                                     //
//  this will allow each map to have its own tileset if necessary                      //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////



    private:
        SDL_Surface* tileset_surface;

    public:
        bool Load(char* file);
        void Save(bool save);
        void Render(SDL_Surface* game_display, int camera_x, int camera_y);
        void Cleanup();
        Area* GetArea(int x, int y);
        Tile* GetTile(int x, int y);
        void  SetTile(int x, int y, Tile new_tile);
};

#endif
