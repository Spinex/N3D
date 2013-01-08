#pragma once
#include "precomp.hpp"

class GlownaKlasa
{
private:
	scene::ICameraSceneNode* kam;
	IrrlichtDevice* device;

	video::IVideoDriver* video;

	scene::IMetaTriangleSelector* metaSelector;
	scene::ISceneNodeAnimatorCollisionResponse* anim;
	scene::ISceneManager* menage;

	InputOutputHandler aktywne;

	int incremental_counter_of_entities;
	irr::core::map<int, Entity*> entity_container;
	

	float direction;
	float zdirection;

	Hero* bohaterGry;

private:
	void recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta);   
	void petlaGry();     
	void wczytajMapeIKolizje();
	void moveCameraControl(bool bMove);

private:
	void wczytajModelITekstureBohatera();

private:
	void sterowaniePostacia();    

public:
	GlownaKlasa();  
	~GlownaKlasa();
	
};      
