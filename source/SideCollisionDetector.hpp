#pragma once
#include "precomp.hpp"

typedef scene::ISceneNodeAnimatorCollisionResponse AnimatorKolizji;

int sprawdzKat(DIRECTION dKierunek);

class SideCollisionDetector 
{
private:
	scene::ISceneNode* leftZnacznik;
	scene::ISceneNode* rightZnacznik;
	scene::ISceneNode* forwardZnacznik;
	scene::ISceneNode* backZnacznik;
	scene::ISceneNode* upZnacznik;
	scene::ISceneNode* downZnacznik;

	AnimatorKolizji* leftAnimator;
	AnimatorKolizji* rightAnimator;
	AnimatorKolizji* forwardAnimator;
	AnimatorKolizji* backAnimator;
	AnimatorKolizji* upAnimator;
	AnimatorKolizji* downAnimator;

	float fRotation;

	Wektor relativeDetectorPosition;
public:
	void setRotation(float fRotate, DIRECTION dKierunek);
	void setPosition(Wektor v, float fRotate, DIRECTION dKierunek);
	void setVisible(bool bV);
public:
	std::vector<bool> getCollisionState();
public:
	SideCollisionDetector();
	~SideCollisionDetector();

};