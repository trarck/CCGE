#include "MainScene.h"
#include "Controllers/MainController.h"
#include "Controllers/HeaderController.h"
#include "Controllers/FooterController.h"

using namespace cocos2d;

NS_CC_GE_BEGIN

// on "init" you need to initialize your instance
void MainScene::loadContents()
{
    BaseScene::loadContents();
    
    
    CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
    
    float headerHeight=160.0f,footerHeight=200.0f;
    
//    float bodyHeight=screenSize.height-headerHeight-footerHeight;
    
	MainController* mainController=new MainController();
	mainController->init();
	this->addChild(mainController->getView());
    addController(mainController);
    mainController->release();
    
    mainController->getView()->setPosition(ccp(0.0f, footerHeight));
    
    HeaderController* headerController=new HeaderController();
	headerController->init();
	this->addChild(headerController->getView());
    addController(headerController);
    headerController->release();

    headerController->getView()->setPosition(ccp(0.0f, screenSize.height-headerHeight));
    
    
    FooterController* footerController=new FooterController();
	footerController->init();
	this->addChild(footerController->getView());
    addController(footerController);
    footerController->release();
}

NS_CC_GE_END