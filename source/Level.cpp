#include "precomp.hpp"
#include "incl.hpp"

Level::Level(const IrrlichtInternals& spDevice, io::path sciezka) :
	_menage( spDevice->getSceneManager() )
{
	scena()->loadScene(sciezka);
	_metaSelector = scena()->createMetaTriangleSelector();
	recursiveFillMetaSelector( spDevice, scena()->getRootSceneNode(), _metaSelector );

	// lambda użyta tutaj jako alias
	auto getTexture = [&spDevice](const String& s){ return spDevice->getVideoDriver()->getTexture(s); };

	if (!bohaterGry) {
		bohaterGry.reset(new Hero(*this, getTexture( "postacie/bohatertekstura.png" ), SzybkoscGracza, ObrotGraczaY, Wektor(pozycja_gracza_x, pozycja_gracza_y, pozycja_gracza_z), Wektor(skala_gracza_x, skala_gracza_y, skala_gracza_z), SzybkoscAnimacjiGracza, SzybkoscGracza));
		drone.reset(new DumbDrone(*this, getTexture( "postacie/dronetekstura.png" ), Wektor(186.739929, 39.554573, 126.878952)));
	}
	for (int i = 0; i < 15; i++) golds.push_back(Gold(*this, getTexture( "postacie/goldtekstura.png" ), Wektor(0, 10, 10*i)));
}

Level::~Level()
{
	_metaSelector->drop();
	for (auto &x : importantSelectors) x.second->drop();
}

void Level::recursiveFillMetaSelector(const IrrlichtInternals& internals, scene::ISceneNode* node, scene::IMetaTriangleSelector* meta )
{
	printf ("Node name is: %s \n",node->getName());
	printf ("Node id is: %d \n",node->getID());
	printf ("Node type:");
	//  printf ("Node type: %s=",smgr->getSceneNodeTypeName());
	if (node->getType() ==   scene::ESNT_UNKNOWN) printf("Unknown mesh type \n\n");
	if (node->getType() ==   scene::ESNT_MESH) {
		// Occ Trees are for land
		printf("Standard Mesh \n\n");
		io::IAttributes* attribs = internals->getFileSystem()->createEmptyAttributes();
		if (attribs) {
			// get the mesh name out
			node->serializeAttributes(attribs);
			core::stringc name = attribs->getAttributeAsString("Mesh");
			attribs->drop();
			// get the animated mesh for the object
			scene::IAnimatedMesh* mesh = scena()->getMesh(name.c_str());
			if (mesh) {
			// EKSPERYMENTY POCZATEK ******************
			    if (node->getID() != 1337)
				{
				   scene::ITriangleSelector* selector = scena()->createTriangleSelector(mesh->getMesh(0), node);
				   node->setTriangleSelector(selector);
				   _metaSelector->addTriangleSelector(selector);
				   
				   importantSelectors.insert({node->getID(), selector});
				   				   
				//   selector->drop();
				}
                else
                {
				   scene::ITriangleSelector* selector = scena()->createTriangleSelector(mesh->getMesh(0), node);
				   node->setTriangleSelector(selector);
				   				   
				   importantSelectors.insert({node->getID(), selector});
                }  				
			// EKSPERYMENTY KONIEC ********************	
			}
		}
	}
	if (node->getType() ==   scene::ESNT_ANIMATED_MESH) printf("Animated Mesh! \n\n");
	if (node->getType() ==   scene::ESNT_SKY_BOX) printf("SkyBox! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA_FPS) printf("Fps Camera! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA_MAYA ) printf("Maya Camera! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA ) {
		printf("STD Camera! \n");
		printf ("The current position of this camera is: %f,%f,%f\n\n",node->getPosition().X,node->getPosition().Y,node->getPosition().Z);
	}
	if (node->getType() ==   scene::ESNT_PARTICLE_SYSTEM ) printf("Particles! \n\n");
	if (node->getType() ==   scene::ESNT_LIGHT  ) printf("Light! \n\n");
	if (node->getType() ==   scene::ESNT_OCTREE) {
		// Occ Trees are for land
		printf("Occtree! \n");
		io::IAttributes* attribs = internals->getFileSystem()->createEmptyAttributes();
		if (attribs) {
			// get the mesh name out
			node->serializeAttributes(attribs);
			core::stringc name = attribs->getAttributeAsString("Mesh");
			attribs->drop();
			// get the animated mesh for the object
			scene::IAnimatedMesh* mesh = scena()->getMesh(name.c_str());
			if (mesh) {
				scene::ITriangleSelector* selector = scena()->createOctreeTriangleSelector(mesh->getMesh(0), node, 128);
				node->setTriangleSelector(selector);
				_metaSelector->addTriangleSelector(selector);
				selector->drop();
			}
		}
	}
	// now recurse on children...
	core::list<scene::ISceneNode*>::ConstIterator begin = node->getChildren().begin();
	core::list<scene::ISceneNode*>::ConstIterator end   = node->getChildren().end();

	for (; begin != end; ++begin)
		recursiveFillMetaSelector(internals, *begin, meta); 
}

void Level::refresh()
{
	drone->refreshState();
	for(Gold& g : golds)
		g.refreshState();
}