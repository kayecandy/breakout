#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Globals.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);


private:
	// Variables
	float instructionsFadeSpeed = 0.3;
	bool isFaded = false;

	// Objects
	cocos2d::Scene* scene;
	cocos2d::Sprite* instructionsSprite;
	class Ball* ball;
	class FluffGenerator* fluffGenerator;

	// Initializer
	void initPhysics();

	// Update
	void update(float) override;

};

#endif // __HELLOWORLD_SCENE_H__
