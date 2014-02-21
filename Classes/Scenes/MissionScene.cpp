#include "MissionScene.h"
#include "Controllers/ThreeSegmentController.h"
#include "Controllers/MissionController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN
// on "init" you need to initialize your instance
void MissionScene::loadContents()
{
	ThreeSegmentScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=static_cast<ThreeSegmentController*>(getControllerByName("ThreeSegmentController"));

	MissionController* missionController=new MissionController();
	missionController->init();
    missionController->setPreferredContentSize(threeSegmentController->getBodyLayer()->getContentSize());

	threeSegmentController->getBodyLayer()->addChild(missionController->getView());
    addController(missionController);
    missionController->release();
}

NS_CC_GE_END