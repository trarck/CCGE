#include "TestMsgScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/TestMsgController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void TestMsgScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getControllerByName("ThreeSegmentController"));

	TestMsgController* testMsgController=new TestMsgController();
	testMsgController->init();
    testMsgController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(testMsgController->getView());
    addController(testMsgController);
    testMsgController->release();
}

NS_CC_GE_END