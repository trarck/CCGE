#include "TestSqliteScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/TestSqliteController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void TestSqliteScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getControllerByName("ThreeSegmentController"));

	TestSqliteController* testSqliteController=new TestSqliteController();
	testSqliteController->init();
    testSqliteController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(testSqliteController->getView());
    addController(testSqliteController);
    testSqliteController->release();
}

NS_CC_GE_END