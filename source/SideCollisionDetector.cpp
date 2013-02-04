#include "precomp.hpp"
#include "incl.hpp"

int sprawdzKat(DIRECTION dKierunek)
{
	switch(dKierunek) {
	case FORWARD:
		return 270;
	case BACKWARD:
		return 90;
	case LEFT:
		return 180;
	case RIGHT:
		return 0;
	case LEFT | FORWARD:
		return 180 + 45;
	case RIGHT | FORWARD:
		return 0 - 45;
	case LEFT | BACKWARD:
		return 180 - 45;
	case RIGHT | BACKWARD:
		return 0 + 45;
	default:
		return 270;
	}
}

SideCollisionDetector::SideCollisionDetector(Level& level, Entity& ent) : connected_entity(ent)
{
	znaczniki[forward] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.15f, 0.0f, 0.0f));
	znaczniki[backward] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.15f, 0.0f, 0.0f));
	znaczniki[up] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.0f, 0.15f, 0.0f));
	znaczniki[down] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.0f, 0.15f, 0.0f));
	znaczniki[right] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.0f, 0.0f, 0.15f));
	znaczniki[left] = level.scena()->addCubeSceneNode(3.0f, 0, -1, Wektor(0, 10, 10), Wektor(0, 0, 0), Wektor(0.0f, 0.0f, 0.15f));
	
	animatory[forward] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[forward], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
	animatory[backward] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[backward], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
	animatory[up] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[up], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
	animatory[down] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[down], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
	animatory[right] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[right], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
	animatory[left] = level.scena()->createCollisionResponseAnimator(level.selektor_trojkatow(), znaczniki[left], core::vector3df(3,3,3), core::vector3df(0,0,0), core::vector3df(0,0,0));
				   
	znaczniki[forward]->addAnimator(animatory[forward]);
	znaczniki[down]->addAnimator(animatory[down]);
	znaczniki[backward]->addAnimator(animatory[backward]);
	znaczniki[up]->addAnimator(animatory[up]);
	znaczniki[left]->addAnimator(animatory[left]);
	znaczniki[right]->addAnimator(animatory[right]);
}

void SideCollisionDetector::setPosition(Wektor v, float rotate, DIRECTION dKierunek)
{
	// Wiem ze implementacja toporna, pisana na kolanie, lenistwo
	
	int angle = sprawdzKat(dKierunek);
	int radius = 5;
	
	Wektor originalCoordinates = v;
	
	// Odpowiednia translacja
	v.Z += radius * cos(( core::PI * (rotate - 90 + angle)) / 180);
	v.X += radius * sin(( core::PI * (rotate - 90 + angle)) / 180);
	v.Y += 15;
	
	znaczniki[forward]->setPosition( v );
	
	// *******************************************************
	
	v = originalCoordinates;
	
	v.Z -= radius * cos(( core::PI * (rotate - 90 + angle)) / 180);
	v.X -= radius * sin(( core::PI * (rotate - 90 + angle)) / 180);
	v.Y += 15;
	
	znaczniki[backward]->setPosition( v );
	
	// ********************************************************
	
	v = originalCoordinates;
	
	v.Y += 22;
	
	znaczniki[up]->setPosition( v );
	
	// ********************************************************
	
	v = originalCoordinates;
	
	v.Y += 4;
	
	znaczniki[down]->setPosition( v );
	
	// *********************************************************
	
	v = originalCoordinates;
	
	angle += 90;
	
	v.Z += radius * cos(( core::PI * (rotate - 90 + angle)) / 180);
	v.X += radius * sin(( core::PI * (rotate - 90 + angle)) / 180);
	v.Y += 15;
	
	znaczniki[right]->setPosition( v );
	
	// *********************************************************
	
	v = originalCoordinates;
	
	v.Z -= radius * cos(( core::PI * (rotate - 90 + angle)) / 180);
	v.X -= radius * sin(( core::PI * (rotate - 90 + angle)) / 180);
	v.Y += 15;
	
	znaczniki[left]->setPosition( v );
	
}

void SideCollisionDetector::setRotation(float rotate, DIRECTION dKierunek)
{
	int angle = sprawdzKat(dKierunek);
	for(auto& znacznik : znaczniki)
		znacznik->setRotation( Wektor( 0, rotate + angle, 0 ) );
}

void SideCollisionDetector::setVisible(bool bV)
{
	znaczniki[left]->setVisible(bV);
	znaczniki[right]->setVisible(bV);
	znaczniki[forward]->setVisible(bV);
	znaczniki[backward]->setVisible(bV);
	znaczniki[up]->setVisible(bV);
	znaczniki[down]->setVisible(bV);
}

std::vector<bool> SideCollisionDetector::getCollisionState()
{
	std::vector<bool> stany(6, false);
	for(int i = 0; i < 6; ++i)
	{
		stany[i] = animatory[i]->collisionOccurred();
	}
	return stany;
}

SideCollisionDetector::~SideCollisionDetector()
{
	for(auto& animator : animatory)
		animator->drop();
}

Wektor SideCollisionDetector::getPosition() const
{
	return connected_entity.getPosition();
}

void SideCollisionDetector::refreshState()
{
	
}