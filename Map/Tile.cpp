#include "Tile.h"

Tile::Tile(){
    this->type_id = Tile::TYPE::NONE;
    this->tile_id = 0;
    this->transition_value = 0;
    this->ul = 0;
    this->ur = 0;
    this->ll = 0;
    this->lr = 0;
}

int Tile::GetTileID(){
    return tile_id;
}


