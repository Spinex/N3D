#include "precomp.hpp"
#include "incl.hpp"

bool HeroCollisionCallback::onCollision(const scene::ISceneNodeAnimatorCollisionResponse & animator)
{
	const scene::ISceneNode* collided_node = animator.getCollisionNode();
	printf("CLD %d ", collided_node->getID());
	if (collided_node->getID() == 1337) exit(0);
	
	SideCollisionDetector& znaczniki = level.bohaterGry->getZnacznikiKolizji();
	
	std::vector<bool> bStanKolizji = znaczniki.getCollisionState();

	if (bStanKolizji[SideCollisionDetector::down])
		level.bohaterGry->stopFallingDown();
	
	if (!bStanKolizji[SideCollisionDetector::down] &&
	    !bStanKolizji[SideCollisionDetector::up] &&
       ( bStanKolizji[SideCollisionDetector::left] ||
		 bStanKolizji[SideCollisionDetector::right]||
		 bStanKolizji[SideCollisionDetector::forward]||
		 bStanKolizji[SideCollisionDetector::backward]) &&
         aktywne.IsKeyDown( klawiszSkoku ) )
	{	 
        level.bohaterGry->stopFallingDown();
		if (bStanKolizji[SideCollisionDetector::right]&&
			bStanKolizji[SideCollisionDetector::forward])
		aktywne.setCameraDirection(aktywne.getCameraDirection() - 30);
		else
		if (bStanKolizji[SideCollisionDetector::left]&&
			bStanKolizji[SideCollisionDetector::forward])
		aktywne.setCameraDirection(aktywne.getCameraDirection() + 30);
        }		
    	
	
	return false;
}

Hero::Hero(Level& level, video::ITexture* texture, float fSpeed, float _rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed) :
	animation_speed(nAnimSpeed),
	bezwladnosc(0),
	opoznienie(SilaTarcia),
	stan_skoku(false),
	falling_speed(0),
	rotation(_rotate),
	kierunek_ruchu(FORWARD),
	animation_type(STAND),
	movement_speed(fMovementSpeed),
	time_to_live(90.0),
	znacznikiKolizji(level, *this),
	wireframe(NULL)
{
	auto* mesh = level.scena()->getMesh("postacie/bohater.b3d");
	wireframe = level.scena()->addAnimatedMeshSceneNode(mesh);
	if(!wireframe)
		{} //wywal program na zbity pysk (ewentualnie grzecznie zgłoś błąd)
	wireframe->setScale( skala );
	wireframe->setPosition( pozycja );
	wireframe->setRotation( Wektor( 180, rotation, 0 ) ); 
	
	wireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	wireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	wireframe->setMaterialTexture( 0, texture ); 
	
	wireframe->setAnimationSpeed(nAnimSpeed);  
	
	wireframe->setFrameLoop(1,1);

	auto& selectors = level.getSelectors(); 

	for (auto &x : selectors)
	{
		auto* animator = level.scena()->createCollisionResponseAnimator(x.second, wireframe, Wektor(5,11,5), Wektor(0,0,0), Wektor(0,-13,0)); 
		animator->setCollisionCallback(new HeroCollisionCallback());
		wireframe->addAnimator(animator);

		animators.push_back(animator);
	}
}

void Hero::move(ANIMATIONS anim, DIRECTION direct) {
	Wektor v = wireframe->getPosition();

	if (anim != STAND)
	{
		int angle = sprawdzKat(direct);
		v.Z += movement_speed * cos(( core::PI * (rotation - 90 + angle)) / 180);
		v.X += movement_speed * sin(( core::PI * (rotation - 90 + angle)) / 180);
		wireframe->setPosition( v );
		wireframe->setRotation( Wektor( 180, rotation + angle, 0 ) );
	}

	if ((animation_type == STAND || animation_type == DECELERATION) && anim == WALK) {
		wireframe->setFrameLoop(15, 34);
		wireframe->setAnimationSpeed( animation_speed );
		animation_type = WALK;
		wireframe->setAnimationSpeed( animation_speed );
	}
	else if ((animation_type == STAND || animation_type == WALK) && anim == DECELERATION) {
		wireframe->setFrameLoop(5, 5);
		wireframe->setAnimationSpeed( animation_speed ); 
		animation_type = DECELERATION;
	}
	else if (anim == STAND) {
		wireframe->setFrameLoop(1, 1);
		wireframe->setAnimationSpeed( animation_speed );
		animation_type = STAND;
	}
}

void Hero::refreshState()
{
	znacznikiKolizji.refreshState();
}

void Hero::decelerate() 
{
	bezwladnosc -= opoznienie;
	movement_speed = bezwladnosc * SzybkoscGracza;

	move(DECELERATION, kierunek_ruchu);
}

Wektor Hero::getPosition() const
{
	return wireframe->getPosition();
}

Hero::~Hero()
{
	for (unsigned i = 0; i < animators.size(); i++)
	{
	    animators[i]->drop();
	}
}

void Hero::fallDown()
{
    gravity_acceleration = 0.2;     
    Wektor v = wireframe->getPosition();
    v.Y -= falling_speed;
    wireframe->setPosition( v );
    falling_speed += gravity_acceleration;
} 

void Hero::jump()
{
   core::vector3df v = wireframe->getPosition();
   v.Y += SilaSkoku;
   wireframe->setPosition(v);
}

DumbDrone::DumbDrone(Level& level, video::ITexture* texture, Wektor starting_location) :
	current(0)
{
	auto* mesh = level.scena()->getMesh("postacie/drone.obj"); //auto - nowa funkcjonalność C++11
	wireframe = level.scena()->addAnimatedMeshSceneNode(mesh);
	if(!wireframe)
		{} //wywal program na zbity pysk (ewentualnie grzecznie zgłoś błąd)
	wireframe->setScale( Wektor(-5, -5, -5) );
	wireframe->setPosition( starting_location );
	wireframe->setRotation( Wektor( 180, 42, 0 ) ); 

	wireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	wireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	wireframe->setMaterialTexture( 0, texture ); 

	//sample locations to move
	waypoints.push_back(Wektor(199.250015, 38.954994, -169.493530));
	waypoints.push_back(Wektor(-155.748276, 39.555645, -140.499557));
	waypoints.push_back(Wektor(-183.163818, 40.155643, 111.872986));
	waypoints.push_back(starting_location);
}

void DumbDrone::refreshState()
{
	Wektor kierunek = (currentTarget() - getPosition()).normalize();
	wireframe->setPosition(getPosition() + kierunek * 0.4);
	if(getPosition().equals(currentTarget(), 1.2)) followNextTarget();
}

/// Przelicza ponownie trasę przemierzaną przez drona.
/// Wykonywana pod koniec zmiany trasy inteligentnego drona.
/// 
void IntelligentDrone::recalculateWaypoints()
{
	// to tylko zalążek
}

/// Konstruktor klasy Gold.
/// Umieszcza złoto w miejscu określonym argumentem, 
/// na określonym poziomie.
Gold::Gold(Level& level, video::ITexture* texture, Wektor position)
{
	wireframe = level.scena()->addCubeSceneNode(10.0f, 0, -2, position, Wektor(0, 0, 0), Wektor(0.3f, 0.3f, 0.3f));
	wireframe->setMaterialTexture( 0, texture ); 
	wireframe->setMaterialFlag( video::EMF_LIGHTING, false );
}
