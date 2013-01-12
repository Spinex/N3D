#include "precomp.hpp"
#include "incl.hpp"

//eksperymentuje z gitem

IrrlichtInternals::IrrlichtInternals() :
	_device(NULL),
	_video(NULL),
	_menage(NULL),
	_kam(NULL),
	direction(0),
	zdirection(0),
	bohaterGry(NULL)
{
	_device = createDevice( video::EDT_OPENGL, core::dimension2d<u32>( 800, 600 ), 32, false, false, true, &aktywne );
	_video = device()->getVideoDriver();
	_menage = device()->getSceneManager();
<<<<<<< HEAD
	_kam = _menage->addCameraSceneNode(0, core::vector3df(0.0f,0.0f,0.0f) , core::vector3df(0.0f,0.0f,0.0f), -1);
=======
	_kam = _menage->addCameraSceneNode(0, Wektor(0.0f,0.0f,0.0f) , Wektor(0.0f,0.0f,0.0f), -1);
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d
	//FILE* file = freopen("stdout.txt", "w", stdout);
	// _kam = menage->addCameraSceneNodeFPS();

	wczytajMapeIKolizje();
	device()->getCursorControl()->setVisible(false);
	if (!bohaterGry) {
		wczytajModelITekstureBohatera();
		bohaterGry = new Hero(fSzybkoscGracza, fObrotGraczaY, Wektor(fPozycjaGraczaX, fPozycjaGraczaY, fPozycjaGraczaZ), Wektor(fSkalaGraczaX, fSkalaGraczaY, fSkalaGraczaZ), nSzybkoscAnimacjiGracza, fSzybkoscGracza);
	}
	
	konsola = new ConsoleManager(device());
	
	
	
	core::stringw str;
	
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

IrrlichtInternals::~IrrlichtInternals() {
	_device->drop();
	_metaSelector->drop();
	delete bohaterGry;
	delete konsola;
	//fclose(file);
}

void IrrlichtInternals::wczytajMapeIKolizje() {
	scena()->loadScene("mapa/map.irr");
	_metaSelector = scena()->createMetaTriangleSelector();
	recursiveFillMetaSelector( scena()->getRootSceneNode(), _metaSelector );
	//anim->drop();
}


void IrrlichtInternals::recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta ) {
	printf ("Node name is: %s \n",node->getName());
	printf ("Node id is: %d \n",node->getID());
	printf ("Node type:");
	//  printf ("Node type: %s=",smgr->getSceneNodeTypeName());
	if (node->getType() ==   scene::ESNT_UNKNOWN) printf("Unknown mesh type \n\n");
	if (node->getType() ==   scene::ESNT_MESH) {
		// Occ Trees are for land
		printf("Standard Mesh \n\n");
		io::IAttributes* attribs = device()->getFileSystem()->createEmptyAttributes();
		if (attribs) {
			// get the mesh name out
			node->serializeAttributes(attribs);
			core::stringc name = attribs->getAttributeAsString("Mesh");
			attribs->drop();
			// get the animated mesh for the object
			scene::IAnimatedMesh* mesh = scena()->getMesh(name.c_str());
			if (mesh) {
				scene::ITriangleSelector* selector = scena()->createTriangleSelector(mesh->getMesh(0), node);
				node->setTriangleSelector(selector);
				_metaSelector->addTriangleSelector(selector);
				selector->drop();
			}
		}
	}
	if (node->getType() ==   scene::ESNT_ANIMATED_MESH) printf("Animated Mesh! \n\n");
	if (node->getType() ==   scene::ESNT_SKY_BOX) printf("SkyBox! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA_FPS) printf("Fps Camera! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA_MAYA ) printf("Maya Camera! \n\n");
	if (node->getType() ==   scene::ESNT_CAMERA ) {
		printf("STD Camera! \n");
		_kam->setPosition(node->getPosition());
		printf ("The current position of this camera is: %f,%f,%f\n\n",node->getPosition().X,node->getPosition().Y,node->getPosition().Z);
	}
	if (node->getType() ==   scene::ESNT_PARTICLE_SYSTEM ) printf("Particles! \n\n");
	if (node->getType() ==   scene::ESNT_LIGHT  ) printf("Light! \n\n");
	if (node->getType() ==   scene::ESNT_OCTREE) {
		// Occ Trees are for land
		printf("Occtree! \n");
		io::IAttributes* attribs = device()->getFileSystem()->createEmptyAttributes();
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
		recursiveFillMetaSelector(*begin, meta); 
}

void IrrlichtInternals::moveCameraControl(bool bMove) {
	core::position2d<f32> cursorPos = device()->getCursorControl()->getRelativePosition();
<<<<<<< HEAD
	//core::vector3df cameraPos = _kam->getAbsolutePosition();
=======
	//Wektor cameraPos = _kam->getAbsolutePosition();
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d
	
	float change_x = ( cursorPos.X - 0.5 ) * 64.0f;
	float change_y = ( cursorPos.Y - 0.5 ) * 64.0f;
	direction += change_x;
	zdirection -= change_y;
	if( zdirection < -80 )
		zdirection = -80;
	else if( zdirection > -10 )
		zdirection = -10;
	device()->getCursorControl()->setPosition( 0.5f, 0.5f );

<<<<<<< HEAD
	core::vector3df playerPos = heroWireframe->getPosition();
=======
	Wektor playerPos = bohaterGry->getPosition();
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d

	float xf = playerPos.X - cos( direction * core::PI / 180.0f ) * 32.0f;
	float yf = playerPos.Y - sin( zdirection * core::PI / 180.0f ) * 32.0f;
	float zf = playerPos.Z + sin( direction * core::PI / 180.0f ) * 32.0f;

<<<<<<< HEAD
	_kam->setPosition( core::vector3df( xf, yf, zf ) );
	_kam->setTarget( core::vector3df( playerPos.X, playerPos.Y + 10.0f, playerPos.Z ) );
=======
	_kam->setPosition( Wektor( xf, yf, zf ) );
	_kam->setTarget( Wektor( playerPos.X, playerPos.Y + 10.0f, playerPos.Z ) );
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d

	if (bMove == false)
		bohaterGry->rotate(direction - 90);
}

void IrrlichtInternals::wczytajModelITekstureBohatera() {
<<<<<<< HEAD
	if (!heroMesh && !heroWireframe) {
		heroMesh = scena()->getMesh(Hero_Mesh);
		heroWireframe = scena()->addAnimatedMeshSceneNode(heroMesh);
=======
	if (!heroMesh) {
		heroMesh = scena()->getMesh(Hero_Mesh);
>>>>>>> 29bc7c1274edef6c285aa13df94682ddfd7b024d
	}
}