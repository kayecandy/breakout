#ifndef __FLUFF_GENERATOR_H__
#define __FLUFF_GENERATOR_H__

#include "Globals.h"
#include <thread>



class FluffGenerator : public cocos2d::Node{

public:
	static FluffGenerator* create(cocos2d::Layer*);
	virtual bool init();

	FluffGenerator(cocos2d::Layer*);

	cocos2d::Layer* scene;

	bool isContinous = true;


	void generateFluff();
	void generateInitialFluff();
	void stopContinousGeneration();
	void startContinousGeneration();

private:
	//Variables
	bool hasContinousGenerationStarted = false;
	int initialFluffCount = 10;

	float minDistanceFromCenter = 150;
	float maxDistanceFromCenter = 200;
	float timeInterval = 5;

	// Generation
	void generateContinousFluff();


};




#endif //__FLUFF_GENERATOR_H__