#include "Map.h"

using namespace std;

Map::Map()
{
    id = 0;
    type = 0;
    hasMoved = false;
    ancestor = NULL;
    position.x(0);
    position.y(0);
    position.w(3840);
    position.h(3072);
    etat = HAUT;
}

Map::~Map()
{
    //dtor
}

void Map::update(Input * in)
{

}

void Map::bot()
{

}

