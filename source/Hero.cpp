#include "naglowek.hpp"

Hero::Hero(float fSpeed, float Rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed) : AMove(STAND), fMovement_Speed(fMovementSpeed), nAnimation_Speed(nAnimSpeed),
 fBezwladnosc(0), fOpoznienie(fSilaTarcia) {
					
	heroWireframe->setScale( skala );
	heroWireframe->setPosition( pozycja );
	heroWireframe->setRotation( core::vector3df( 180, Rotate, 0 ) ); 
	
	heroWireframe->setMaterialFlag( video::EMF_LIGHTING, false );
	heroWireframe->setMaterialFlag( video::EMF_BACK_FACE_CULLING, false);
	heroWireframe->setMaterialTexture( 0, _video->getTexture( Hero_Texture ) ); 
	
	heroWireframe->setAnimationSpeed(nAnimSpeed);  
	
	heroWireframe->setFrameLoop(1,1);
	
	_anim = _menage->createCollisionResponseAnimator(_metaSelector, heroWireframe, core::vector3df(5,11,5), core::vector3df(0,-9.81f,0), core::vector3df(0,-13,0));
	_anim->setCollisionCallback(&hero_collision_callback);

	heroWireframe->addAnimator(_anim);
}

HeroCollisionCallback hero_collision_callback;

void Hero::move(ANIMATIONS Anim, DIRECTION Direct) {
	core::vector3df v = heroWireframe->getPosition();

	if (Anim != STAND)
	{
		int angle;
		switch(Direct)
		{
			case FORWARD: angle = 270; break;
			case BACKWARD: angle = 90; break;
			case LEFT: angle = 180; break;
			case RIGHT: angle = 0; break;
			case LEFT | FORWARD: angle = 180 + 45; break;
			case RIGHT | FORWARD: angle = 0 - 45; break;
			case LEFT | BACKWARD: angle = 180 - 45; break;
			case RIGHT | BACKWARD: angle = 0 + 45; break;
			default: angle = 270; break;
		}
		v.Z += fMovement_Speed * cos(( PI * (fRotate - 90 + angle)) / 180);
		v.X += fMovement_Speed * sin(( PI * (fRotate - 90 + angle)) / 180);
		heroWireframe->setPosition( v );
		heroWireframe->setRotation( core::vector3df( 180, fRotate + angle, 0 ) );
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

}

void Hero::decelerate() 
{
     
     fBezwladnosc -= fOpoznienie;
     
     fMovement_Speed = fBezwladnosc * fSzybkoscGracza;
    
     
     move(DECELERATION, dKierunekRuchu);
         
}     

Wektor Hero::getPosition() const
{
	// to tylko zalążek
    //	return Wektor(0, 0, 0);

    // Moja propozycja 
    
    return heroWireframe->getPosition();  
 	
}
