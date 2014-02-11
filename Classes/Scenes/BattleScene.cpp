#include "BattleScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/BattleController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void BattleScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getLayerControllerByName("ThreeSegmentController"));

	BattleController* battleController=new BattleController();
	battleController->init();
    battleController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(battleController->getLayer());
    addLayerController(battleController);
    battleController->release();
}

NS_CC_GE_END