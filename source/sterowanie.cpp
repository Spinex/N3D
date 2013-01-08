#include "precomp.hpp"
#include "incl.hpp"

bool bBlokadaZapetlaniaAnimacjiSkakania = false;

void GlownaKlasa::sterowaniePostacia() {
	//Roboczo na szybko, pozniej zaimplementuje sie skakanie do metody Move() 
	// Odtad **********************************************************************************************************

	if ( aktywne.IsKeyDown( klawiszSkoku ) && !bStanSkoku && _anim->collisionOccurred() ) {
		bStanSkoku = true;
		// heroWireframe->setFrameLoop(45, 60);
		// heroWireframe->setAnimationSpeed(nSzybkoscAnimacjiGracza / 3);
		bBlokadaZapetlaniaAnimacjiSkakania = false;
	}   
	else if (_anim->collisionOccurred()) {
		bStanSkoku = false;
	}
	
	if (bStanSkoku) {
		if (heroWireframe->getFrameNr() >= 55 && !bBlokadaZapetlaniaAnimacjiSkakania) {
			heroWireframe->setFrameLoop(60,60);
			bBlokadaZapetlaniaAnimacjiSkakania = true;
		}
		core::vector3df v = heroWireframe->getPosition();

		v.Y += fSilaSkoku;
		heroWireframe->setPosition(v);

		moveCameraControl(false);
	}
	else
		bBlokadaZapetlaniaAnimacjiSkakania = false;

	//Dotad *************************************************************************************************************
	 
	int player_direction = 0;
	if ( aktywne.IsKeyDown( irr::KEY_KEY_W ) )
	{
		player_direction |= FORWARD;
		bohaterGry->setBezwladnosc(1);
		bohaterGry->resetAnimAndSpeed();
    }	
	if ( aktywne.IsKeyDown( irr::KEY_KEY_S ) )
	{
		player_direction |= BACKWARD;
		bohaterGry->setBezwladnosc(1);
		bohaterGry->resetAnimAndSpeed();
    }	
	if ( aktywne.IsKeyDown( irr::KEY_KEY_A ) )
	{
		player_direction |= LEFT;
		bohaterGry->setBezwladnosc(1);
		bohaterGry->resetAnimAndSpeed();
    }	
	if ( aktywne.IsKeyDown( irr::KEY_KEY_D ) )
	{
		player_direction |= RIGHT;
		bohaterGry->setBezwladnosc(1);
		bohaterGry->resetAnimAndSpeed();
    }	

	//nic się nie zmieniło
	if(player_direction == 0) {
		
        if (bohaterGry->getBezwladnosc() <= 0) bohaterGry->move(STAND, FORWARD);
	    else bohaterGry->decelerate();   
        
                                  
		moveCameraControl(true);
		return;
	}
	bohaterGry->setDirection(static_cast<DIRECTION>(player_direction));
	bohaterGry->move(WALK, bohaterGry->getDirection());
	moveCameraControl(false);
	
}
