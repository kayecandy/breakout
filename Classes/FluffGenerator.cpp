#include "FluffGenerator.h"


FluffGenerator* FluffGenerator::create(Layer* scene){
	FluffGenerator* f = new (std::nothrow)FluffGenerator(scene);

	if (f && f->init())
	{
		f->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(f);
	}
	return f;
}

FluffGenerator::FluffGenerator(cocos2d::Layer* scene){
	this->scene = scene;
}

bool FluffGenerator::init(){
	if (!Node::init()){
		return false;
	}

	return true;
}



void FluffGenerator::generateFluff(){
	if (isContinous){
		auto fluff = Fluff::create();

		float distance = cocos2d::random(minDistanceFromCenter, maxDistanceFromCenter);
		float angle = cocos2d::random(0, 360);

		fluff->setPositionX(SCREEN_WIDTH / 2 + sind(angle) * distance);
		fluff->setPositionY(SCREEN_HEIGHT / 2 + cosd(angle) * distance);

		scene->addChild(fluff, 1);
	}
	
}

void FluffGenerator::generateInitialFluff(){
	for (int i = 0; i < initialFluffCount; i++){
		generateFluff();
	}
}

void FluffGenerator::generateContinousFluff(){
	auto action = Sequence::create(
		DelayTime::create(timeInterval),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(FluffGenerator::generateFluff)),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(FluffGenerator::generateContinousFluff)),
		NULL
	);

	this->runAction(action);
	
	
}

void FluffGenerator::stopContinousGeneration(){
	isContinous = false;
}
void FluffGenerator::startContinousGeneration(){
	isContinous = true;

	if (!hasContinousGenerationStarted){
		hasContinousGenerationStarted = true;
		generateContinousFluff();
	}
}