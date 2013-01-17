#include "precomp.hpp"
#include "incl.hpp"

//eksperymentuje z gitem

IrrlichtInternals::IrrlichtInternals() :
	_device(NULL),
	_video(NULL),
	_menage(NULL),
	_kam(NULL),
	direction(0),
	zdirection(0)
{
	_device = createDevice( video::EDT_OPENGL, core::dimension2d<u32>( 800, 600 ), 32, false, false, true, &aktywne );
	_video = device()->getVideoDriver();
	_menage = device()->getSceneManager();
	_kam = _menage->addCameraSceneNode(0, Wektor(0.0f,0.0f,0.0f) , Wektor(0.0f,0.0f,0.0f), -1);
	//FILE* file = freopen("stdout.txt", "w", stdout);
	// _kam = menage->addCameraSceneNodeFPS();

	wczytajMapeIKolizje();
	device()->getCursorControl()->setVisible(false);
	if (!bohaterGry) {
		wczytajModelITekstureBohatera();
		bohaterGry.reset(new Hero(fSzybkoscGracza, fObrotGraczaY, Wektor(fPozycjaGraczaX, fPozycjaGraczaY, fPozycjaGraczaZ), Wektor(fSkalaGraczaX, fSkalaGraczaY, fSkalaGraczaZ), nSzybkoscAnimacjiGracza, fSzybkoscGracza));
		drone.reset(new DumbDrone(Wektor(186.739929, 39.554573, 126.878952)));
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
	
    for (int i = 0; i < 10; i++) golds.push_back(Gold(Wektor(0, 10, 10*i)));
	
	petlaGry();
}

IrrlichtInternals::~IrrlichtInternals() {
	_device->drop();
	_metaSelector->drop();
	delete konsola;
	golds.clear();
	selectorKladki->drop();
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
			// EKSPERYMENTY POCZATEK ******************
			    if (node->getID() != 1337)
				{
				   scene::ITriangleSelector* selector = scena()->createTriangleSelector(mesh->getMesh(0), node);
				   node->setTriangleSelector(selector);
				   _metaSelector->addTriangleSelector(selector);
				   selector->drop();
				}
                else
                {
				   selectorKladki = scena()->createTriangleSelector(mesh->getMesh(0), node);
				   node->setTriangleSelector(selectorKladki);
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
	//Wektor cameraPos = _kam->getAbsolutePosition();
	
	float change_x = ( cursorPos.X - 0.5 ) * 64.0f;
	float change_y = ( cursorPos.Y - 0.5 ) * 64.0f;
	direction += change_x;
	zdirection -= change_y;
	if( zdirection < -80 )
		zdirection = -80;
	else if( zdirection > -10 )
		zdirection = -10;
	device()->getCursorControl()->setPosition( 0.5f, 0.5f );

	Wektor playerPos = bohaterGry->getPosition();

	float xf = playerPos.X - cos( direction * core::PI / 180.0f ) * 32.0f;
	float yf = playerPos.Y - sin( zdirection * core::PI / 180.0f ) * 32.0f;
	float zf = playerPos.Z + sin( direction * core::PI / 180.0f ) * 32.0f;

	_kam->setPosition( Wektor( xf, yf, zf ) );
	_kam->setTarget( Wektor( playerPos.X, playerPos.Y + 10.0f, playerPos.Z ) );

	if (bMove == false)
		bohaterGry->rotate(direction - 90);
}

void IrrlichtInternals::wczytajModelITekstureBohatera() {
	if (!heroMesh) {
		heroMesh = scena()->getMesh(Hero_Mesh);
	}
}
