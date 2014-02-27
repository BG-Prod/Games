#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include <SDL.h>
#include <iostream>

class Generator
{
    protected:
    int m_nombre, m_tempsPrecedent, m_tempsActuel;

    public:
    Generator(int);
    Generator(const Generator &p_generatorACopier);
    ~Generator();
    void generation();

};

#endif // GENERATOR_H_INCLUDED
