#include "RealtimeBattleScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/RealtimeBattleController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void RealtimeBattleScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getControllerByName("ThreeSegmentController"));

	RealtimeBattleController* realtimeBattleController=new RealtimeBattleController();
	realtimeBattleController->init();
    realtimeBattleController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(realtimeBattleController->getView());
    addController(realtimeBattleController);
    realtimeBattleController->release();
}

NS_CC_GE_END