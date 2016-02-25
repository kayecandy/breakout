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

	// Physics
	cocos2d::PhysicsBody* physicsBody;


};

#endif //__PLANET_H__