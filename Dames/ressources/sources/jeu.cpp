#include "jeu.h"

using namespace std;


void game(Input * p_in, SDL_Surface ** p_images)
{
/// initialisation données du jeu
    int ** tableauCases = NULL;         /// correspond aux cases du plateau
    tableauCases = (int **) malloc(sizeof(int*)*NB_CARRE_X);
    for(int i=0; i< NB_CARRE_X ; i++)
    {
        tableauCases[i] = (int*) malloc(sizeof(int)*NB_CARRE_Y);

        for(int j = 0 ; j < NB_CARRE_Y ; j++)
        {
            tableauCases[i][j] = (i+j)%2;
        }
    }

    int ** tableauPions = NULL;         /// correspond à l'emplacement des pions
    tableauPions = (int **) malloc(sizeof(int*)*NB_CARRE_X);
    for(int i=0; i< NB_CARRE_X ; i++)
    {
        tableauPions[i] = (int*) malloc(sizeof(int)*NB_CARRE_Y);
        for(int j = 0 ; j < NB_CARRE_Y ; j++)
        {
            if(tableauCases[i][j] == 1)
            {
                if(i < 4)
                {
                    tableauPions[i][j] = 2;
                }
                else if(i > 5)
                {
                    tableauPions[i][j] = 1;
                }
                else
                {
                    tableauPions[i][j] = 0;
                }
            }
            else
            {
                tableauPions[i][j] = 0;
            }
        }
    }

    bool playa_turn = true;     /// true : tour du joueur    false : tour de l'IA
    int pion_en_main = 0,       /// représente le pion que l'on veut bouger
        temp_origine_X = 0,     /// coordonnées d'origine du pion en mouvement
        temp_origine_Y = 0,     ///
        temp_destination_X = 0, /// coordonnées d'arrivée du pion en mouvement
        temp_destination_Y = 0; ///

/// loop of the game
    int tempsPrecedent = 0, tempsActuel = 0;
    while(!p_in->key[SDLK_ESCAPE] && !p_in->quit && !tester_fin(tableauPions,pion_en_main))
    {
    /// events
        updateEvents(p_in);

    /// FPS
        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent >= SCREEN_REFRESH)
        {
            tempsPrecedent = tempsActuel;
        }
        else if (tempsActuel - tempsPrecedent < SCREEN_REFRESH)
        {
            SDL_Delay(tempsActuel - tempsPrecedent);
            tempsPrecedent = tempsActuel;
        }


    /// mécanique du jeu
        jouer_jeu(p_in, &playa_turn, tableauPions, &pion_en_main,
                  &temp_origine_X,
                  &temp_origine_Y,
                  &temp_destination_X,
                  &temp_destination_Y);
    /// affichage du jeu
        afficher_jeu(p_images,tableauCases,tableauPions);
    }

/// fermeture du jeu
    for(int i=0; i<NB_CARRE_X ; ++i)
    {free(tableauCases[i]);}
    free(tableauCases);
    for(int i=0; i<NB_CARRE_X ; ++i)
    {free(tableauPions[i]);}
    free(tableauPions);
}

void jouer_jeu(Input * p_in, bool * p_playa_turn, int ** p_tableau, int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y)
{
    if(!(*p_playa_turn))        /// si c'est le tour de l'IA
    {
        time_to_IA();
        *p_playa_turn = true;
    }
    else        /// si c'est le tour du joueur
    {
        cliquer_prendre_poser(p_in, p_tableau, p_pion, p_origine_X, p_origine_Y, p_destination_X, p_destination_Y);
    }

    pion_to_dame(p_tableau);
}


void time_to_IA()
{

}


void tester_action()
{

}


