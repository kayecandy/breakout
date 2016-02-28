#ifndef __BALL_H__
#define __BALL_H__

#include "Globals.h"

class Ball : public cocos2d::Node{
public:
	static class Ball* create(class Block* block);
	virtual bool init();

	int isMoving = false;

private:
	// Variables
	int speed = 350;
	float hitSpeedIncreaseRate = 1.5;

	// Parent
	class Block* block;

	// Initializer
	void initializeSprite();
	void initializePosition();
	void initializePhysics();
	void initializeEvent();

	// Sprite
	cocos2d::Sprite* ballSprite;

	// Physics 
	cocos2d::PhysicsBody* physicsBody;
	float density = 0.1;
	float friction = 0.3;
	float restitution = 1;

	// Update
	void update(float) override;

	// Listener
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* e);
	void onContactSeparate(cocos2d::PhysicsContact&);

};

#endif //__BALL_H__
