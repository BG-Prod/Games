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

#include "Person.h"

Person::Person()
{
    //ctor
}

Person::Person(string _firstName, string _lastName, int _age, int _satisfaction, int _value, int _id, string _craft, string _sex, string _species)
{
    firstName = _firstName;
    lastName = _lastName;
    age = _age;
    satisfaction = _satisfaction;
    value = _value;
    id = _id;
    craft = _craft;
    sex = _sex;
    species = _species;
}

Person::~Person()
{
    //dtor
}
