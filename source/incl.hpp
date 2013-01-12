#pragma once

#pragma comment(lib, "Irrlicht.lib")

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
<<<<<<< HEAD
extern scene::IAnimatedMeshSceneNode* heroWireframe;
=======
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d
extern const io::path Hero_Mesh;
extern const io::path Hero_Texture;

extern const float fPozycjaGraczaX;
extern const float fPozycjaGraczaY;
extern const float fPozycjaGraczaZ;
extern const float fSkalaGraczaX;
extern const float fSkalaGraczaY;
extern const float fSkalaGraczaZ;

extern float fObrotGraczaY;

<<<<<<< HEAD
extern float fSzybkoscGracza;
extern unsigned nSzybkoscAnimacjiGracza;

extern scene::ISceneNodeAnimatorCollisionResponse* anim;
extern EKEY_CODE klawiszSkoku;
=======
extern const float fSzybkoscGracza;
extern const unsigned nSzybkoscAnimacjiGracza;
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d

extern scene::ISceneNodeAnimatorCollisionResponse* anim;
extern const EKEY_CODE klawiszSkoku;

extern const float fSilaTarcia;
extern const float fSilaSkoku;

typedef irr::core::vector3df Wektor;

#include "InputOutputHandler.hpp"
#include "SideCollisionDetector.hpp"
#include "Hero.hpp"
#include "ConsoleManager.hpp"
#include "IrrlichtInternals.hpp"


