#include "MissionController.h"
#include <yhge/isometric.h>
#include "Game.h"
#include "Consts/DataDefine.h"
#include "SceneDirector/GameSceneDirector.h"


USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

MissionController::MissionController(void)
:m_gameWorld(NULL)
{
    
}


MissionController::~MissionController(void)
{
    CCLOG("MissionController destroy");
    CC_SAFE_RELEASE_NULL(m_gameWorld);
}

void MissionController::viewDidLoad()
{
    CCSize visibleSize =  this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    m_gameWorld=new StepGameWorldController();
    m_gameWorld->init(1000, 1);
    m_gameWorld->setPreferredContentSize(visibleSize);
    
    m_view->addChild(m_gameWorld->getView());
    
    //create test button
    CCMenuItemLabel *stepBtn=CCMenuItemLabel::create(CCLabelTTF::create("step", "Arial", 20),
                                                     this,
                                                     menu_selector(MissionController::onStepEvent));
    
    CCMenu* menu=CCMenu::create(stepBtn,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
}

void MissionController::onViewExit()
{
    Controller::onViewExit();
}

void MissionController::doStepEvent()
{
    CCDictionary* dict=new CCDictionary();
    dict->setObject(CCInteger::create(1), CCGE_DATA_BATTLE_TYPE);
    dict->setObject(CCInteger::create(1), CCGE_DATA_BATTLE_OPPID);
    
    GameSceneDirector::getInstance()->setSceneContext(dict);
    
    dict->release();
    
    GameSceneDirector::getInstance()->pushScene(kBattlePrepareScene);
}

void MissionController::onStepEvent(CCObject* sender)
{
    doStepEvent();
}

NS_CC_GE_END