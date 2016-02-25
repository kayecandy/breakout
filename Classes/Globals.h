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

USING_NS_CC;

namespace{

	enum Indices{
		INDEX_BACKGROUND = 0,

		INDEX_PLANET = 1,
		INDEX_PLANET_GLOW = 2,

		INDEX_BLOCK = 3

	};

	char* SPRITE_SOURCE[] = {
		"Background2.png",

		"Planet.png",
		"PlanetGlow.png",

		"Block.png"

	};

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

}


#endif // __GLOBALS_H__