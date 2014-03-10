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
,m_internalOrgnaizer(NULL)
{
    
}

BaseScene::~BaseScene()
{
    //    CC_SAFE_RELEASE_NULL(m_document);
    CC_SAFE_RELEASE_NULL(m_internalOrgnaizer);
}

bool BaseScene::init()
{
    if(yhmvc::Scene::init()){
        
        createDocument();
        return true;
    }
    
    return false;
}

void BaseScene::createDocument()
{
    m_internalOrgnaizer=new yhgui::NormalDocumentTreeOrganizer();
    m_internalOrgnaizer->init();
    m_internalOrgnaizer->registerWithTouchDispatcher();
    
    m_document=new yhgui::Component();
    
    addChild(m_document);
    
    m_internalOrgnaizer->setDocument(m_document);
    
    m_document->release();
}

//void BaseScene::loadContents()
//{
//    yhmvc::Scene::loadContents();
//    //    createDocument();
//    
//}
NS_CC_GE_END