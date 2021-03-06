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

#ifndef SOUAPP_H
#define SOUAPP_H

#include <vector>

#include <Application.h>
#include <Player.h>
#include <Vaisseau.h>
#include <Screen.h>
#include <Map.h>
#include <Interface.h>
#include <Button.h>


class SoUApp : public Application
{
    public:
        SoUApp();
        virtual ~SoUApp();

        virtual void app();
        virtual void windowAttributes();

        void addHuman(Player * p);
        void addBot(Player * p);

        void pullPlayer(int id);

    protected:
        vector<Player*> players;
        Player * you;

        int whatImage(int a, int b);
        void intro();
        void init();
        void menu();
        void eventsManager();
        void radarManager();
        void saveGame();
        void loadGame();
};

#endif // SOUAPP_H
