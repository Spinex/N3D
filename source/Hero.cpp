#include "precomp.hpp"
#include "incl.hpp"

Hero::Hero(float fSpeed, float Rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed) :
	fRotate(Rotate),
	dKierunekRuchu(FORWARD),
	AMove(STAND),
	fMovement_Speed(fMovementSpeed),
	nAnimation_Speed(nAnimSpeed),
	fBezwladnosc(0),
	fOpoznienie(fSilaTarcia),
	bJestMartwy(false),
	bStanSkoku(false),
	fFallingSpeed(0),
	heroWireframe(NULL)
{
	heroWireframe = internals.scena()->addAnimatedMeshSceneNode(heroMesh);
	if(!heroWireframe)
		{} //wywal program na zbity pysk (ewentualnie grzecznie zgłoś błąd)
	heroWireframe->setScale( skala );
	heroWireframe->setPosition( pozycja );
	heroWireframe->setRotation( Wektor( 180, Rotate, 0 ) ); 
	
	heroWireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	heroWireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	heroWireframe->setMaterialTexture( 0, internals.video()->getTexture( Hero_Texture ) ); 
	
	heroWireframe->setAnimationSpeed(nAnimSpeed);  
	
	heroWireframe->setFrameLoop(1,1);

  // Eksperymenty poczatek	
//	anim = internals.scena()->createCollisionResponseAnimator(internals.selektor_trojkatow(), heroWireframe, Wektor(5,11,5), Wektor(0,0,0), Wektor(0,-13,0));
//	animKladki = internals.scena()->createCollisionResponseAnimator(selectorKladki, heroWireframe, Wektor(5,11,5), Wektor(0,0,0), Wektor(0,-13,0));
//	anim->setCollisionCallback(new HeroCollisionCallback());

 //   animKladki->setCollisionCallback(new HeroCollisionCallback()); 

 std::vector<scene::ITriangleSelector*>& selectors = internals.getSelectors(); 
 
 for (unsigned i = 0; i < selectors.size(); i++)
 {
      scene::ISceneNodeAnimatorCollisionResponse* animator = 
	  internals.scena()->createCollisionResponseAnimator(selectors[i], heroWireframe, Wektor(5,11,5), Wektor(0,0,0), Wektor(0,-13,0)); 
	  
	  animator->setCollisionCallback(&hero_collision_callback);
	  heroWireframe->addAnimator(animator);

      animators.push_back(animator);
	 
 }  
 
      scene::ISceneNodeAnimatorCollisionResponse* animator = 
	  internals.scena()->createCollisionResponseAnimator(internals.selektor_trojkatow(), heroWireframe, Wektor(5,11,5), Wektor(0,0,0), Wektor(0,-13,0)); 
	  
	  heroWireframe->addAnimator(animator);
	  animators.push_back(animator);

 //	heroWireframe->addAnimator(anim);
  //  heroWireframe->addAnimator(animKladki);
  // Eksperymenty koniec	
}

void Hero::move(ANIMATIONS Anim, DIRECTION Direct) {
	Wektor v = heroWireframe->getPosition();

	if (Anim != STAND)
	{
		int angle = sprawdzKat(Direct);
		v.Z += fMovement_Speed * cos(( core::PI * (fRotate - 90 + angle)) / 180);
		v.X += fMovement_Speed * sin(( core::PI * (fRotate - 90 + angle)) / 180);
		heroWireframe->setPosition( v );
		heroWireframe->setRotation( Wektor( 180, fRotate + angle, 0 ) );
	}

	if ((AMove == STAND || AMove == DECELERATION) && Anim == WALK) {
		heroWireframe->setFrameLoop(15, 34);
		heroWireframe->setAnimationSpeed( nAnimation_Speed );
		AMove = WALK;
		heroWireframe->setAnimationSpeed( nAnimation_Speed );
	}
	else if ((AMove == STAND || AMove == WALK) && Anim == DECELERATION) {
		heroWireframe->setFrameLoop(5, 5);
		heroWireframe->setAnimationSpeed( nAnimation_Speed ); 
		AMove = DECELERATION;
	}
	else if (Anim == STAND) {
		heroWireframe->setFrameLoop(1, 1);
		heroWireframe->setAnimationSpeed( nAnimation_Speed );
		AMove = STAND;
	}
}

void Hero::refreshState()
{
	// to tylko zalążek
}

void Hero::decelerate() 
{
	fBezwladnosc -= fOpoznienie;
	fMovement_Speed = fBezwladnosc * fSzybkoscGracza;

	move(DECELERATION, dKierunekRuchu);
}

Wektor Hero::getPosition() const
{
	return heroWireframe->getPosition();
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
    fGravityAcceleration = 0.2;     
    Wektor v = heroWireframe->getPosition();
    v.Y -= fFallingSpeed;
    heroWireframe->setPosition( v );
    fFallingSpeed += fGravityAcceleration;
} 

void Hero::jump()
{
   core::vector3df v = heroWireframe->getPosition();
   v.Y += fSilaSkoku;
   heroWireframe->setPosition(v);
}   

/* void Hero::invertDirection()
{
   switch (dKierunekRuchu)
   {
      case FORWARD: dKierunekRuchu = BACKWARD; break;
	  case BACKWARD: dKierunekRuchu = FORWARD; break;
	  case LEFT: dKierunekRuchu = RIGHT; break;
	  case RIGHT: dKierunekRuchu = LEFT; break;
	  case UP: dKierunekRuchu = DOWN; break;
	  case DOWN: dKierunekRuchu = UP; break;
	  case LEFT | FORWARD: dKierunekRuchu = RIGHTBACKWARD; break;
	  case RIGHT | FORWARD: dKierunekRuchu = LEFTBACKWARD; break;
	  case LEFT | BACKWARD: dKierunekRuchu = RIGHTFORWARD; break;
	  case RIGHT | BACKWARD: dKierunekRuchu = LEFTFORWARD; break;
   }	  
} */     

DumbDrone::DumbDrone(Wektor starting_location) :
	current(0)
{
	auto* mesh = internals.scena()->getMesh("postacie/drone.obj"); //auto - nowa funkcjonalność C++11
	wireframe = internals.scena()->addAnimatedMeshSceneNode(mesh);
	if(!wireframe)
		{} //wywal program na zbity pysk (ewentualnie grzecznie zgłoś błąd)
	wireframe->setScale( Wektor(-5, -5, -5) );
	wireframe->setPosition( starting_location );
	wireframe->setRotation( Wektor( 180, 42, 0 ) ); 

	wireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	wireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	wireframe->setMaterialTexture( 0, internals.video()->getTexture( "postacie/dronetekstura.png" ) ); 

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

void IntelligentDrone::recalculate_waypoints()
{
	// to tylko zalążek
}


Gold::Gold(Wektor position)
{
     wireframe = internals.scena()->addCubeSceneNode(10.0f, 0, -2, position, Wektor(0, 0, 0), Wektor(0.3f, 0.3f, 0.3f));
	 wireframe->setMaterialTexture( 0, internals.video()->getTexture( "postacie/goldtekstura.png" ) ); 
	 wireframe->setMaterialFlag( video::EMF_LIGHTING, false );
}