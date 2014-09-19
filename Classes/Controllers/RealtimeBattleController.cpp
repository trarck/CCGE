#include "RealtimeBattleController.h"
#include <yhgui/yhgui.h>
#include <yhge/yhge.h>
#include "Game.h"
#include "Consts/PropertyDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/Components/BattlePositionComponent.h"
#include "EntityComponent/Components/Battles/PopupComponent.h"
#include "Services/ServiceFactory.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Layers/DimetricCoordinateLayer.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

//static const float kGameTileWidth=120;
//static const float kGameTileHeight=60;

//static const float kGameTileWidth=120;
//static const float kGameTileHeight=48;

static const float kTimelineWidth=400;
static const float kTimelineHeight=40;

RealtimeBattleController::RealtimeBattleController(void)
:m_mapId(0)
,m_zoneId(0)
,m_round(0)
,m_stepSide(0)
,m_selfStepIndex(0)
,m_oppStepIndex(0)
,m_battleEnd(false)
,m_win(false)
,m_battleWorld(NULL)
,m_timelineNodes(NULL)
,m_timelineLayer(NULL)
,m_battleManager(NULL)
,m_tipLayer(NULL)
{
    m_sName="RealtimeBattleController";
}

RealtimeBattleController::~RealtimeBattleController(void)
{
    CCLOG("RealtimeBattleController destroy");

    CC_SAFE_RELEASE_NULL(m_battleWorld);
    
    CC_SAFE_RELEASE_NULL(m_timelineNodes);
    
    CC_SAFE_RELEASE_NULL(m_tipLayer);
}

bool RealtimeBattleController::init()
{
    if (BaseController::init()) {
        
        return true;
    }
    
    return false;
}

