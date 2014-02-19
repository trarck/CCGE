#include "BattlePrepareScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/BattlePrepareController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void BattlePrepareScene::loadContents()
{
	BaseScene::loadContents();
    
	BattlePrepareController* battlePrepareController=new BattlePrepareController();
	battlePrepareController->init();
    battlePrepareController->setPreferredContentSize(CCDirector::sharedDirector()->getWinSize());

	addChild(battlePrepareController->getLayer());
    addLayerController(battlePrepareController);
    battlePrepareController->release();
}

NS_CC_GE_END