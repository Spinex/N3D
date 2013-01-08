#include "precomp.hpp"
#include "incl.hpp"

void GlownaKlasa::petlaGry()
{
	while(device->run())
	{
		if(aktywne.IsKeyDown( irr::KEY_ESCAPE ))
			break;

		sterowaniePostacia();

		video->beginScene( true, true, video::SColor( 0, 0, 10, 200 ) );
		menage->drawAll();
		
		konsola->showMessages();
		
		video->endScene();
	}
}