void RealtimeBattleController::viewDidLoad()
{
    loadBattleGround();
    
    m_battleManager=Game::getInstance()->getEngine()->getBattleManager();
    
    
    //create battle layer
    loadBattleWorld();
    
    loadEntities();
    
//    showCoordinate();
    
    //create test button
    
    CCMenuItemLabel *btn1=CCMenuItemLabel::create(CCLabelTTF::create("skill1", "Arial", 34),
                                                   this,
                                                   menu_selector(RealtimeBattleController::onSkill1));
    
    CCMenuItemLabel *btn2=CCMenuItemLabel::create(CCLabelTTF::create("skill2", "Arial", 34),
                                                     this,
                                                     menu_selector(RealtimeBattleController::onSkill2));

    CCMenu* menu=CCMenu::create(btn1,btn2,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
    
}

void RealtimeBattleController::onViewEnter()
{
    Controller::onViewEnter();
}

void RealtimeBattleController::onViewExit()
{
    CCLOG("RealtimeBattleController::onViewExit %d",this->retainCount());
    
    unloadEntities();
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Controller::onViewExit();
}

void RealtimeBattleController::loadBattleGround()
{
    CCSize contentSize=getPreferredContentSize();
    //TODO load by zoneId
    CCSprite* bg=CCSprite::create("battle/fight_stage_bg_1.png");
    
    bg->setAnchorPoint(ccp(0.5,0.5));
    
    CCSize bgSize=bg->getContentSize();
    
    bg->setPosition(ccp(contentSize.width/2,contentSize.height/2));
    
//    float scaleX=contentSize.width/bgSize.width,scaleY=contentSize.height/bgSize.height;
    
//    bg->setScaleX(scaleX);
//    bg->setScaleY(scaleY);
    
    m_view->addChild(bg);
}

void RealtimeBattleController::loadBattleWorld()
{
    CCSize contentSize=getPreferredContentSize();
    
    m_battleWorld=new CCLayer();
    m_battleWorld->init();
    m_battleWorld->setPosition(ccp(0,100));
    m_view->addChild(m_battleWorld);
    
    m_tipLayer=new CCLayer();
    m_tipLayer->CCNode::init();
    m_tipLayer->setPosition(ccp(0,100));
    m_view->addChild(m_tipLayer);
    
//    m_timelineLayer=CCLayerColor::create(ccc4(128, 128, 128, 200), kTimelineWidth, kTimelineHeight);
//    m_timelineLayer->setPosition(ccp((contentSize.width-kTimelineWidth)/2,30));
//    m_view->addChild(m_timelineLayer);
    
    Json::Value stageInfo;
    HeroVector heroList;
    
    //add test data
    Json::Value hero;
    
    hero["id"]=1;
    hero["camp"]=kCampPlayer;
    heroList.push_back(hero);
    
    hero["id"]=2;
    hero["camp"]=kCampPlayer;
    heroList.push_back(hero);
    
    hero["id"]=3;
    hero["camp"]=kCampPlayer;
    heroList.push_back(hero);
//
//    hero["id"]=1;
//    hero["position_x"]=-240;
//    hero["position_y"]=-40;
//    hero["camp"]=kCampPlayer;
//    heroList.push_back(hero);
//    
//    hero["id"]=1;
//    hero["position_x"]=-320;
//    hero["position_y"]=40;
//    hero["camp"]=kCampPlayer;
//    heroList.push_back(hero);
    
    HeroVector enemyList;
    Json::Value enemy;
    
    enemy["id"]=6;
    enemy["camp"]=kCampEnemy;
    enemyList.push_back(enemy);
    
    enemy["id"]=5;
    enemy["camp"]=kCampEnemy;
    enemyList.push_back(enemy);
//
//    enemy["id"]=4;
//    enemy["camp"]=kCampEnemy;
//    enemyList.push_back(enemy);
    
//    m_battleManager->enterStage(stageInfo, heroList, true);
    m_battleManager->enterArena(heroList, enemyList, false, false);
    
    
    
}

void RealtimeBattleController::showCoordinate()
{
    //show coordinate line
    DimetricCoordinateLayer* coordLayer=new DimetricCoordinateLayer();
    coordLayer->setMapWidth(20);
    coordLayer->setMapHeight(20);
    coordLayer->setAnchorPoint(ccp(0,0));
    coordLayer->setPosition(ccp(0,100));
    
    m_view->addChild(coordLayer);
    
    coordLayer->release();
}

void RealtimeBattleController::loadEntities()
{
    //把entity加入显示列表
    
    std::map<int, GameEntityVector > aliveUnits=m_battleManager->getAliveUnits();
        
    GameEntity* entity=NULL;
    
    for (std::map<int, GameEntityVector >::iterator campIter=aliveUnits.begin(); campIter!=aliveUnits.end(); ++campIter) {
        for (GameEntityVector::iterator iter=campIter->second.begin(); iter!=campIter->second.end(); ++iter) {
            
            entity=*iter;
                        
            RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
            m_battleWorld->addChild(rendererComponent->getRenderer());
            
            PopupComponent* popupComponent=static_cast<PopupComponent*>(entity->getComponent("PopupComponent"));
            if (popupComponent) {
                popupComponent->setContainer(m_tipLayer);
            }
        }
    }    
}

void RealtimeBattleController::unloadEntities()
{
    std::map<int, GameEntityVector > aliveUnits=m_battleManager->getAliveUnits();
    
    GameEntity* entity=NULL;
    
    for (std::map<int, GameEntityVector >::iterator campIter=aliveUnits.begin(); campIter!=aliveUnits.end(); ++campIter) {
        for (GameEntityVector::iterator iter=campIter->second.begin(); iter!=campIter->second.end(); ++iter) {
            
            entity=*iter;
            
            entity->cleanup();
            
        }
    }
    
    m_battleWorld->removeAllChildrenWithCleanup(true);
    
}

/**
 * @brief 战斗结束操作
 */
void RealtimeBattleController::doBattleEnd(bool win)
{
    m_battleEnd=true;
    m_win=win;
    
    CCLOG("BattleEnd:win %d",win);
    
    CCLabelTTF* tempLabel=NULL;
    
    if(win){
        tempLabel=CCLabelTTF::create("胜利", "Arial", 64);
        tempLabel->setColor(ccc3(200, 0, 0));
    }else{
        tempLabel=CCLabelTTF::create("失败", "Arial", 64);
        tempLabel->setColor(ccc3(200, 200, 0));
    }
    
    CCSize contentSize=CCDirector::sharedDirector()->getWinSize();
    
    tempLabel->setPosition(ccp(contentSize.width/2,contentSize.height/2-100));
    m_view->addChild(tempLabel);
    
    CCAction* action=CCSequence::create(
                                        CCMoveBy::create(1.0, ccp(0,200)),
                                        CCRemoveSelf::create(),
//                                        CCDelayTime::create(0.5),
                                        CCCallFunc::create(this, callfunc_selector(RealtimeBattleController::onEndTipCallback)),
                                        NULL);
    
    tempLabel->runAction(action);
}

void RealtimeBattleController::onEndTipCallback()
{
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

void RealtimeBattleController::onSkill1(CCObject* sender)
{
    //get first alive entity
    GameEntity* caster=m_battleManager->getUnits().front();
    
    if (static_cast<UnitProperty*>(caster->getProperty(CCGE_PROPERTY_UNIT))->isAlive()) {
        GameEntityVector enemyList=m_battleManager->getAliveUnitsOfCamp(kCampEnemy);
        GameEntity* target=enemyList.front();
        
        //TODO get skill by id
        SkillManager::SkillList::iterator begin= Game::getInstance()->getEngine()->getSkillManager()->getEntitySkills(caster->m_uID).begin();
        SkillComponent* aSkill=*(begin+1);
        if(aSkill){
            aSkill->cast(target);
        }
    }
    

}

void RealtimeBattleController::onSkill2(CCObject* sender)
{
    GameEntity* caster=m_battleManager->getUnits().at(1);
    if (static_cast<UnitProperty*>(caster->getProperty(CCGE_PROPERTY_UNIT))->isAlive()) {
        GameEntityVector enemyList=m_battleManager->getAliveUnitsOfCamp(kCampEnemy);
        GameEntity* target=enemyList.front();
        
        //TODO get skill by id
        SkillManager::SkillList::iterator begin= Game::getInstance()->getEngine()->getSkillManager()->getEntitySkills(caster->m_uID).begin();
        
        SkillComponent* aSkill=*(begin+1);
        if(aSkill){
            aSkill->cast(target);
        }
    }
}

NS_CC_GE_END