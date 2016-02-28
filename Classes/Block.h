#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Globals.h"

USING_NS_CC;

class Block : public cocos2d::Node{
public:
	static class Block* create();
	virtual bool init();

	void allowMovement();
	void blockMovement();


private:
	// Variables
	bool isBallMoving = false;
	float movementSpeed = .005;
	float movementFast = 3;
	float movementNormal = 3;
	float movementDistance = movementNormal;

	int distanceFromCenter = 350;
	float positionAngle = 0;

	// Sprite
	cocos2d::Sprite* blockSprite;

	// Initializers
	void initializeNode();
	void initializeEvents();

	// Setter
	void setRelativePosition(float angle);

	// Events
	bool isKeyPressed = false;;
	void onKeyboardPressed(EventKeyboard::KeyCode, Event*);
	void onKeyboardReleased(EventKeyboard::KeyCode, Event*);
	void whileKeyboardPressed(EventKeyboard::KeyCode, Event*);

	//Physics
	cocos2d::PhysicsBody* physicsBody;
	float density = 100000;
	float friction = 0.5;
	float restitution = 1.0;

};


#endif //__BLOCK_H__