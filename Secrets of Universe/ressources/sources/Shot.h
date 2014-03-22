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

#ifndef SHOT_H
#define SHOT_H

#include <SDL.h>

#include <Object.h>
#include <Image.h>
#include <DisplayDatas.h>


class Shot : public Object
{
    public:
        Shot(Object * o);
        virtual ~Shot();

        void init();
        void use();
        void update();
        bool death();

    protected:
        int vitesse;
        int force;
        const int birth;
        const int lifeTime;
        Image * image;
};

#endif // SHOT_H
