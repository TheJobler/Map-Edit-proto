
#ifndef __TILE_H
#define __TILE_H

#include <vector>

#include "../Define.h"

class Tile{
    public:
        Tile();

    public:
        enum TYPE{
            NONE = 0,
            WALKABLE,
            BARRICADE
        };
        enum CORNERTAG{
            GRASS = 0x00000000,
            DIRT  = 0x00000001,
            WATER = 0x00000002
        };

        int ur;//upper right id
        int lr;//lower right id
        int ul;//upper left  id
        int ll;//lower left  id

    public:
        int type_id;
        int tile_id;
        int transition_value;

        int GetTileID();
        //int height;
};

#endif
