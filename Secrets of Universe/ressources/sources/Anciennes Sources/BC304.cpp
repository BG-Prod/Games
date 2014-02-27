#include "BC304.h"


using namespace std;


BC304::BC304(SDL_Surface ** p_images) : Vaisseau()
{
    m_image[HAUT] = p_images[22];
    m_image[BAS] = p_images[23];
    m_image[GAUCHE] = p_images[24];
    m_image[DROITE] = p_images[25];
    m_image[HD] = p_images[26];
    m_image[HG] = p_images[27];
    m_image[BG] = p_images[28];
    m_image[BD] = p_images[29];
    m_image[DETRUIT] = p_images[30];

    m_image[ACTUELLE] = m_image[HAUT];

    m_position.w = m_image[ACTUELLE]->w;
    m_position.h = m_image[ACTUELLE]->h;
}

BC304::BC304(const BC304 &p_BC304ACopier) : Vaisseau()
{
    m_image[ACTUELLE] = m_image[HAUT];
}

BC304::~BC304()
{

}