bool tester_fin(int ** p_tableau, int p_pion)       /// détermine si la partie est finie
{
    int blancs = 0, noirs = 0;

    for(int i = 0 ; i < NB_CARRE_Y; i++)
    {
        for(int j = 0 ; j < NB_CARRE_X; j++)
        {
            if(1 == p_tableau[i][j] || 3 == p_tableau[i][j]){blancs++;}
            if(2 == p_tableau[i][j] || 4 == p_tableau[i][j]){noirs++;}
        }
    }

    if(1 == p_pion || 3 == p_pion){blancs++;}
    if(2 == p_pion || 4 == p_pion){noirs++;}

    if(0 == blancs || 0 == noirs)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool tester_mouvement(int ** p_tableau, int p_piece, int p_origin_X, int p_origin_Y, int p_dest_X, int p_dest_Y)
{
    return test_mouvement(p_tableau, p_piece, p_origin_X, p_origin_Y, p_dest_X, p_dest_Y);        /// la fonction de Benji
}


void prendre_piece(int ** p_tableau, int p_depart_X, int p_depart_Y,
                   int * p_pion, int * p_temp_X, int * p_temp_Y)        /// permet de prendre une pièce
{
    *p_pion = p_tableau[p_depart_Y][p_depart_X];
    *p_temp_X = p_depart_X;
    *p_temp_Y = p_depart_Y;
    p_tableau[p_depart_Y][p_depart_X] = 0;
}


void poser_piece(int ** p_tableau, int p_arrivee_X, int p_arrivee_Y,
                 int * p_pion, int * p_temp_X, int * p_temp_Y)          /// permet de poser une pièce
{
    *p_temp_X = p_arrivee_X;
    *p_temp_Y = p_arrivee_Y;
    p_tableau[*p_temp_Y][*p_temp_X] = *p_pion;
    *p_pion = 0;
}


void pion_to_dame(int ** p_tableau)         /// change un pion en dame si il est sur la dernière ligne
{
    for(int i = 0 ; i < NB_CARRE_X ; i++)
    {
        if(p_tableau[0][i] == 1)
        {
            p_tableau[0][i] = 3;
        }
        if(p_tableau[9][i] == 2)
        {
            p_tableau[9][i] = 4;
        }
    }
}


void cliquer_prendre_poser(Input * p_in, int ** p_tableau, int * p_pion,
                           int * p_origine_X, int * p_origine_Y,
                           int * p_destination_X, int * p_destination_Y)
{
    if(*p_pion != 0 && (p_in->mousex) < (TAILLE_CARRE * NB_CARRE_X))    /// poser une pièce
    {
        if(p_in->mousebuttons[SDL_BUTTON_LEFT])
        {
            *p_destination_X = ((p_in->mousex)/(TAILLE_CARRE));
            *p_destination_Y = ((p_in->mousey)/(TAILLE_CARRE));

            if(tester_mouvement(p_tableau, *p_pion, *p_origine_X, *p_origine_Y, *p_destination_X, *p_destination_Y))        /// si le mouvement est possible on la pose
            {
                poser_piece(p_tableau, *p_destination_X, *p_destination_Y,
                            p_pion, p_destination_X, p_destination_Y);
            }
            else                            /// sinon on la remet à sa place
            {
                poser_piece(p_tableau, *p_origine_X, *p_origine_Y,
                            p_pion, p_destination_X, p_destination_Y);
            }

            nettoyer_deplacement(p_pion, p_origine_X, p_origine_Y, p_destination_X, p_destination_Y);
            p_in->mousebuttons[SDL_BUTTON_LEFT] = 0;
        }
        if(p_in->mousebuttons[SDL_BUTTON_RIGHT])        /// relacher une pièce
        {
            poser_piece(p_tableau, *p_origine_X, *p_origine_Y,
                        p_pion, p_destination_X, p_destination_Y);
            nettoyer_deplacement(p_pion, p_origine_X, p_origine_Y, p_destination_X, p_destination_Y);
            p_in->mousebuttons[SDL_BUTTON_RIGHT] = 0;
        }
    }
    if((*p_pion) == 0 && p_in->mousex < TAILLE_CARRE * NB_CARRE_X)          /// prendre une pièce
    {
        if(p_in->mousebuttons[SDL_BUTTON_LEFT])
        {
            prendre_piece(p_tableau, ((p_in->mousex)/(TAILLE_CARRE)), ((p_in->mousey)/(TAILLE_CARRE)), p_pion, p_origine_X, p_origine_Y);
            p_in->mousebuttons[SDL_BUTTON_LEFT] = 0;
        }
    }
}


void nettoyer_deplacement(int * p_pion, int * p_origine_X, int * p_origine_Y, int * p_destination_X, int * p_destination_Y)
{
    * p_pion = 0;
    * p_origine_X = 0;
    * p_origine_Y = 0;
    * p_destination_X = 0;
    * p_destination_Y = 0;
}

