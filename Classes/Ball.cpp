#include "Ball.h"

Ball* Ball::create(Block* block){
	Ball* b = new (std::nothrow)Ball();
	b->block = block;


	if (b && b->init())
	{
		b->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(b);
	}

	return b;
}

bool Ball::init(){
	if (!Node::init()){
		return false;
	}

	initializeSprite();
	initializePhysics();
	initializeEvent();

	initializePosition();


	return true;

}

void Ball::initializeSprite(){
	ballSprite = Sprite::create(SPRITE_SOURCE[INDEX_BALL]);

	this->addChild(ballSprite);
	this->setName(NAME_BALL);
	
}

void Ball::initializePhysics(){
	physicsBody = PhysicsBody::createCircle(
		ballSprite->getContentSize().width / 2,
		PhysicsMaterial(density, restitution, friction));

	physicsBody->setVelocityLimit(speed);

	physicsBody->setContactTestBitmask(0x01);
	physicsBody->setCategoryBitmask(0x03);

	this->setPhysicsBody(physicsBody);


}

void Ball::initializePosition(){
	block->blockMovement();
	isMoving = false;
	this->setPosition(Vec2(
		block->getPositionX() + sind(block->getRotation() - 180) * (block->getContentSize().height + ballSprite->getContentSize().height + 10),
		block->getPositionY() + cosd(block->getRotation() - 180) * (block->getContentSize().height + ballSprite->getContentSize().height + 10)));
	
	physicsBody->setAngularVelocity(0);
	physicsBody->setVelocity(Vec2(0, 0));
}

void Ball::initializeEvent(){
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Ball::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactSeparate = CC_CALLBACK_1(Ball::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Ball::onContactSeparate(cocos2d::PhysicsContact& contact){
	auto ball = GET_BODY_FROM_CONTACT(contact, NAME_BALL);
	auto fluff = GET_BODY_FROM_CONTACT(contact, NAME_FLUFF);

	if (ball != NULL){
		auto velocity = ball->getPhysicsBody()->getVelocity();
		
		//cocos2d::log("angle: %f", velocity.getAngle() * M_PI / 180);
		ball->getPhysicsBody()->setVelocity(Vec2(
			cos(velocity.getAngle()) * speed,
			sin(velocity.getAngle()) * speed));
	}
	

	if (ball != NULL && fluff != NULL){
		
		fluff->setVisible(false);
		fluff->getPhysicsBody()->setContactTestBitmask(0x00);
		fluff->getPhysicsBody()->setCollisionBitmask(0x00);
		
	}
	
		

}

void Ball::onKeyPressed(EventKeyboard::KeyCode key, Event* e){
	switch (key){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		if (!isMoving){
			block->allowMovement();
			isMoving = true;
			//this->scheduleUpdate();

			physicsBody->setAngularVelocity(10);

			int mx = 1, my = 1;
			if (GET_DISTANCE_FROM_CENTER_X(this->getPositionX()) > 0)
				mx = -1;
			if (GET_DISTANCE_FROM_CENTER_Y(this->getPositionY()) > 0)
				my = -1;

			physicsBody->setVelocity(Vec2(sind(block->getRotation()-180)*speed, cosd(block->getRotation()-180)*speed));
			cocos2d::log("correct");
		}

		break;
	}
}



void Ball::update(float delta){
	/*cocos2d::log("%d %d %f",
		physicsBody->getVelocity().x, 
		physicsBody->getVelocity().y,
		delta);
	*/

	if (!IS_INSIDE_SCREEN(this->getPosition())){
		initializePosition();
	}


	//if (isMoving)
		//physicsBody->setVelocity(Vec2(-1 *speed, -1*speed));
}