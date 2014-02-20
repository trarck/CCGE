//
//  BaseScene.cpp
//  CCGE
//
//  Created by duanhouhai on 13-8-6.
//
//

#include "BaseScene.h"
#include <yhgui/yhgui.h>
#include "Game.h"

USING_NS_CC;
USING_NS_CC_YHGUI;

NS_CC_GE_BEGIN

void BaseScene::onEnter()
{
    yhmvc::Scene::onEnter();
    Game::getInstance()->getInteractiveOrganizer()->setDocument(NULL);
}

void BaseScene::onExit()
{
    Game::getInstance()->getInteractiveOrganizer()->setDocument(NULL);
    yhmvc::Scene::onExit();
}

NS_CC_GE_END