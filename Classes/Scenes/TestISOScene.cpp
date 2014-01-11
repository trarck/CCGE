#include "TestISOScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/TestISOController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void TestISOScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getLayerControllerByName("ThreeSegmentController"));

	TestISOController* testISOController=new TestISOController();
	testISOController->init();
    testISOController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(testISOController->getLayer());
    addLayerController(testISOController);
    testISOController->release();
}

NS_CC_GE_END