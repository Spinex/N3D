#include "precomp.hpp"
#include "incl.hpp"

bool bBlokadaZapetlaniaAnimacjiSkakania = false;

int time_interval = 0;

void InputOutputHandler::sterowaniePostacia(Hero& hero)
{
	// Sprawdzanie stanu kolizji	
	std::vector<bool> bStany = hero.getZnacznikiKolizji().getCollisionState();
	
	// Blad - Kiedy ustawia sie na niewidoczny, detektor przestaje dzialac.
	if (IsKeyDown( irr::KEY_KEY_Q ))
	{
		hero.getZnacznikiKolizji().setVisible(false);
	}
	if (IsKeyDown( irr::KEY_KEY_E ))
	{
		hero.getZnacznikiKolizji().setVisible(true);
	}
	
	konsola.setMessage(0, bStany[0] ? "left: true" : "left: false");
	konsola.setMessage(1, bStany[1] ? "right: true" : "right: false");
	konsola.setMessage(2, bStany[2] ? "forward: true" : "forward: false");
	konsola.setMessage(3, bStany[3] ? "back: true" : "back: false");
	konsola.setMessage(4, bStany[4] ? "up: true" : "up: false");
	konsola.setMessage(5, bStany[5] ? "down: true" : "down: false");

	// przerobić na callback, serio
	if(!bStany[SideCollisionDetector::down])
		hero.fallDown();
	else
		hero.stopFallingDown();


	hero.getZnacznikiKolizji().setPosition(hero.getPosition(), hero.getRotation(), hero.getDirection());
	hero.getZnacznikiKolizji().setRotation(hero.getRotation(), hero.getDirection());


	if ( IsKeyDown( klawiszSkoku ) && !hero.getJumpState() && bStany[SideCollisionDetector::down] )
	{
		hero.setJumpState(true);
		hero.stopFallingDown();
	}
	else if	(IsKeyDown( klawiszSkoku ) && (!bStany[SideCollisionDetector::down] && bStany[SideCollisionDetector::forward]))
	{
		hero.setJumpState(true);
		hero.stopFallingDown();
		hero.rotate(hero.getRotation() + 180);
		time_interval = 15;
	}
	else if (bStany[SideCollisionDetector::down] || bStany[SideCollisionDetector::up])
		hero.setJumpState(false);
	if(hero.getJumpState())
		hero.jump();

	int player_direction = 0;
	if ( IsKeyDown( irr::KEY_KEY_W ) )
		player_direction |= FORWARD;
	if ( IsKeyDown( irr::KEY_KEY_S ) )
		player_direction |= BACKWARD;
	if ( IsKeyDown( irr::KEY_KEY_A ) )
		player_direction |= LEFT;
	if ( IsKeyDown( irr::KEY_KEY_D ) )
		player_direction |= RIGHT;

	//nic się nie zmieniło
	if(player_direction == 0) {
		
        if (hero.getBezwladnosc() <= 0) hero.move(STAND, FORWARD);
	    else hero.decelerate();
           
        hero.getZnacznikiKolizji().setPosition(hero.getPosition(), hero.getRotation(), hero.getDirection());
        hero.getZnacznikiKolizji().setRotation(hero.getRotation(), hero.getDirection());

		moveCameraControl();
		hero.rotate(direction - 90);
		return;
	}
	else {
		hero.setBezwladnosc(1);
		hero.resetAnimAndSpeed();
		hero.setDirection(static_cast<DIRECTION>(player_direction));
		
		hero.getZnacznikiKolizji().setPosition(hero.getPosition(), hero.getRotation(), hero.getDirection()); 
		hero.getZnacznikiKolizji().setRotation(hero.getRotation(), hero.getDirection());

		hero.move(WALK, hero.getDirection());
		
		if (!hero.getJumpState() || time_interval <= 0)
		{
		    moveCameraControl();
		}	
		else 
		{		
		   moveCameraControl();
		   hero.rotate(direction - 90);
		   time_interval -= 1;
		}
	}
	hero.rotate(direction - 90);
}

void InputOutputHandler::moveCameraControl() {
	// TODO: drop the need for global variable
	extern IrrlichtInternals internals;
	extern Level level;
	core::position2d<f32> cursorPos = internals->getCursorControl()->getRelativePosition();
	//Wektor cameraPos = pKamera->getAbsolutePosition();
	
	float change_x = ( cursorPos.X - 0.5 ) * 64.0f;
	float change_y = ( cursorPos.Y - 0.5 ) * 64.0f;
	direction += change_x;
	zdirection -= change_y;
	if( zdirection < -80 )
		zdirection = -80;
	else if( zdirection > -10 )
		zdirection = -10;
	internals->getCursorControl()->setPosition( 0.5f, 0.5f );

	Wektor playerPos = level.bohaterGry->getPosition();

	float xf = playerPos.X - cos( direction * core::PI / 180.0f ) * 32.0f;
	float yf = playerPos.Y - sin( zdirection * core::PI / 180.0f ) * 32.0f;
	float zf = playerPos.Z + sin( direction * core::PI / 180.0f ) * 32.0f;

	pKamera->setPosition( Wektor( xf, yf, zf ) );
	pKamera->setTarget( Wektor( playerPos.X, playerPos.Y + 10.0f, playerPos.Z ) );
}

InputOutputHandler::InputOutputHandler(const IrrlichtInternals& spDevice) :
	direction(0),
	zdirection(0)
{
	spDevice->getCursorControl()->setVisible(false);
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[ i ] = false;
	pKamera = spDevice->getSceneManager()->addCameraSceneNode(0, Wektor(0.0f,0.0f,0.0f) , Wektor(0.0f,0.0f,0.0f), -1);
	spDevice->setEventReceiver(this);
}