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
	this->addChild(planet, 1);


	auto block = Block::create();
	this->addChild(block, 1);

	
	
	auto test = PhysicsJointRotarySpring::construct(
		planet->getPhysicsBody(),
		block->getPhysicsBody(), 0.5, 0.2);

	test->createConstraints();

	PhysicsJointRotaryLimit::construct(
		planet->getPhysicsBody(),
		block->getPhysicsBody(),
		10 * 180 / M_PI,
		90 * 180 / M_PI);




	return true;
}

void GameScene::initPhysics(){
	//scene->getPhysicsWorld()->setGravity(Vec2(0,0));
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
