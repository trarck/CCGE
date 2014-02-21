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
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

BaseScene::BaseScene()
:m_document(NULL)
{
    
}

BaseScene::~BaseScene()
{
//    CC_SAFE_RELEASE_NULL(m_document);
}

bool BaseScene::init()
{
    if (Scene::init()) {
        m_document=new Component();
        
        addChild(m_document);
        
//        m_document->release();
        
        return true;
    }
    
    return false;
}

void BaseScene::onEnter()
{
    yhmvc::Scene::onEnter();
    Game::getInstance()->getInteractiveOrganizer()->setDocument(m_document);
}

void BaseScene::onExit()
{
    Game::getInstance()->getInteractiveOrganizer()->setDocument(NULL);
    yhmvc::Scene::onExit();
}

NS_CC_GE_END