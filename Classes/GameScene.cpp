#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->scene = scene;

	layer->initPhysics();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto background = cocos2d::Sprite::create(SPRITE_SOURCE[INDEX_BACKGROUND]);
	background->setPosition(POSITION_CENTER_CENTER);

	this->addChild(background, 0);

	//auto playButton = ui::Button::create(Globals::playButtonSource[0], Globals::playButtonSource[1], Globals::playButtonSource[1]);
	//playButton->setPosition(POSITION_CENTER_CENTER);

	//this->addChild(playButton, 1);


	auto planet = Planet::create();
	planet->setPosition(POSITION_CENTER_CENTER);
	this->addChild(planet, 2);


	auto block = Block::create();
	this->addChild(block, 1);


	ball = Ball::create(block);
	this->addChild(ball, 1);

	fluffGenerator = FluffGenerator::create(this);
	this->addChild(fluffGenerator, 1);


	fluffGenerator->generateInitialFluff();

	instructionsSprite = Sprite::create(SPRITE_SOURCE[INDEX_INSTRUCTIONS]);
	instructionsSprite->setPosition(POSITION_CENTER_CENTER);
	this->addChild(instructionsSprite, 5);
	//instructionsSprite->updateDisplayedOpacity(255);

	this->scheduleUpdate();

	return true;
}

void GameScene::initPhysics(){
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

void GameScene::update(float delta){
	//cocos2d::log("opacity: %d", instructionsSprite->getDisplayedOpacity());

	if (ball->isMoving && !isFaded){
		isFaded = true;
		instructionsSprite->runAction(FadeOut::create(instructionsFadeSpeed));
		fluffGenerator->startContinousGeneration();



		for (Node* n : this->getChildren())
		{
			if (dynamic_cast<Fluff*>(n)){
				auto f = dynamic_cast<Fluff*>(n);
				f->enableExpand();
			}
		}

		cocos2d::log("correct1");


	}
	else if (!ball->isMoving && isFaded){
		isFaded = false;
		instructionsSprite->runAction(FadeIn::create(instructionsFadeSpeed));
		fluffGenerator->stopContinousGeneration();

		for (Node* n : this->getChildren())
		{
			if (dynamic_cast<Fluff*>(n)){
				auto f = dynamic_cast<Fluff*>(n);
				f->disableExpand();
			}
		}
	}

}



void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
