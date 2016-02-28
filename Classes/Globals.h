#pragma once
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define COCOS2D_DEBUG 1

#define SCREEN_WIDTH GET_VISIBLE_SIZE().width
#define SCREEN_HEIGHT GET_VISIBLE_SIZE().height

#define SCREEN_POSITION_LEFT 0
#define SCREEN_POSITION_RIGHT GET_VISIBLE_SIZE.width
#define SCREEN_POSITION_TOP GET_VISIBLE_SIZE.height
#define SCREEN_POSITION_BOTTOM 0

#define POSITION_CENTER_CENTER GET_POSITION_CENTER_CENTER()

#include "cocos2d.h"
#include "Planet.h"
#include "GameScene.h"
#include "Block.h"
#include "Fluff.h"
#include "FluffGenerator.h"
#include "Ball.h"

USING_NS_CC;

namespace{

	enum Indices{
		INDEX_BACKGROUND = 0,

		INDEX_PLANET = 1,
		INDEX_PLANET_GLOW = 2,

		INDEX_BLOCK = 3,

		INDEX_FLUFF = 4,
		INDEX_FLUFF_EYES = 5,

		INDEX_BALL = 6,

		INDEX_INSTRUCTIONS

	};

	char* NAME_BALL = "Ball";
	char* NAME_FLUFF = "Fluff";
	char* NAME_BLOCK = "Block";

	char* SPRITE_SOURCE[] = {
		"Background2.png",

		"Planet.png",
		"PlanetGlow.png",

		"Block.png",

		"Fluff.png",
		"FluffEyes.png",

		"Ball.png",

		"Instructions.png"

	};

	int CONTACT_GROUP_FLUFF = 1;

	Size GET_VISIBLE_SIZE(){
		return cocos2d::Director::getInstance()->getVisibleSize();
	}

	Vec2 GET_ORIGIN(){
		return cocos2d::Director::getInstance()->getVisibleOrigin();
	}

	Vec2 GET_POSITION_CENTER_CENTER(){
		Size visibleSize = GET_VISIBLE_SIZE();
		Vec2 origin = GET_ORIGIN();

		return Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	}

	double sind(double angle){
		return sin(angle* M_PI / 180.0f);
	}

	double cosd(double angle){
		return cos(angle*M_PI / 180.0f);
	}

	double asind(double angle){
		return asin(angle*M_PI / 180.0f);
	}
	double acosd(double angle){
		return acos(angle*M_PI / 180.0f);
	}
	double atand(double angle){
		return atan(angle) * 180 / M_PI;
	}

	float GET_DISTANCE_FROM_CENTER(float x, float y){
		float dX = SCREEN_WIDTH / 2 - x;
		float dY = SCREEN_HEIGHT / 2 - y;

		return sqrt(dX*dX + dY*dY);
	}

	float GET_DISTANCE_FROM_CENTER_X(float x){
		return x - SCREEN_WIDTH / 2;
	}
	float GET_DISTANCE_FROM_CENTER_Y(float y){
		return y - SCREEN_HEIGHT / 2;
	}

	bool IS_INSIDE_SCREEN(cocos2d::Vec2 position){
		if (position.x <= 0 || position.x >= SCREEN_WIDTH)
			return false;

		if (position.y <= 0 || position.y >= SCREEN_HEIGHT)
			return false;

		return true;
	}

	bool TEST_CONTACT(cocos2d::PhysicsContact& contact, char* nameA, char*nameB){
		auto bodyA = contact.getShapeA()->getBody();
		auto bodyB = contact.getShapeB()->getBody();

		if ((bodyA->getNode()->getName() == nameA
			|| bodyB->getNode()->getName() == nameB)
			&&
			(bodyA->getNode()->getName() == nameA
			|| bodyB->getNode()->getName() == nameB)){
			return true;
		}

		return false;
	}

	cocos2d::Node* GET_BODY_FROM_CONTACT(cocos2d::PhysicsContact& contact, char* name){
		auto bodyA = contact.getShapeA()->getBody()->getNode();
		auto bodyB = contact.getShapeB()->getBody()->getNode();

		if (bodyA->getName() == name)
			return bodyA;
		else if (bodyB->getName() == name)
			return bodyB;
	
		return NULL;
	}

}




#endif // __GLOBALS_H__