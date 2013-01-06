#pragma once

#include <irrlicht.h>
#pragma comment(lib, "Irrlicht.lib")

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
using namespace irr::core; 
using namespace irr::scene;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

extern IAnimatedMesh* heroMesh;
extern IAnimatedMeshSceneNode* heroWireframe;
extern const path Hero_Mesh;
extern const path Hero_Texture;

extern float fPozycjaGraczaX;
extern float fPozycjaGraczaY;
extern float fPozycjaGraczaZ;
extern float fSkalaGraczaX;
extern float fSkalaGraczaY;
extern float fSkalaGraczaZ;

extern float fObrotGraczaY;

extern float fSzybkoscGracza;
extern unsigned nSzybkoscAnimacjiGracza;

extern video::IVideoDriver* _video;

extern scene::IMetaTriangleSelector* _metaSelector;
extern scene::ISceneNodeAnimatorCollisionResponse* _anim;
extern scene::ISceneManager * _menage;
extern EKEY_CODE klawiszSkoku;


extern float fSilaTarcia;
extern float fSilaSkoku;
extern bool bStanSkoku;

typedef irr::core::vector3df Wektor;

#include "InputOutputHandler.hpp"
#include "Hero.hpp"
#include "GlownaKlasa.hpp"
