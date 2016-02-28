#ifndef __PLANET_H__
#define __PLANET_H__

#include "Globals.h"

class Planet : public cocos2d::Node
{
public:
	static class Planet* create();
	virtual bool init();
	
private:
	// Sprites
	cocos2d::Sprite* glowSprite;
	cocos2d::Sprite* planetSprite;

	// Initializers
	void initializeSprite();
	void initializePhysics();
	void initializeEvent();

	// Physics
	cocos2d::PhysicsBody* physicsBody;
	float density = 1;
	float friction = 0.5;
	float restitution = 1;

	bool onContactBegin(cocos2d::PhysicsContact&);

	// Update
	void update(float) override;

};

#endif //__PLANET_H__