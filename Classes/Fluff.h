#ifndef __FLUFF_H__
#define __FLUFF_H__

#include "Globals.h"

class Fluff : public cocos2d::Node{
public:
	static class Fluff* create();
	virtual bool init();

	void enableExpand();
	void disableExpand();

private:
	enum Direction{
		Vertical=0, Horizontal=1, Null=-1
	};
	//Variables
	float movementSpeed = 25;

	float isExpandEnabled = false;
	float expandIndexMin = 0.0005;
	float expandIndexMax = 0.00009;
	float expandMax = 1.55;
	
	
	float movementExpandIndexMin = 0.0025;
	float movementExpandIndexMax = 0.01;
	Direction movementExpandDirection = Null;
	float movementExpandMax = 0.80;

	//Sprites
	cocos2d::Sprite* fluffSprite;
	cocos2d::Sprite* fluffEyesSprite;

	// Initializers
	void initializeSprite();
	void initializePhysics();
	void initializeEvent();

	// Movements
	bool isMovementReverse = false;
	void setExpand();
	void setMovementExpand();

	//Update
	void update(float) override;

	//Physics
	cocos2d::PhysicsBody* physicsBody;
	float density = 0.5;
	float friction = 0.0;
	float restitution = 0.05;
	float linearDamping = 0.75;

	void setVelocity();

};

#endif //__FLUFF_H__