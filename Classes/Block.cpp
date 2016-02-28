#include "Block.h"

Block* Block::create(){
	Block* b = new (std::nothrow)Block();

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

bool Block::init(){

	if (!Node::init()){
		return false;
	}

	initializeNode();
	initializeEvents();
	

	return true;
}

void Block::initializeNode(){
	blockSprite = Sprite::create(SPRITE_SOURCE[INDEX_BLOCK]);
	this->addChild(blockSprite);
	this->setName(NAME_BLOCK);

	physicsBody = PhysicsBody::createBox(
		blockSprite->getContentSize(), 
		PhysicsMaterial(density, restitution, friction));
	
	//physicsBody->setDynamic(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(0x01);
	physicsBody->setCategoryBitmask(0x03);
	
	this->setPhysicsBody(physicsBody);

	setRelativePosition(30);

}

void Block::initializeEvents(){
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Block::onKeyboardPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Block::onKeyboardReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Block::setRelativePosition(float angle){
		positionAngle = (int)(positionAngle + angle) % 360;

		float newX = sind(positionAngle) * distanceFromCenter;
		float newY = cosd(positionAngle) * distanceFromCenter;


		//auto move = MoveTo::create(moveDuration, Vec2(newX, newY));

		this->setPositionX(POSITION_CENTER_CENTER.x + newX);
		this->setPositionY(POSITION_CENTER_CENTER.y + newY);

		this->setRotation(positionAngle);
}

void Block::onKeyboardPressed(EventKeyboard::KeyCode key, Event* e){
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isKeyPressed = true;

		if (isBallMoving)
			this->runAction(Sequence::create(
				DelayTime::create(movementSpeed),
				CallFunc::create(std::bind(&Block::whileKeyboardPressed, this, key, e)),
				NULL));

		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		movementDistance += movementFast;
		break;
	}

	cocos2d::log("correct2");
	
	
}

void Block::whileKeyboardPressed(EventKeyboard::KeyCode key, Event* e){
	if (isKeyPressed){
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			setRelativePosition(-1 * movementDistance);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			setRelativePosition(movementDistance);
			break;
		}

		onKeyboardPressed(key, e);
	}

	
}

void Block::onKeyboardReleased(EventKeyboard::KeyCode key, Event* e){
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		isKeyPressed = false;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		movementDistance -= movementFast;
		break;
	}

}

void Block::allowMovement(){
	isBallMoving = true;
}

void Block::blockMovement(){
	isBallMoving = false;
	
}