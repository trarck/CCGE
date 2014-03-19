#include "MissionController.h"
#include <yhge/isometric.h>
#include "Game.h"
#include "Consts/DataDefine.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Services/ServiceFactory.h"


USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

enum StepEventType
{
    kNopEvent=0,//没有事件
    kBattleEvent,
    kGetMoneyEvent,
    kGetExpEvent,
    kGetItemEvent,
    kPvpEvent,
    
    kStartEvent,//开始结点
    kEndEvent//结束结点
};

MissionController::MissionController(void)
:m_gameWorld(NULL)
,m_stepEvents(NULL)
{
    
}


MissionController::~MissionController(void)
{
    CCLOG("MissionController destroy");
    CC_SAFE_RELEASE_NULL(m_gameWorld);
    CC_SAFE_RELEASE_NULL(m_stepEvents);
}

void MissionController::viewDidLoad()
{
    CCSize visibleSize =  this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    m_gameWorld=new StepGameWorldController();
    m_gameWorld->init(1000, 1);
    m_gameWorld->setTouchable(false);
    m_gameWorld->setPreferredContentSize(visibleSize);
    m_gameWorld->setStepIndex(ServiceFactory::getInstance()->getMissionService()->getLastMapStepIndex());
    
    m_view->addChild(m_gameWorld->getView());
    
    //create test button
    CCMenuItemLabel *stepBtn=CCMenuItemLabel::create(CCLabelTTF::create("step", "Arial", 40),
                                                     this,
                                                     menu_selector(MissionController::onStepEvent));
    
    CCMenu* menu=CCMenu::create(stepBtn,NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(visibleSize.width-60,40));
    
    m_view->addChild(menu);
    
    
    
    //for test
    generateStepPathEvent();
    
}

void MissionController::onViewExit()
{
    //清理注册过的事件
    Game::getInstance()->getMessageManager()->removeReceiver(m_gameWorld->getPlayer(), MSG_MOVE_COMPLETE,
                                                             message_selector(MissionController::onPlayerMoveComplete));
    
    Controller::onViewExit();
}

void MissionController::doStepEvent()
{
    CCPoint currentPos= m_gameWorld->getCurrentPosition();
    
    int key=positionToStepKey(currentPos);
    
    CCInteger* typeValue=static_cast<CCInteger*>(m_stepEvents->objectForKey(key));
    
    if (typeValue) {
        
        CCLOG("MissionController::doStepEvent type:%d",typeValue->getValue());
        
        switch (typeValue->getValue()) {
            case kBattleEvent:
                doBattleEvent();
                break;
            case kGetMoneyEvent:
                doGetMoneyEvent();
                break;
            case kGetExpEvent:
                doGetExpEvent();
                break;
            case kGetItemEvent:
                doGetItemEvent();
                break;
            case kPvpEvent:
                doPvpEvent();
                break;
            default:
                break;
        }
    }
}

void MissionController::onStepEvent(CCObject* sender)
{
    if (!m_gameWorld->isEndStep()) {
        
        Game::getInstance()->getMessageManager()->registerReceiver(
                                                                   m_gameWorld->getPlayer(), MSG_MOVE_COMPLETE, NULL,
                                                                   message_selector(MissionController::onPlayerMoveComplete), this);
        
        //还没有到达终点，继续前进。
        
        unsigned int step=Game::getInstance()->getRandom()->NextUInt(1,6);
        //TODO 如果路上有被阻碍的点(比如战斗事件)则要处理阻碍事件再继续。
        m_gameWorld->nextStep(step);
        
        ServiceFactory::getInstance()->getMissionService()->setLastMapStepIndex(m_gameWorld->getStepIndex());
        
    }else{
        //步骤完成
        
    }
    
}

void MissionController::onPlayerMoveComplete(yhge::Message* message)
{
    Game::getInstance()->getMessageManager()->removeReceiver(m_gameWorld->getPlayer(), MSG_MOVE_COMPLETE,
                                                               message_selector(MissionController::onPlayerMoveComplete));
    doStepEvent();
}

void MissionController::generateStepPathEvent()
{
    CCArray* paths=m_gameWorld->getWalkPaths();
    m_stepEvents=new CCDictionary();
    
    CCPointValue* posValue=NULL;
    CCPoint pos;
    int key=0;
    
    //start
    posValue= static_cast<CCPointValue*>(paths->objectAtIndex(0));
    pos=posValue->getPoint();
    key=positionToStepKey(pos);
    m_stepEvents->setObject(CCInteger::create(kStartEvent), key);
    
    //end
    posValue= static_cast<CCPointValue*>(paths->objectAtIndex(paths->count()-1));
    pos=posValue->getPoint();
    key=positionToStepKey(pos);
    m_stepEvents->setObject(CCInteger::create(kEndEvent), key);
    
    //其它点，随机生成
    for (int i=1; i<paths->count()-2; ++i) {
        posValue= static_cast<CCPointValue*>(paths->objectAtIndex(i));
        pos=posValue->getPoint();
        key=positionToStepKey(pos);
        m_stepEvents->setObject(CCInteger::create(Game::getInstance()->getRandom()->Next(kStartEvent)), key);
    }
}

void MissionController::doBattleEvent()
{
    CCDictionary* dict=new CCDictionary();
    dict->setObject(CCInteger::create(1), CCGE_DATA_BATTLE_TYPE);
    dict->setObject(CCInteger::create(1), CCGE_DATA_BATTLE_OPPID);
    
    GameSceneDirector::getInstance()->setSceneContext(dict);
    
    dict->release();
    
    GameSceneDirector::getInstance()->pushScene(kBattlePrepareScene);
}

void MissionController::doGetMoneyEvent()
{
    CCLOG("get 100 gold");
}

void MissionController::doGetExpEvent()
{
    CCLOG("get 23 exp");
}

void MissionController::doGetItemEvent()
{
    CCLOG("get one weap");
}

void MissionController::doPvpEvent()
{
    CCLOG("battle with other");
}

int MissionController::positionToStepKey(const CCPoint& pos)
{
    return m_gameWorld->getMapColumn() * (int)pos.y+(int)pos.x;
}

NS_CC_GE_END