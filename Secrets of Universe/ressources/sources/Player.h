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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <Crew.h>
#include <Vaisseau.h>

using namespace std;

class Player
{
    public:
        Player();
        Player(int _id, int _xp, int _level, int _team, int _coins, bool _human, string _name, Crew* _crew, Vaisseau* _starship);
        virtual ~Player();

        int getId();
        string getName();
        Vaisseau * getStarship();
        void setStarship(Vaisseau * v);

        void setCoins(int v);
        void addCoins(int v);
        int getCoins();
        int getLevel();

    protected:
        int id, xp, level, team, coins;
        bool human;
        Crew * crew;
        string name;
        Vaisseau * starship;
};

#endif // PLAYER_H
