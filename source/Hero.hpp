#pragma once
#include "precomp.hpp"

class HeroCollisionCallback : public scene::ICollisionCallback
{
	bool onCollision(const scene::ISceneNodeAnimatorCollisionResponse & animator);
};

/// Główny bohater.
class Hero : public Entity {
private:
	unsigned animation_speed;
	float bezwladnosc;
	float opoznienie;
	bool stan_skoku;
	float falling_speed;
	float gravity_acceleration;
	
	float rotation;
	DIRECTION kierunek_ruchu;
	ANIMATIONS animation_type;
	float movement_speed;
	float time_to_live;
	Wektor velocity;
	SideCollisionDetector znacznikiKolizji;
	scene::IAnimatedMeshSceneNode* wireframe;
	std::vector<scene::ISceneNodeAnimatorCollisionResponse*> animators;
	
public: // these should not exist
	void fallDown();
	void stopFallingDown() {falling_speed = 0;}
	void setJumpState(bool bV) {stan_skoku = bV;}
	bool getJumpState() {return stan_skoku;}
	void decelerate();
	void resetAnimAndSpeed() { movement_speed = SzybkoscGracza; animation_speed = SzybkoscAnimacjiGracza; }
	void setMovementSpeed(float fV) { movement_speed = fV; }
	void setAnimationSpeed(unsigned nV) {animation_speed = nV;}
	void setBezwladnosc(float fV) {bezwladnosc = fV;}
	DIRECTION getDirection() const {return kierunek_ruchu;}  
	ANIMATIONS getAnimation() const {return animation_type;}
	float getRotation() const {return rotation;}
	float getMovementSpeed() const {return movement_speed;}
	float getBezwladnosc() const {return bezwladnosc;}

public:
	void jump();
	void rotate(float r) {rotation = r;} 
	void move(ANIMATIONS anim, DIRECTION direct); 
	void setDirection(DIRECTION dValue) {kierunek_ruchu = dValue;}
	
public:	
	SideCollisionDetector& getZnacznikiKolizji() {return znacznikiKolizji;}
	
public:
	Hero(Level& level, video::ITexture* texture, float fSpeed, float rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed);
	~Hero();
	void refreshState();
	Wektor getPosition() const;
};    

/// Spadająca sześcienna platforma z jedną powierzchnią kopiącą prądem.
class Thwump : public Entity {

};

/// Dron kopiący prądem. 
class DumbDrone : public Entity {
private:
	std::vector<Wektor> waypoints;
	std::size_t current;
	scene::IAnimatedMeshSceneNode* wireframe;

	void followNextTarget() { current = (current+1)%waypoints.size(); }
	Wektor currentTarget() { return waypoints[current]; }
public:
	void refreshState();

	DumbDrone(Level& level, video::ITexture* texture, Wektor starting_location);

	Wektor getPosition() const
	{
		return wireframe->getPosition();
	}

};

/// Dron kopiący prądem. Wersja z namierzaniem gracza.
class IntelligentDrone : public DumbDrone {
	void recalculateWaypoints();
};

/// Złoto.
/// Zebranie złota wydłuża czas życia postaci gracza o 2 sekundy.
class Gold : public Entity {

    private:
    scene::IMeshSceneNode* wireframe;

    public:
	Gold(Level& level, video::ITexture* texture, Wektor position);
	void refreshState() {}
	Wektor getPosition() const {return wireframe->getPosition();}
};