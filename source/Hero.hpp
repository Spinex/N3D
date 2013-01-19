#pragma once
#include "precomp.hpp"

/// Obiekt na planszy.
class Entity
{
private:

public:
	virtual Wektor getPosition() const = 0;
	virtual void refreshState() = 0;
	virtual ~Entity() {}
};

class HeroCollisionCallback : public scene::ICollisionCallback
{
	bool onCollision(const scene::ISceneNodeAnimatorCollisionResponse & animator);
};

/// Główny bohater.
class Hero : public Entity {
private:
	float fRotate;
	DIRECTION dKierunekRuchu;
	ANIMATIONS AMove;
	float fMovement_Speed;
	unsigned nAnimation_Speed;
	float fBezwladnosc;
	float fOpoznienie;
	bool bJestMartwy;
	
	bool bStanSkoku;
	float fFallingSpeed;
	float fGravityAcceleration;
	
	SideCollisionDetector znacznikiKolizji;
	scene::IAnimatedMeshSceneNode* heroWireframe;
	HeroCollisionCallback hero_collision_callback;
	
	std::vector<scene::ISceneNodeAnimatorCollisionResponse*> animators;
	
public:
    void fallDown();
    void stopFallingDown() {fFallingSpeed = 0;}   
    void setJumpState(bool bV) {bStanSkoku = bV;}
    bool getJumpState() {return bStanSkoku;}
    void jump();
//	void invertDirection();
public:
	void rotate(float fValue) {fRotate = fValue;} 
	void move(ANIMATIONS Anim, DIRECTION Direct); 
	void decelerate();
			
	void resetAnimAndSpeed() { fMovement_Speed = fSzybkoscGracza; nAnimation_Speed = nSzybkoscAnimacjiGracza; }
    	
	void setDirection(DIRECTION dValue) {dKierunekRuchu = dValue;}
	void setMovementSpeed(float fV) { fMovement_Speed = fV; }
	void setAnimationSpeed(unsigned nV) {nAnimation_Speed = nV;}
	void setBezwladnosc(float fV) {fBezwladnosc = fV;}
	
public:
	DIRECTION getDirection() const {return dKierunekRuchu;}  
	ANIMATIONS getAnimation() const {return AMove;}
	
	
	SideCollisionDetector& getZnacznikiKolizji() {return znacznikiKolizji;}
	
	float getRotation() const {return fRotate;}
	float getMovementSpeed() const {return fMovement_Speed;}
	float getBezwladnosc() const {return fBezwladnosc;}
	
public:
	Hero(float fSpeed, float Rotate, Wektor pozycja, Wektor skala, unsigned nAnimSpeed, float fMovementSpeed);
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

	DumbDrone(Wektor starting_location);

	Wektor getPosition() const
	{
		return wireframe->getPosition();
	}

};

/// Dron kopiący prądem. Wersja z namierzaniem gracza.
class IntelligentDrone : public Entity {
	void recalculateWaypoints();
};

/// Złoto.
/// Zebranie złota wydłuża czas życia postaci gracza o 2 sekundy.
class Gold : public Entity {

    private:
    scene::IMeshSceneNode* wireframe;

    public:
	Gold(Wektor position);
	void refreshState() {}
	Wektor getPosition() const {return wireframe->getPosition();}
};