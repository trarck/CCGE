#include "InitializeScene.h"
#include "Controllers/InitializeController.h"

using namespace cocos2d;

NS_CC_GE_BEGIN

// on "init" you need to initialize your instance
void InitializeScene::loadContents()
{
    BaseScene::loadContents();
        
	InitializeController* initializeController=new InitializeController();
	initializeController->init();
	m_document->addChild(initializeController->getView());
    addController(initializeController);
    initializeController->release();
}

NS_CC_GE_END