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

	initializeSprite();
	initializePhysics();
	//initializeEvent();


	return true;
}

void Planet::initializeSprite(){
	glowSprite = Sprite::create(SPRITE_SOURCE[INDEX_PLANET_GLOW]);
	planetSprite = Sprite::create(SPRITE_SOURCE[INDEX_PLANET]);

	this->setName("Planet");

	this->addChild(glowSprite, 1);
	this->addChild(planetSprite, 2);
}

void Planet::initializePhysics(){
	physicsBody = PhysicsBody::createCircle(
		planetSprite->getContentSize().width / 2,
		PhysicsMaterial(density, restitution, friction));
	//physicsBody->setDynamic(false);

	//physicsBody->setLinearDamping(1);
	//physicsBody->setAngularDamping(1);

	this->setPhysicsBody(physicsBody);
}

void Planet::initializeEvent(){
	auto listener = EventListenerPhysicsContact::create();

	//auto listener = EventListenerPhysicsContactWithGroup::create(CONTACT_GROUP_FLUFF);
	listener->onContactBegin = CC_CALLBACK_1(Planet::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Planet::onContactBegin(cocos2d::PhysicsContact& contact){

	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	
	if ((bodyA->getNode()->getName() == "Planet"
		|| bodyB->getNode()->getName() == "Planet") 
		&&
		(bodyA->getNode()->getName() == "Fluff"
		|| bodyB->getNode()->getName() == "Fluff")){
		bodyA->setVelocityLimit(0);
		bodyB->setVelocityLimit(0);
	}
	cocos2d::log("colid");

	return true;
}

void Planet::update(float delta){
	this->setPosition(POSITION_CENTER_CENTER);
}