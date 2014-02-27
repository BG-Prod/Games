#include "Environnement.h"


using namespace std;


struct Couple;


Environnement::Environnement()
{
    m_actif = 1;
    m_tirsActifs = -1;
}

Environnement::Environnement(const Environnement &p_EnvironnementACopier)
{
    m_actif = p_EnvironnementACopier.m_actif;
}

Environnement::~Environnement()
{

}

void Environnement::combienDeTirs(Projectile* p_tableauATirs[])
{
    for(int i = 0; i < 20000; i++)
    {
        if(p_tableauATirs[i] != NULL)
        {

        }
    }
}

void Environnement::gerer(Vaisseau *p_tableauObjet[], SDL_Surface* p_ou, SDL_Surface* p_ecran, Input p_in, SDL_Rect p_coor[],int p_listeDeg[], Univers *p_uni, int p_info[][2])
{

    if(m_actif >= 0)
    {
        for(int i = 0; i <= m_actif; i++)
        {
            if(p_tableauObjet[i] != NULL && p_tableauObjet[i]->get("m_alive") == false)
            {
                delete p_tableauObjet[i];
                p_tableauObjet[i] = NULL;
                p_tableauObjet[i] = p_tableauObjet[m_actif];
                if(p_tableauObjet[i]->get("m_alive") == true)
                {
                    p_tableauObjet[i]->update(p_ou, p_ecran, p_in,p_coor, p_listeDeg);
                }
                m_actif--;
            }

            if(p_tableauObjet[i] != NULL && p_tableauObjet[i]->get("m_alive") == true) // COLLISIONS
            {
                p_tableauObjet[i]->update(p_ou, p_ecran, p_in,p_coor, p_listeDeg);
                if(p_tableauObjet[i]->get("m_alive") == false)
                {
                    delete p_tableauObjet[i];
                    p_tableauObjet[i] = NULL;
                }
                if(p_tableauObjet[i] != NULL)
                {
                    for(int j = 0; j <= m_actif; j++)
                    {
                        if(j != i && (p_tableauObjet[j] != NULL) && ((p_tableauObjet[i]->get("m_alive")) != 238))
                        {
                            if((p_tableauObjet[j]->getCouple().coor.x >= p_tableauObjet[i]->getCouple().coor.x + p_tableauObjet[i]->getCouple().image->w)      // trop à droite
                            || (p_tableauObjet[j]->getCouple().coor.x + p_tableauObjet[j]->getCouple().image->w <= p_tableauObjet[i]->getCouple().coor.x) // trop à gauche
                            || (p_tableauObjet[j]->getCouple().coor.y >= p_tableauObjet[i]->getCouple().coor.y + p_tableauObjet[i]->getCouple().image->h) // trop en bas
                            || (p_tableauObjet[j]->getCouple().coor.y + p_tableauObjet[j]->getCouple().image->h <= p_tableauObjet[i]->getCouple().coor.y))  // trop en haut
                            {
                                p_tableauObjet[i]->mobilite(true);
                                p_tableauObjet[j]->mobilite(true);
                            }
                            else
                            {
                                p_tableauObjet[i]->mobilite(false);
                                p_tableauObjet[j]->mobilite(false);
                            }
                        }

                    }
                }

            }
        }

        for(int i = 0; i <= m_actif; i++)
        {
            if(p_tableauObjet[i] != NULL)
            {
                p_tableauObjet[i]->modCoque(p_listeDeg[i]);

                for(int j = 0; j < 2; j++)
                {
                    p_info[i][j] = p_tableauObjet[i]->getParametre(j);
                    p_uni->modValJauge(i,j,p_info[i][j]);
                }
            }

        }
    }

    p_uni->afficher(p_ecran);

}

bool Environnement::check_collision( SDL_Rect A, SDL_Rect B )
{
//Les cotes des rectangles
int leftA, leftB;
int rightA, rightB;
int topA, topB;
int bottomA, bottomB;
//Calcul les cotes du rectangle A
leftA = A.x;
rightA = A.x + A.w;
topA = A.y;
bottomA = A.y + A.h;
//Calcul les cotes du rectangle B
leftB = B.x;
rightB = B.x + B.w;
topB = B.y;
bottomB = B.y + B.h;

//Tests de collision
if( bottomA <= topB )
{
return false;
}
if( topA >= bottomB )
{
return false;
}
if( rightA <= leftB )
{
return false;
}
if( leftA >= rightB )
{
return false;
}
//Si conditions collision detectee
return true;
}
