#include "Planet.h"

Planet* Planet::create(){
	Planet* p = new (std::nothrow)Planet();

	if (p && p->init())
	{
		p->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(p);
	}
	return p;
}

bool Planet::init(){
	if (!Node::init()){
		return false;
	}

	glowSprite = Sprite::create(SPRITE_SOURCE[INDEX_PLANET_GLOW]);
	planetSprite = Sprite::create(SPRITE_SOURCE[INDEX_PLANET]);

	this->addChild(glowSprite, 1);
	this->addChild(planetSprite, 2);

	physicsBody = PhysicsBody::createCircle(planetSprite->getContentSize().width/2);
	physicsBody->setDynamic(false);

	this->setPhysicsBody(physicsBody);

	return true;
}