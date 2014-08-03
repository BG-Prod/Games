/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : bgprod@outlook.com
*/

#include "Player.h"

Player::Player()
{
    Player(random(0,999999), 0, 0, random(1,16), random(1000,10000), false, "COMPUTER", new Crew, new Vaisseau(random(0,4095),random(0,4095)));
}

Player::Player(int _id, int _xp, int _level, int _team, int _coins, bool _human, string _name, Crew* _crew, Vaisseau* _starship)
{
    id = _id;
    xp = _xp;
    level = _level;
    team = _team;
    human = _human;
    crew = _crew;
    name = _name;
    starship = _starship;
    coins = _coins;
}

Player::~Player()
{
    if(crew != NULL)
    {
        delete crew;
    }
}

int Player::getId()
{
    return id;
}

string Player::getName()
{
    return name;
}

int Player::getLevel()
{
    return level;
}

Vaisseau * Player::getStarship()
{
    return starship;
}

void Player::setCoins(int v)
{
    coins = v;
}

void Player::addCoins(int v)
{
    coins += v;
}

int Player::getCoins()
{
    return coins;
}

