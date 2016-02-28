#include "Fluff.h"

Fluff* Fluff::create(){
	Fluff* f = new (std::nothrow)Fluff();

	if (f && f->init())
	{
		f->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(f);
	}
	return f;
}

bool Fluff::init(){
	if (!Node::init()){
		return false;
	}

	initializeSprite();
	initializePhysics();

	this->scheduleUpdate();
	
	return true;

}

void Fluff::initializeSprite(){
	fluffSprite = Sprite::create(SPRITE_SOURCE[INDEX_FLUFF]);
	fluffEyesSprite = Sprite::create(SPRITE_SOURCE[INDEX_FLUFF_EYES]);

	this->setScale(cocos2d::random(1.0f, expandMax));
	this->setName(NAME_FLUFF);

	this->addChild(fluffSprite, 1);
	//this->addChild(fluffEyesSprite, 2);

	fluffEyesSprite->setPositionY(fluffEyesSprite->getPositionY() + 5);

}

void Fluff::initializePhysics(){
	physicsBody = PhysicsBody::createCircle(
		fluffSprite->getContentSize().width / 2,
		PhysicsMaterial(density, restitution, friction)
		);

	physicsBody->setVelocityLimit(1);
	physicsBody->setContactTestBitmask(0x01);
	physicsBody->setCategoryBitmask(0x03);

	physicsBody->setLinearDamping(linearDamping);
	
	this->setPhysicsBody(physicsBody);
}


void Fluff::setVelocity(){
	if (physicsBody->getVelocity().x <= 5 
			&& physicsBody->getVelocity().y <= 5){
		float newX = movementSpeed, newY = movementSpeed;

		if (this->getPositionX() > SCREEN_WIDTH / 2)
			newX *= -1;

		if (this->getPositionY() > SCREEN_HEIGHT / 2)
			newY *= -1;

		physicsBody->setVelocity(Vec2(newX, newY));

		float newR = atand(abs(
			GET_DISTANCE_FROM_CENTER_X(this->getPositionX()) /
			GET_DISTANCE_FROM_CENTER_Y(this->getPositionY())
			));

		this->setRotation(newR);

	}
	

}

void Fluff::setExpand(){
	if (isExpandEnabled){
		if (this->getScale() <= expandMax){
			this->setScale(this->getScale() + cocos2d::random(expandIndexMin, expandIndexMax));
		}else{
			auto fluff = Fluff::create();
			this->getParent()->addChild(fluff);

			this->setScale(1);
			fluff->setPosition(this->getPosition());
		}
	}
}
void Fluff::enableExpand(){
	isExpandEnabled = true;
}
void Fluff::disableExpand(){
	isExpandEnabled = false;
}

void Fluff::setMovementExpand(){

	if (movementExpandDirection == Null){
		if (cocos2d::random(0, 1))
			movementExpandDirection = Vertical;
		else
			movementExpandDirection = Horizontal;
	}

	float scale;
	std::function<void(float)> setScale;

	using namespace std::placeholders;
	switch (movementExpandDirection)
	{
	case Horizontal:
		scale = fluffSprite->getScaleX();
		setScale = std::bind(&Sprite::setScaleX, fluffSprite, _1);
		break;
	default:
		scale = fluffSprite->getScaleY();
		setScale = std::bind(&Sprite::setScaleY, fluffSprite, _1);
		break;
	}

	if (scale >= movementExpandMax && !isMovementReverse)
		setScale(scale - cocos2d::random(movementExpandIndexMin, movementExpandIndexMax));
	else if (scale <= 1){
		isMovementReverse = true;
		setScale(scale + cocos2d::random(movementExpandIndexMin, movementExpandIndexMax));
	}
	else{
		isMovementReverse = false;
		movementExpandDirection = Null;
		setScale(1);
	}

	//cocos2d::log("scalex: %f", scaleX);
}

void Fluff::update(float delta){
	setVelocity();

	setExpand();

	setMovementExpand();

	if (!this->isVisible()){
		this->removeFromParent();
	}


}