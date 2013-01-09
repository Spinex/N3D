#pragma once
#include "precomp.hpp"

class IrrlichtInternals
{
private:
	IrrlichtDevice* _device;

	video::IVideoDriver* _video;

	scene::IMetaTriangleSelector* _metaSelector;
	scene::ISceneManager* _menage;
	scene::ICameraSceneNode* _kam;

	InputOutputHandler aktywne;

	float direction;
	float zdirection;

	Hero* bohaterGry;
	ConsoleManager* konsola;

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
	IrrlichtInternals();
	~IrrlichtInternals();
	void request_initialization();

public:
	IrrlichtDevice* device() { return _device; }
	video::IVideoDriver* video() { return _video; }
	scene::ISceneManager* scena() { return _menage; }
	scene::IMetaTriangleSelector* selektor_trojkatow() { return _metaSelector; }
};

extern IrrlichtInternals internals;