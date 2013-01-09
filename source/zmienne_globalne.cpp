#include "precomp.hpp"
#include "incl.hpp"

// od teraz definicje wszystkich zmiennych globalnych dla całego pliku
// (to znaczy razem z externem w nagłówku) umieszczamy tutaj
// gdyż łatwiej je wytępić gdy będzie trzeba
// a także nie będzie problemu z tzw. "static initialization order fiasco"
// czyli problemami z niezdefiniowaną kolejnością wywołania konstruktorów

scene::IAnimatedMesh* heroMesh = NULL;
scene::IAnimatedMeshSceneNode* heroWireframe = NULL;
scene::ISceneNodeAnimatorCollisionResponse* anim = NULL;

const io::path Hero_Mesh = "postacie/bohater.b3d";
const io::path Hero_Texture = "postacie/bohatertekstura.png";

float fPozycjaGraczaX = 7;
float fPozycjaGraczaY = 80;
float fPozycjaGraczaZ = 0;
float fSkalaGraczaX = -3;
float fSkalaGraczaY = -3;
float fSkalaGraczaZ = -3;

bool bStanSkoku = false;

float fObrotGraczaY = 180;

float fSilaSkoku = 4;
float fSilaTarcia = 0.04;

float fSzybkoscGracza = 1.4;
unsigned nSzybkoscAnimacjiGracza = fSzybkoscGracza * 33.3;


EKEY_CODE klawiszSkoku = irr::KEY_SPACE;


IrrlichtInternals internals;