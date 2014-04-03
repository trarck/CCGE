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
,m_leftStep(0)
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
    
    MissionService* missionService=ServiceFactory::getInstance()->getMissionService();
    
    m_gameWorld=new StepGameWorldController();
    m_gameWorld->init(missionService->getCurrentZone(), missionService->getCurrentMap());
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
    
    showStepEvent();
    
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

void MissionController::moveStep(int step)
{
    m_leftStep=0;
    
    Game::getInstance()->getMessageManager()->registerReceiver(
                                                               m_gameWorld->getPlayer(), MSG_MOVE_COMPLETE, NULL,
                                                               message_selector(MissionController::onPlayerMoveComplete), this);
    
    // 如果路上有被阻碍的点(比如战斗事件)则要处理阻碍事件再继续。
    int stopStep=checkPathBarrier(step);
    if (stopStep) {
        m_leftStep=step-stopStep;
        step=stopStep;
    }
    
    m_gameWorld->nextStep(step);
    
    ServiceFactory::getInstance()->getMissionService()->setLastMapStepIndex(m_gameWorld->getStepIndex());
}

void MissionController::doMissionFinish()
{
    //步骤完成
    ServiceFactory::getInstance()->getMissionService()->completeCurrentMap();
    Game::getInstance()->getSceneDirector()->popScene();
}

void MissionController::onStepEvent(CCObject* sender)
{
//    if (!m_gameWorld->isEndStep()) {
    
        //还没有到达终点，继续前进。不需要检查，会在移动完成处理
        
        unsigned int step=Game::getInstance()->getRandom()->NextUInt(1,6);
        
        moveStep(step);
        
//    }else{
//        doMissionFinish();
//    }
    
}

void MissionController::onPlayerMoveComplete(yhge::Message* message)
{
    Game::getInstance()->getMessageManager()->removeReceiver(m_gameWorld->getPlayer(), MSG_MOVE_COMPLETE,
                                                               message_selector(MissionController::onPlayerMoveComplete));
    doStepEvent();
    
    //检查是否被断下来
    if (m_leftStep) {
        //继续移动
        moveStep(m_leftStep);
    }
    
    //检查是否移动完成
    if (m_gameWorld->isEndStep()) {
        doMissionFinish();
    }
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

/**
 * @brief 显示步骤事件
 */
void MissionController::showStepEvent()
{
    CCArray* paths=m_gameWorld->getWalkPaths();
    CCObject* pObj=NULL;
    CCPointValue* posValue=NULL;
    
    CCInteger* typeValue=NULL;
    
    CCString* iconPath=NULL;
    
    CCARRAY_FOREACH(paths, pObj){
        posValue=static_cast<CCPointValue*>(pObj);
        
        CCPoint coord=posValue->getPoint();
        
        typeValue=static_cast<CCInteger*>(m_stepEvents->objectForKey(positionToStepKey(coord)));
        
        if (typeValue) {
            switch (typeValue->getValue()) {
                case kBattleEvent:
                case kGetMoneyEvent:
                case kGetExpEvent:
                case kGetItemEvent:
                case kPvpEvent:
                    iconPath=CCString::createWithFormat("event_icon/%d.png",typeValue->getValue());
                    break;
                default:
                    iconPath=NULL;
                    break;
            }
            
            if (iconPath) {
                
                CCSprite* iconSprite=CCSprite::create(iconPath->getCString());
                
                //fixed to cell center
                coord.x+=0.5f;
                coord.y+=0.5f;
                
                CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord));

                iconSprite->setPosition(viewPos);
                
                m_gameWorld->getStepEventLayer()->addChild(iconSprite);
                
            }
            
        }else{
            CCLOG("no %f,%f",posValue->getPoint().x,posValue->getPoint().y);
        }
    }
    
}

int MissionController::checkPathBarrier(int step)
{
    CCArray* paths=m_gameWorld->getWalkPaths();
    
    CCPointValue* posValue=NULL;
    
    CCInteger* typeValue=NULL;
    
    int startIndex=m_gameWorld->getStepIndex();
    
    if (startIndex<paths->count()) {
        
        for (int i=0 ; i<step; ++i) {
            
            posValue=static_cast<CCPointValue*>(paths->objectAtIndex(startIndex+i));
            
            CCPoint coord=posValue->getPoint();
            
            typeValue=static_cast<CCInteger*>(m_stepEvents->objectForKey(positionToStepKey(coord)));
            
            if (typeValue) {
                switch (typeValue->getValue()) {
                        
                    //在战斗事件上停下来
                    case kBattleEvent:
                    case kPvpEvent:
                        //must stop
                        return i+1;
                        break;
                    default:
                        break;
                }
            }else{
                CCLOG("no %f,%f",posValue->getPoint().x,posValue->getPoint().y);
            }
            
        }
    }
    
    return 0;
}

NS_CC_GE_END