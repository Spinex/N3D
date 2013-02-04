#include "precomp.hpp"
#include "incl.hpp"

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

const float pozycja_gracza_x = 7;
const float pozycja_gracza_y = 80;
const float pozycja_gracza_z = 0;
const float skala_gracza_x = -3;
const float skala_gracza_y = -3;
const float skala_gracza_z = -3;

float ObrotGraczaY = 180;

const float SilaSkoku = 4;
const float SilaTarcia = 0.04;

const float SzybkoscGracza = 1.4;
const unsigned SzybkoscAnimacjiGracza = SzybkoscGracza * 33.3;


const EKEY_CODE klawiszSkoku = irr::KEY_SPACE;


IrrlichtInternals internals(createDevice( video::EDT_OPENGL, core::dimension2d<u32>( 800, 600 ), 32, false, false, true ));
ConsoleManager konsola(internals);
InputOutputHandler aktywne(internals);
Level level(internals, "mapa/map.irr");