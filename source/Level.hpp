#pragma once
#include "precomp.hpp"

class Level
{
private:
	scene::IMetaTriangleSelector* _metaSelector;
	scene::ISceneManager* _menage;

public: //for now
	std::unique_ptr<Hero> bohaterGry;
private:
	std::unique_ptr<Entity> drone;
	std::vector<Gold> golds;

	std::unordered_map<int, scene::ITriangleSelector*> importantSelectors;
public:
	Level(const IrrlichtInternals& internals, io::path sciezka);
	~Level();

	scene::ISceneManager* scena() { return _menage; }
	scene::IMetaTriangleSelector* selektor_trojkatow() { return _metaSelector; }

	void recursiveFillMetaSelector(const IrrlichtInternals& internals, scene::ISceneNode* node, scene::IMetaTriangleSelector* meta);
	void refresh();

	std::unordered_map<int, scene::ITriangleSelector*>& getSelectors() {return importantSelectors;}
};