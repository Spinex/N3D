#include "precomp.hpp"
#include "incl.hpp"

IAnimatedMesh* heroMesh = NULL;
IAnimatedMeshSceneNode* heroWireframe = NULL;
video::IVideoDriver* _video = NULL;

scene::IMetaTriangleSelector* _metaSelector = NULL;
scene::ISceneNodeAnimatorCollisionResponse* _anim = NULL;
scene::ISceneManager* _menage = NULL;



const path Hero_Mesh = "postacie/bohater.b3d";
const path Hero_Texture = "postacie/bohatertekstura.png";

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
unsigned nSzybkoscAnimacjiGracza = static_cast<unsigned>(fSzybkoscGracza * 33.3);


EKEY_CODE klawiszSkoku = irr::KEY_SPACE;
