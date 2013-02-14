#pragma once

// wiem, że mówiłem o zasadzie "biblioteki standardowe wstawiać do precomp.hpp"
// ale ten jeden plik nagłówkowy jest wyjątkowy i nie może być w prekompilowanym nagłówku
#include <cassert>

enum DIRECTION {
	FORWARD = 4+1,
	BACKWARD = 2+1,
	LEFT = 8+1,
	RIGHT = 16+1,
	RIGHTFORWARD = 16+4+1,
	LEFTFORWARD = 8+4+1,
	RIGHTBACKWARD = 16+2+1,
	LEFTBACKWARD = 8+2+1,
	UP = 32+1,
	DOWN = 64+1
};

enum ANIMATIONS {
	STAND,
	WALK,
	RUN,
	JUMP,
	DECELERATION
};

using namespace irr;

extern scene::IAnimatedMesh* heroMesh;
extern const io::path Hero_Mesh;
extern const io::path Hero_Texture;

extern const float pozycja_gracza_x;
extern const float pozycja_gracza_y;
extern const float pozycja_gracza_z;
extern const float skala_gracza_x;
extern const float skala_gracza_y;
extern const float skala_gracza_z;

extern float ObrotGraczaY;

extern const float SzybkoscGracza;
extern const unsigned SzybkoscAnimacjiGracza;

extern scene::ISceneNodeAnimatorCollisionResponse* anim;

extern const EKEY_CODE klawiszSkoku;

extern const float SilaTarcia;
extern const float SilaSkoku;

typedef irr::core::vector3df Wektor;
typedef std::unique_ptr<irr::IrrlichtDevice> IrrlichtInternals;
typedef irr::core::stringw String;

class Level;
extern Level level;


#include "InputOutputHandler.hpp"
#include "Entity.hpp"
#include "SideCollisionDetector.hpp"
#include "Hero.hpp"
#include "ConsoleManager.hpp"
#include "Level.hpp"

extern InputOutputHandler aktywne;

extern ConsoleManager konsola;
