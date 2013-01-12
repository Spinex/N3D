#include "precomp.hpp"
#include "incl.hpp"

<<<<<<< HEAD
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
=======
// od teraz definicje wszystkich zmiennych globalnych dla całego projektu
// umieszczamy tutaj
// gdyż łatwiej je wytępić gdy będzie trzeba, a także
// nie będzie problemu z tzw. "static initialization order fiasco"
// czyli problemami z niezdefiniowaną kolejnością wywołania konstruktorów
// pomiędzy modułami kompilacji
//
// to powiedziawszy warto starać się o jak najmniej zmiennych globalnych
// (ale stałe globalne są wporzo i nawet zachęcam do ich używania - tylko
// trzeba uważać na konflikty nazw. Ale od czego są przestrzenie nazw...)

scene::IAnimatedMesh* heroMesh = NULL;
scene::ISceneNodeAnimatorCollisionResponse* anim = NULL;

const io::path Hero_Mesh = "postacie/bohater.b3d";
const io::path Hero_Texture = "postacie/bohatertekstura.png";

const float fPozycjaGraczaX = 7;
const float fPozycjaGraczaY = 80;
const float fPozycjaGraczaZ = 0;
const float fSkalaGraczaX = -3;
const float fSkalaGraczaY = -3;
const float fSkalaGraczaZ = -3;

float fObrotGraczaY = 180;
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d

const float fSilaSkoku = 4;
const float fSilaTarcia = 0.04;

const float fSzybkoscGracza = 1.4;
const unsigned nSzybkoscAnimacjiGracza = fSzybkoscGracza * 33.3;


<<<<<<< HEAD
float fSzybkoscGracza = 1.4;
unsigned nSzybkoscAnimacjiGracza = fSzybkoscGracza * 33.3;


EKEY_CODE klawiszSkoku = irr::KEY_SPACE;


=======
const EKEY_CODE klawiszSkoku = irr::KEY_SPACE;


>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d
IrrlichtInternals internals;