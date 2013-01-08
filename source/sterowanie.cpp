#include "precomp.hpp"
#include "incl.hpp"

bool bBlokadaZapetlaniaAnimacjiSkakania = false;

void GlownaKlasa::sterowaniePostacia() {
     
     	// Sprawdzanie stanu kolizji
	
	vector<bool> bStany = bohaterGry->getZnacznikiKolizji().getCollisionState();
	
	bool bCzyJestWidoczny = true;
	
	// Blad - Kiedy ustawia sie na niewidoczny, detektor przestaje dzialac.
	
 /*	if (aktywne.IsKeyDown( irr::KEY_KEY_Q ))
	{
                
        if (bCzyJestWidoczny) bCzyJestWidoczny = false;    
        else bCzyJestWidoczny = true;    
        
        bohaterGry->getZnacznikiKolizji().setVisible(bCzyJestWidoczny);                   
    }    */                   
	
	stringw str;
	
	if (bStany[0]) str = "left: true";  
	else str = "left: false";
        konsola->setMessage(0, str);
        
    if (bStany[1]) str = "right: true";  
	else str = "right: false";
        konsola->setMessage(1, str);  
          
    if (bStany[2]) str = "forward: true";  
	else str = "forward: false";
        konsola->setMessage(2, str);
        
    if (bStany[3]) str = "back: true";  
	else str = "back: false";
        konsola->setMessage(3, str);
        
    if (bStany[4]) str = "up: true";  
	else str = "up: false";
        konsola->setMessage(4, str);
        
    if (bStany[5]) str = "down: true";  
	else str = "down: false";
        konsola->setMessage(5, str);
        
    // *************************************************************************************************************    
     
     
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
           
           bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection());   
           bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());
             
                                        
		moveCameraControl(true);
		return;
	}
	bohaterGry->setDirection(static_cast<DIRECTION>(player_direction));
	
	bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection()); 
    bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());
    
    
	bohaterGry->move(WALK, bohaterGry->getDirection());
	moveCameraControl(false);
	
	
                   
	
}
