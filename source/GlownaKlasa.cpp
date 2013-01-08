#include "naglowek.hpp"

//eksperymentuje z gitem

GlownaKlasa::GlownaKlasa() : direction(0), zdirection(0), bohaterGry(NULL) {
	device = createDevice( EDT_OPENGL, core::dimension2d<u32>( 800, 600 ), 32, false, false, true, &aktywne );
	video = device->getVideoDriver();
	menage = device->getSceneManager();
	// kam = menage->addCameraSceneNodeFPS();
	kam = menage->addCameraSceneNode(0, core::vector3df(0.0f,0.0f,0.0f) , core::vector3df(0.0f,0.0f,0.0f), -1);

	_video = video;
	_menage = menage;

	wczytajMapeIKolizje();
	device->getCursorControl()->setVisible(false);
	if (!bohaterGry) {
		wczytajModelITekstureBohatera();
		bohaterGry = new Hero(fSzybkoscGracza, fObrotGraczaY, 
		                      Wektor(fPozycjaGraczaX, fPozycjaGraczaY, fPozycjaGraczaZ),
		                      Wektor(fSkalaGraczaX, fSkalaGraczaY, fSkalaGraczaZ),
		                      nSzybkoscAnimacjiGracza, fSzybkoscGracza);
	}
	
	konsola = new ConsoleManager(device);
	
	
	
	stringw str;
	
	//instrukcje potrzebne w tym miejscu do sprawdzania funkcjonalnosci mojego detektora kolizji
	
	str = "left: false";	
	konsola->addMessage(str);
	str = "right: false";
	konsola->addMessage(str);
	str = "forward: false";
	konsola->addMessage(str);
	str = "back: false";
	konsola->addMessage(str);
	str = "up: false";
	konsola->addMessage(str);
	str = "down: false";
	konsola->addMessage(str);
	
	str = "SideCollisionDetector is visible: true";
	konsola->addMessage(str);
	
	
	petlaGry();
}

GlownaKlasa::~GlownaKlasa() {
	device->drop();
	metaSelector->drop();
	delete bohaterGry;
	delete konsola;
}

void GlownaKlasa::wczytajMapeIKolizje() {
	menage->loadScene("mapa/map.irr");
	metaSelector = menage->createMetaTriangleSelector();
	recursiveFillMetaSelector( menage->getRootSceneNode(), metaSelector );
	_metaSelector = metaSelector;
	//anim->drop();
}


void GlownaKlasa::recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta ) {
	printf ("Node name is: %s \n",node->getName());
	printf ("Node id is: %d \n",node->getID());
	printf ("Node type:");
	//  printf ("Node type: %s=",smgr->getSceneNodeTypeName());
	if (node->getType() ==   ESNT_UNKNOWN) printf("Unknown mesh type \n\n");
	if (node->getType() ==   ESNT_MESH) {
		// Occ Trees are for land
		printf("Standard Mesh \n\n");
		io::IAttributes* attribs = device->getFileSystem()->createEmptyAttributes();
		if (attribs) {
			// get the mesh name out
			node->serializeAttributes(attribs);
			core::stringc name = attribs->getAttributeAsString("Mesh");
			attribs->drop();
			// get the animated mesh for the object
			scene::IAnimatedMesh* mesh = menage->getMesh(name.c_str());
			if (mesh) {
				scene::ITriangleSelector* selector = menage->createTriangleSelector(mesh->getMesh(0), node);
				node->setTriangleSelector(selector);
				metaSelector->addTriangleSelector(selector);
				selector->drop();
			}
		}
	}
	if (node->getType() ==   ESNT_ANIMATED_MESH) printf("Animated Mesh! \n\n");
	if (node->getType() ==   ESNT_SKY_BOX) printf("SkyBox! \n\n");
	if (node->getType() ==   ESNT_CAMERA_FPS) printf("Fps Camera! \n\n");
	if (node->getType() ==   ESNT_CAMERA_MAYA ) printf("Maya Camera! \n\n");
	if (node->getType() ==   ESNT_CAMERA ) {
		printf("STD Camera! \n");
		kam->setPosition(node->getPosition());
		printf ("The current position of this camera is: %f,%f,%f\n\n",node->getPosition().X,node->getPosition().Y,node->getPosition().Z);
	}
	if (node->getType() ==   ESNT_PARTICLE_SYSTEM ) printf("Particles! \n\n");
	if (node->getType() ==   ESNT_LIGHT  ) printf("Light! \n\n");
	if (node->getType() ==   ESNT_OCTREE) {
		// Occ Trees are for land
		printf("Occtree! \n");
		io::IAttributes* attribs = device->getFileSystem()->createEmptyAttributes();
		if (attribs) {
			// get the mesh name out
			node->serializeAttributes(attribs);
			core::stringc name = attribs->getAttributeAsString("Mesh");
			attribs->drop();
			// get the animated mesh for the object
			scene::IAnimatedMesh* mesh = menage->getMesh(name.c_str());
			if (mesh) {
				scene::ITriangleSelector* selector = menage->createOctreeTriangleSelector(mesh->getMesh(0), node, 128);
				node->setTriangleSelector(selector);
				metaSelector->addTriangleSelector(selector);
				selector->drop();
			}
		}
	}
	// now recurse on children...
	core::list<scene::ISceneNode*>::ConstIterator begin = node->getChildren().begin();
	core::list<scene::ISceneNode*>::ConstIterator end   = node->getChildren().end();

	for (; begin != end; ++begin)
		recursiveFillMetaSelector(*begin, meta); 
}

void GlownaKlasa::moveCameraControl(bool bMove) {
	core::position2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
	//core::vector3df cameraPos = kam->getAbsolutePosition();
	
	float change_x = ( cursorPos.X - 0.5 ) * 64.0f;
	float change_y = ( cursorPos.Y - 0.5 ) * 64.0f;
	direction += change_x;
	zdirection -= change_y;
	if( zdirection < -80 )
		zdirection = -80;
	else if( zdirection > -10 )
		zdirection = -10;
	device->getCursorControl()->setPosition( 0.5f, 0.5f );

	core::vector3df playerPos = heroWireframe->getPosition();

	float xf = playerPos.X - cos( direction * PI / 180.0f ) * 32.0f;
	float yf = playerPos.Y - sin( zdirection * PI / 180.0f ) * 32.0f;
	float zf = playerPos.Z + sin( direction * PI / 180.0f ) * 32.0f;

	kam->setPosition( core::vector3df( xf, yf, zf ) );
	kam->setTarget( core::vector3df( playerPos.X, playerPos.Y + 10.0f, playerPos.Z ) );

	if (bMove == false)
		bohaterGry->rotate(direction - 90);
}

void GlownaKlasa::wczytajModelITekstureBohatera() {
	if (!heroMesh && !heroWireframe) {
		heroMesh = menage->getMesh(Hero_Mesh);
		heroWireframe = menage->addAnimatedMeshSceneNode(heroMesh);
	}
}
