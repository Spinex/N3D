#include "precomp.hpp"
#include "incl.hpp"

bool bBlokadaZapetlaniaAnimacjiSkakania = false;

void IrrlichtInternals::sterowaniePostacia() {

	// Sprawdzanie stanu kolizji

	// sztuczna "inteligencja" drona
	drone->refreshState();
	
	std::vector<bool> bStany = bohaterGry->getZnacznikiKolizji().getCollisionState();
	
	// do przyszłego użytku
	//bool bCzyJestWidoczny = true;
	
	// Blad - Kiedy ustawia sie na niewidoczny, detektor przestaje dzialac.
	
	/*if (aktywne.IsKeyDown( irr::KEY_KEY_Q ))
	{
		bCzyJestWidoczny = !bCzyJestWidoczny;  
		bohaterGry->getZnacznikiKolizji().setVisible(bCzyJestWidoczny);                   
	}*/
	
	core::stringw str;
	
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
		
		
       if(!bStany[5])
       {
         bohaterGry->fallDown();
         bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection());   
         bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());
       }     
       else
       {   
         bohaterGry->stopFallingDown();  
         bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection());   
         bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());  
       }      
          	   
    
       if ( aktywne.IsKeyDown( klawiszSkoku ) && !bohaterGry->getJumpState() && bStany[5] ) 	        
       { 
         bohaterGry->setJumpState(true);
	 bohaterGry->stopFallingDown();  
       }
       else if	(aktywne.IsKeyDown( klawiszSkoku ) && (!bStany[5] && bStany[2]))
       {
         bohaterGry->setJumpState(true);
	 bohaterGry->stopFallingDown();  
	 bohaterGry->rotate(bohaterGry->getRotation() + 180);
       }	   
       else if (bStany[5] || bStany[4]) bohaterGry->setJumpState(false);	
       if (bohaterGry->getJumpState()) bohaterGry->jump();
	   
	   	     
	 
	int player_direction = 0;
	if ( aktywne.IsKeyDown( irr::KEY_KEY_W ) )
		player_direction |= FORWARD;
	if ( aktywne.IsKeyDown( irr::KEY_KEY_S ) )
		player_direction |= BACKWARD;
	if ( aktywne.IsKeyDown( irr::KEY_KEY_A ) )
		player_direction |= LEFT;
	if ( aktywne.IsKeyDown( irr::KEY_KEY_D ) )
		player_direction |= RIGHT;

	//nic się nie zmieniło
	if(player_direction == 0) {
		
        if (bohaterGry->getBezwladnosc() <= 0) bohaterGry->move(STAND, FORWARD);
	    else bohaterGry->decelerate(); 
           
           bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection());   
           bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());
             
                                        
		moveCameraControl(true);
		return;
	}
	else {
		bohaterGry->setBezwladnosc(1);
		bohaterGry->resetAnimAndSpeed();
		bohaterGry->setDirection(static_cast<DIRECTION>(player_direction));
		
		bohaterGry->getZnacznikiKolizji().setPosition(bohaterGry->getPosition(), bohaterGry->getRotation(), bohaterGry->getDirection()); 
		bohaterGry->getZnacznikiKolizji().setRotation(bohaterGry->getRotation(), bohaterGry->getDirection());

		bohaterGry->move(WALK, bohaterGry->getDirection());
		
		if (!bohaterGry->getJumpState())
		moveCameraControl(false);
		else moveCameraControl(true);
	}
}
