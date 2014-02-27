#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


#include <string>


#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define LARGEUR_ECRAN       CX_SCREEN   ///  1366       1280       1920
#define HAUTEUR_ECRAN       CY_SCREEN   ///  768        1024       1080
#define LARGEUR_MAP         3840
#define HAUTEUR_MAP         3072
#define VITESSE             5
#define VITESSER            10
#define VITESSEL            3

#define SCREEN_REFRESH      40
#define DEBUG               std::cerr << std::endl <<
#define NOMBRE_IMAGE        31
#define NOMBRE_MUSIQUE      1
#define NOMBRE_POLICE       1
#define NOMBRE_MAP          5

const std::string cheminRessources = "ressources/";
const std::string cheminCarte = cheminRessources + "map/";
const std::string cheminSon = cheminRessources + "sons/";
const std::string cheminImage = cheminRessources + "images/";
const std::string cheminPolice = cheminRessources + "polices/";
const std::string cheminFile = cheminRessources + "fichiers/";


enum objet{VAISSEAU, ETRE, PROJECTILE, ASTRE};
enum arme{CANON, BATTERIE, LASER, PHASEUR};
enum etat{HAUT, BAS, GAUCHE, DROITE, HD, BD, BG, HG, DETRUIT, ACTUELLE};
enum bouclier{BOUCLIER, BOUCLIER_W, BOUCLIER_H, BOUCLIER_DD, BOUCLIER_DG};



#endif // CONSTANTES_H_INCLUDED
