#include "Map.h"

Map::Map(){
    map_size = 0;
}

Map* Map::Instance(){
    static Map instance;
    return &instance;
}

bool Map::Load(char* file){
    area_list.clear();

    FILE* fin = fopen(file, "r");

    if(fin == nullptr || fin == NULL){
        return false;
    }

    char tileset_file[255];

    fscanf(fin, "%s\n", tileset_file);

    if((tileset_surface = AppSurface::Load(tileset_file)) == false){
        fclose(fin);
        return false;
    }

    fscanf(fin, "%d\n", &map_size);

    for(int y = 0; y < map_size; ++y){
        for(int x = 0; x < map_size; ++x){

            char area_file[255];
            //char tileset_file[255];
            fscanf(fin, "%s ", area_file);
            //fscanf(area_file, "%s : %s . ", area_file);


            Area tmp_area;
            if((tmp_area.Load(area_file)) == false){
                fclose(fin);
                return false;
            }

            tmp_area.tileset_surface = tileset_surface;
            area_list.push_back(tmp_area);
        }
        fscanf(fin, "\n");

    }
    fclose(fin);

    return true;
}

void Map::Save(bool save){
    for(std::vector<Area>::iterator it = area_list.begin();
     it != area_list.end();
     ++it){
        it->Save(save);
    }
}


void Map::Render(SDL_Surface* game_display, int camera_x, int camera_y){
    int map_width = AREA_WIDTH * TILE_SIZE;
    int map_height = AREA_HEIGHT * TILE_SIZE;

    int first_id = -camera_x / map_width;
        first_id = first_id + ((-camera_y / map_height) * map_size);

    for(int i = 0; i < 4; i++){
        int id = first_id + ((i / 2) * map_size) + (i % 2);

        if(id < 0 || id >= area_list.size())continue;
        //if(id < 0){
        //    id = (area_list.size()+id)%area_list.size();
        //}
        //if(id >= area_list.size()){
        //    id%=area_list.size();
        //}

        int X = ((id % map_size) * map_width) + camera_x;
        int Y = ((id / map_size) * map_height)+ camera_y;

        area_list[id].Render(game_display, X, Y);
    }
}

void Map::Cleanup(){
    if(tileset_surface){
        SDL_FreeSurface(tileset_surface);
    }
    area_list.clear();
}


Area* Map::GetArea(int x, int y){
    int area_w = AREA_WIDTH  * TILE_SIZE;
    int area_h = AREA_HEIGHT * TILE_SIZE;

    int index = x / area_w;
    index = index + ((y / area_h) * map_size);

    if(index < 0 || area_list.size() <= index){
        return nullptr;
    }

    return &area_list[index];
}

Tile* Map::GetTile(int x, int y){
    int area_w = AREA_WIDTH  * TILE_SIZE;
    int area_h = AREA_HEIGHT * TILE_SIZE;

    Area* area = GetArea(x, y);

    if(area == nullptr){
        return nullptr;
    }

    x %= area_w;
    y %= area_h;

    return area->GetTile(x, y);
}

void Map::SetTile(int x, int y, Tile new_tile){
    int area_w = AREA_WIDTH  * TILE_SIZE;
    int area_h = AREA_HEIGHT * TILE_SIZE;

    Area* area = GetArea(x, y);

    if(area == nullptr){
        return;
    }

    x %= area_w;
    y %= area_h;

    area->SetTile(x, y, new_tile);
}

