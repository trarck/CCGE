#include "ThreeSegmentScene.h"
#include "Controllers/HeaderController.h"
#include "Controllers/FooterController.h"
#include "Controllers/ThreeSegmentController.h"

using namespace cocos2d;

NS_CC_GE_BEGIN

void ThreeSegmentScene::loadContents()
{
    BaseScene::loadContents();
    
    ThreeSegmentController* threeSegmentController=new ThreeSegmentController();
    threeSegmentController->init("ThreeSegmentController");
    addController(threeSegmentController);
    threeSegmentController->release();
    addChild(threeSegmentController->getView());
    
    HeaderController* headerController=new HeaderController();
	headerController->init();
    headerController->setPreferredContentSize(threeSegmentController->getHeaderLayer()->getContentSize());
	threeSegmentController->getHeaderLayer()->addChild(headerController->getView());
    addController(headerController);
    headerController->release();
    
    FooterController* footerController=new FooterController();
	footerController->init();
    footerController->setPreferredContentSize(threeSegmentController->getFooterLayer()->getContentSize());
	threeSegmentController->getFooterLayer()->addChild(footerController->getView());
    addController(footerController);
    footerController->release();
}

NS_CC_GE_END