#pragma once

typedef scene::ISceneNodeAnimatorCollisionResponse AnimatorKolizji;

int sprawdzKat(DIRECTION dKierunek);

class Level;

class SideCollisionDetector : public Entity
{
private:
	scene::ISceneNode* znaczniki[6];
	AnimatorKolizji* animatory[6];

	float fRotation;
	Wektor relativeDetectorPosition;
	Entity& connected_entity;
public:
	static const int left = 0;
	static const int right = 1;
	static const int forward = 2;
	static const int backward = 3;
	static const int up = 4;
	static const int down = 5;
	
	void setRotation(float rotate, DIRECTION dKierunek);
	void setPosition(Wektor v, float rotate, DIRECTION dKierunek);
	void setVisible(bool bV);
public:
	std::vector<bool> getCollisionState();
	Wektor getPosition() const;
	void refreshState();
public:
	SideCollisionDetector(Level& level, Entity& ent);
	~SideCollisionDetector();
};