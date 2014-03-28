#include "SimpleScene.h"
#include "Game.h"
#include "Controllers/BaseController.h"

using namespace cocos2d;

NS_CC_GE_BEGIN

// on "init" you need to initialize your instance
void SimpleScene::loadContents()
{
    BaseScene::loadContents();
    
    BaseController* controller= static_cast<BaseController*>(Game::getInstance()->getSceneDirector()->getSceneContext());
    if (controller) {
        m_document->addChild(controller->getView());
        addController(controller);
    }
}

NS_CC_GE_END