#pragma once
#include "precomp.hpp"

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
	bool onCollision(const scene::ISceneNodeAnimatorCollisionResponse & animator)
	{
		const scene::ISceneNode* collided_node = animator.getCollisionNode();
		printf("CLD %d ", collided_node->getID());
		if (collided_node->getID() == 1337) exit(0);
		return false;
	}
};

extern HeroCollisionCallback hero_collision_callback;

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
	
public:
    void fallDown();
    void stopFallingDown() {fFallingSpeed = 0;}   
    void setJumpState(bool bV) {bStanSkoku = bV;}
    bool getJumpState() {return bStanSkoku;}
    void jump();	

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


class Thwump : public Entity {

};
