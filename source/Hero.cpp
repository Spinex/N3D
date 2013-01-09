#include "precomp.hpp"
#include "incl.hpp"

Hero::Hero(float fSpeed, float Rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed) : AMove(STAND), fMovement_Speed(fMovementSpeed), nAnimation_Speed(nAnimSpeed),
 fBezwladnosc(0), fOpoznienie(fSilaTarcia) {
	heroWireframe->setScale( skala );
	heroWireframe->setPosition( pozycja );
	heroWireframe->setRotation( Wektor( 180, Rotate, 0 ) ); 
	
	heroWireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	heroWireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	heroWireframe->setMaterialTexture( 0, internals.video()->getTexture( Hero_Texture ) ); 
	
	heroWireframe->setAnimationSpeed(nAnimSpeed);  
	
	heroWireframe->setFrameLoop(1,1);
	
	anim = internals.scena()->createCollisionResponseAnimator(internals.selektor_trojkatow(), heroWireframe, Wektor(5,11,5), Wektor(0,-9.81f,0), Wektor(0,-13,0));
	anim->setCollisionCallback(new HeroCollisionCallback());

	heroWireframe->addAnimator(anim);
}

HeroCollisionCallback hero_collision_callback;

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
	anim->drop();
}