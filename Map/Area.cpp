
#include "Area.h"

Area::Area(){
    tileset_surface = nullptr;
}

bool Area::Load(char* file){
    area_name = new std::string(file);
    tile_list.clear();
    FILE* fin = fopen(file, "r+");

    if(fin == nullptr){
        return false;
    }

    for(int y = 0; y < AREA_HEIGHT; ++y){
        for(int x = 0; x < AREA_WIDTH; ++x){

            Tile tmp_tile;
            fscanf(fin,"%d->{%d,%d,%d,%d}:%d ",
                   &tmp_tile.tile_id,
                   &tmp_tile.ul,
                   &tmp_tile.ur,
                   &tmp_tile.ll,
                   &tmp_tile.lr,
                   &tmp_tile.type_id
                );
            tile_list.push_back(tmp_tile);

        }
        fscanf(fin, "\n");
    }
    fclose(fin);

    return true;
}

bool Area::Save(bool save){
    if(save){
        bool ret = true;
        FILE* fout = fopen(area_name->c_str(), "w");
        if(fout == nullptr){
            ret = false;
        }
        else{
            for(int i = 0; i < tile_list.size(); ++i){
                if(i%AREA_WIDTH == 0){
                    fprintf(fout, "\n");
                }
                fprintf(fout, "%d->{%d,%d,%d,%d}:%d ",
                        tile_list[i].tile_id,
                        tile_list[i].ul,
                        tile_list[i].ur,
                        tile_list[i].ll,
                        tile_list[i].lr,
                        tile_list[i].type_id
                    );
            }
            fprintf(fout, "\n");
        }
        fclose(fout);
        delete area_name;
        area_name = nullptr;
    }
}

void Area::Render(SDL_Surface* game_display, int area_x, int area_y){
    if(tileset_surface == nullptr){
        return;
    }

    //tileset height and width in number of tiles
    //the TILE_SIZE is the number of pixels in one dimension of the tile
    //dividing the total width of pixels of the tileset (tileset_surface->w)
    //yeilds the number of tiles wide same for height
    int tileset_w = tileset_surface->w / TILE_SIZE;
    int tileset_h = tileset_surface->h / TILE_SIZE;

    int index = 0;

    for(int y = 0; y < AREA_HEIGHT; ++y){
        for(int x = 0; x < AREA_WIDTH; ++x){
            if(tile_list[index].type_id == Tile::TYPE::NONE){
                index++;
                continue;
            }

            int offset_x = area_x + (x * TILE_SIZE);
            int offset_y = area_y + (y * TILE_SIZE);


            //calculate the x and y position of the tile in the tileset
            int tile_x = (tile_list[index].tile_id % tileset_w) * TILE_SIZE;
            int tile_y = (tile_list[index].tile_id / tileset_w) * TILE_SIZE;

            AppSurface::Draw(
                game_display,
                tileset_surface,
                offset_x,
                offset_y,
                tile_x  ,
                tile_y,
                TILE_SIZE,
                TILE_SIZE
            );

            index++;

        }
    }
}


Tile* Area::GetTile(int x, int y){
    int index = 0;

    index = x / TILE_SIZE;
    index = index + ( AREA_WIDTH * (y / TILE_SIZE));

    if(index < 0 || tile_list.size() <= index){
        return nullptr;
    }

    return &tile_list[index];
}

void Area::SetTile(int x, int y, Tile new_tile){
    int index = 0;

    index = x / TILE_SIZE;
    index = index + ( AREA_WIDTH * ( y / TILE_SIZE ) );

    if(index < 0 || tile_list.size() <= index){
        return;
    }
    tile_list[index] = new_tile;
}


















