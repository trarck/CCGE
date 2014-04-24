#include "RealtimeBattleController.h"
#include <yhgui/yhgui.h>
#include <yhge/yhge.h>
#include "Game.h"
#include "Consts/PropertyDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/EntityFactory.h"
#include "EntityComponent/Components/BattlePositionComponent.h"
#include "Datas/DataFactory.h"
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
{
    m_sName="RealtimeBattleController";
}

RealtimeBattleController::~RealtimeBattleController(void)
{
    CCLOG("RealtimeBattleController destroy");

    CC_SAFE_RELEASE_NULL(m_battleWorld);
    
    CC_SAFE_RELEASE_NULL(m_timelineNodes);
}

bool RealtimeBattleController::init()
{
    if (BaseController::init()) {
        
        m_timelineNodes=new CCArray(18);
        
        initTroops();
        
        return true;
    }
    
    return false;
}

void RealtimeBattleController::viewDidLoad()
{
    loadBattleGround();
    
    //create battle layer
    loadBattleWorld();
    
    loadEntities();
    
    showCoordinate();
    
    //create test button
    
    CCMenuItemLabel *skipBtn=CCMenuItemLabel::create(CCLabelTTF::create("skip", "Arial", 34),
                                                   this,
                                                   menu_selector(RealtimeBattleController::onSkip));
    
    CCMenuItemLabel *startBtn=CCMenuItemLabel::create(CCLabelTTF::create("start", "Arial", 34),
                                                     this,
                                                     menu_selector(RealtimeBattleController::onStart));

    CCMenu* menu=CCMenu::create(skipBtn,startBtn,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
    
}

void RealtimeBattleController::onViewEnter()
{
    Controller::onViewEnter();
    
    createTroopsBattleTimeline();
    
    start();
}

void RealtimeBattleController::onViewExit()
{
    CCLOG("RealtimeBattleController::onViewExit %d",this->retainCount());
    
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
    
    m_timelineLayer=CCLayerColor::create(ccc4(128, 128, 128, 200), kTimelineWidth, kTimelineHeight);
    m_timelineLayer->setPosition(ccp((contentSize.width-kTimelineWidth)/2,30));
    m_view->addChild(m_timelineLayer);
    
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
    //加载自己
    this->loadSelfEntities();
    
    //加载对方
    this->loadOppEntities();
    

}


void RealtimeBattleController::convertIndexToCell(int index,int* col,int* row)
{
    *col=index%kBattleCellCol;
    *row=index/kBattleCellCol;
}

/*
 格子分布
 
      row
 
 col  7   4   1 
 
      8   5   2 
     
      9   6   3
 */

void RealtimeBattleController::convertCoord(int index,int* col,int* row,int* x,int* y)
{
    *col=index%kBattleCellCol;
    *row=index/kBattleCellCol;
    
    //x=kBattleCellCol-row-1
    //y=kBattleCellRow-col-1;
    *x=kBattleCellRow-*row-1;
    *y=kBattleCellCol-*col-1;
}

/*
 格子分布
 
      row
 
 col  1   4   7
 
      2   5   8
 
      3   6   9
 */
void RealtimeBattleController::convertOppCoord(int index,int* col,int* row,int* x,int* y)
{
    *col=index%kBattleCellCol;
    *row=index/kBattleCellCol;
    
    //x=kBattleCellCol-row-1
    //y=kBattleCellRow-col-1;
    *x=*row;
    *y=kBattleCellCol-*col-1;
}

void RealtimeBattleController::loadSelfEntities()
{
    BattleService* battleService=ServiceFactory::getInstance()->getPveBattleService();

    std::vector<int> troops=battleService->getSelfTroops();
    
    int teamSize=troops.size();
    
    int entityId=0;
    
    for (int i=0; i<teamSize; ++i) {
        
        entityId=troops[i];
        
        if (entityId) {
            
            CCLOG("entity id:%d",entityId);
            
            GameEntity* entity=createSelfTroopEntity(entityId,i);
            
//            //取得坐标
//            convertCoord(i, &col, &row, &x, &y);
//            
//            //创建对象
//            GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(entityId);
//            
//            addEntityToSelfTroops(entity, col, row);
//            
//            //临时的。set unit property。应该在EntityFactory创建的时候从配置文件中设置相应值。如果是玩家数据，则要做相应设置
//            UnitProperty* unitProperty=entity->getUnitProperty();
//            unitProperty->setDamage(10);
//            unitProperty->setDefence(10);
//            unitProperty->setHealth(100);
//            unitProperty->setMaxHealth(100);
//            
//            //set battle property
//            BattleProperty* battleProperty=entity->getBattleProperty();
//            battleProperty->setCol(col);
//            battleProperty->setRow(row);
//            battleProperty->setSide(kSelfSide);
//            
//            //set animation
//            CCDictionary* data=new CCDictionary();
//            data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
//            data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
//            MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
//            
//            RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
//            CCNode* renderer=rendererComponent->getRenderer();
//            renderer->setScale(1.5f);
//            renderer->setZOrder(col);
//            
//            //设置坐标
//            
//            //y方向居中对齐，坐标要加0.5
//            CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(x,y+0.5);
//            pos.x+=kBattleSelfOffsetX+x*kBattleCellOffsetX;
//            pos.y+=kBattleSelfOffsetY+y*kBattleCellOffsetY;
//            renderer->setPosition(pos);
//            
//            m_view->addChild(renderer);
//            
//            
//            //血条
//            HealthBarComponent* healthBarComponent=entity->getHealthBarComponent();
//            healthBarComponent->setMaxHp(unitProperty->getMaxHealth());
//            healthBarComponent->setCurrentHp(unitProperty->getHealth());
//            
//            healthBarComponent->getHealthBar()->setPosition(ccp(0,85));
            
            registerEntityMessage(entity);
        }
        
    }
}

void RealtimeBattleController::loadOppEntities()
{

    BattleService* battleService=ServiceFactory::getInstance()->getPveBattleService();
   
    std::vector<int> troops=battleService->getOppTroops();
    
    int teamSize=troops.size();
    
//    int col=0;
//    int row=0;
//    int x=0;
//    int y=0;
    
    int entityId=0;
    
    for (int i=0; i<teamSize; ++i) {
        
        entityId=troops[i];
        
        if (entityId) {
            
            GameEntity* entity=createOppTroopEntity(entityId,i);
            
//            //创建对象
//            GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(entityId);
//            
//            //取得坐标
//            convertOppCoord(i, &col, &row, &x, &y);
//            
//            
//            addEntityToOppTroops(entity, col, row);
//            
//            //临时的。set unit property。应该在EntityFactory创建的时候从配置文件中设置相应值。如果是玩家数据，则要做相应设置
//            UnitProperty* unitProperty=entity->getUnitProperty();
//            unitProperty->setDamage(10);
//            unitProperty->setDefence(10);
//            
//            if (i==1) {
//                unitProperty->setHealth(9);
//            }else{
//                unitProperty->setHealth(30);
//            }
//            unitProperty->setMaxHealth(100);
//            
//            //set battle property
//            BattleProperty* battleProperty=entity->getBattleProperty();
//            battleProperty->setCol(col);
//            battleProperty->setRow(row);
//            battleProperty->setSide(kOppSide);
//            
//            //set animation
//            CCDictionary* data=new CCDictionary();
//            data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
//            data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
//            MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
//            
//            RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
//            CCNode* renderer=rendererComponent->getRenderer();
//            renderer->setScale(1.5f);
//            renderer->setZOrder(col);
//            static_cast<CCSprite*>(renderer)->setFlipX(true);
//            
//            //设置坐标
//            //y方向居中对齐，坐标要加0.5
//            CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(x+kBattleOppOffsetCell,y+0.5);
//            pos.x+=kBattleOppOffsetX+x*kBattleCellOffsetX;
//            pos.y+=kBattleOppOffsetY+y*kBattleCellOffsetY;
//            renderer->setPosition(pos);
//            
//            m_view->addChild(renderer);
//            
//            //血条
//            HealthBarComponent* healthBarComponent=entity->getHealthBarComponent();
//            healthBarComponent->setMaxHp(unitProperty->getMaxHealth());
//            healthBarComponent->setCurrentHp(unitProperty->getHealth());
//            
//            //TODO load from config
//            healthBarComponent->getHealthBar()->setPosition(ccp(15,85));
            
            registerEntityMessage(entity);
        }
    }
}

//初始化战斗双方的队伍
void RealtimeBattleController::initTroops()
{
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            m_selfTroops[j][i]=NULL;
            m_oppTroops[j][i]=NULL;
        }
    }
}

//消除战斗双方的队伍
void RealtimeBattleController::cleanTroops()
{
    GameEntity* entity=NULL;
    
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            
            entity=m_selfTroops[j][i];
            if (entity) {
                removeEntityMessage(entity);
                entity->cleanup();
                entity->release();
            }
            
            entity=m_oppTroops[j][i];
            if (entity) {
                removeEntityMessage(entity);
                entity->cleanup();
                entity->release();
            }
        }
    }
}

//注意entityId和unitId是不同的.
//entityId是enitty的唯一标识.
//unit可能被几个entity使用。
//比如玩家队伍，同一个玩家可以拥有不同的unit,但entityId不同。
//比如怪物，不同关卡，出现的怪物可以是同一个unit，只是等级装备不同
GameEntity* RealtimeBattleController::createSelfTroopEntity(int entityId,int index)
{
    
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    //取得坐标.index转化成9宫格的坐标
    convertCoord(index, &col, &row, &x, &y);
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    
    //创建实体
    GameEntity* entity=EntityFactory::getInstance()->createEntity(entityId);
    
    //设置实体属性
    
    CharacterData* characterData=DataFactory::getInstance()->getCharacterData();
    
    Json::Value characterConfig=characterData->getDataById(entityId);
    
    int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
    float scale=characterConfig[CCGE_PLAYER_SCALE].asDouble();
    int level=characterConfig[CCGE_PLAYER_LEVEL].asInt();
    
    //取得配置
    UnitData* unitData=DataFactory::getInstance()->getUnitData();

    Json::Value unitConfig=unitData->getDataById(unitId);

    
    //设置单位属性
    UnitProperty* unitProperty=unitService->createUnitPropertyFromLevel(level, unitConfig);
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    entity->setUnitProperty(unitProperty);
    
    CCLOG("level:%d,damage:%f",level,unitProperty->getDamage());
    
    //设置战斗属性
    EntityFactory::getInstance()->getEntityPropertyFactory()->addBattleProperty(entity,col,row,kSelfSide,scale);
    
    //添加组件
    EntityFactory::getInstance()->addBattleComponents(entity);
    
    RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
    m_battleWorld->addChild(rendererComponent->getRenderer());
    
    
    addEntityToSelfTroops(entity, col, row);
    
    return entity;
}

GameEntity* RealtimeBattleController::createOppTroopEntity(int entityId,int index)
{
    
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    //取得坐标.index转化成9宫格的坐标
    convertOppCoord(index, &col, &row, &x, &y);
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    
    //创建实体
    GameEntity* entity=EntityFactory::getInstance()->createEntity(entityId);
    
    //设置实体属性
    
    MonsterData* monsterData=DataFactory::getInstance()->getMonsterData();
    
    Json::Value monsterConfig=monsterData->getDataById(entityId);
    
    int unitId=monsterConfig[CCGE_MONSTER_UNIT_ID].asInt();
    float scale=monsterConfig[CCGE_MONSTER_SCALE].asDouble();
    int level=monsterConfig[CCGE_MONSTER_LEVEL].asInt();
    
    //取得配置
    UnitData* unitData=DataFactory::getInstance()->getUnitData();
    
    Json::Value unitConfig=unitData->getDataById(unitId);
    
    //设置单位属性
    UnitProperty* unitProperty=unitService->createUnitPropertyFromLevel(level, unitConfig);
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    entity->setUnitProperty(unitProperty);
    
    CCLOG("opp level:%d,damage:%f",level,unitProperty->getDamage());
    
    //设置战斗属性
    EntityFactory::getInstance()->getEntityPropertyFactory()->addBattleProperty(entity,col,row,kOppSide,scale);
    
    //添加组件
    EntityFactory::getInstance()->addBattleComponents(entity);
    
    RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
    m_battleWorld->addChild(rendererComponent->getRenderer());
    
    addEntityToOppTroops(entity, col, row);
    
    return entity;
}


void RealtimeBattleController::addEntityToSelfTroops(GameEntity* entity,int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    if (m_selfTroops[row][col]) {
        m_selfTroops[row][col]->release();
    }
    m_selfTroops[row][col]=entity;
    CC_SAFE_RETAIN(entity);
}

void RealtimeBattleController::removeEntityFromSelfTroops(GameEntity* entity)
{
    if (!entity) return;
    
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            
            if (m_selfTroops[j][i]==entity) {
                m_selfTroops[j][i]->release();
                m_selfTroops[j][i]=NULL;
            }
        }
    }

}

void RealtimeBattleController::removeEntityFromSelfTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    if (m_selfTroops[row][col]) {
        m_selfTroops[row][col]->release();
        m_selfTroops[row][col]=NULL;
    }
}

GameEntity* RealtimeBattleController::getEntityFromSelfTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    return m_selfTroops[row][col];
}

void RealtimeBattleController::addEntityToOppTroops(GameEntity* entity,int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    if (m_oppTroops[row][col]) {
        m_oppTroops[row][col]->release();
    }
    m_oppTroops[row][col]=entity;
    CC_SAFE_RETAIN(entity);
}

void RealtimeBattleController::removeEntityFromOppTroops(GameEntity* entity)
{
    if (!entity) return;
    
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            
            if (m_oppTroops[j][i]==entity) {
                m_oppTroops[j][i]->release();
                m_oppTroops[j][i]=NULL;
            }
        }
    }
}

void RealtimeBattleController::removeEntityFromOppTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    if (m_oppTroops[row][col]) {
        m_oppTroops[row][col]->release();
        m_oppTroops[row][col]=NULL;
    }
}

GameEntity* RealtimeBattleController::getEntityFromOppTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "RealtimeBattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "RealtimeBattleController::addEntityToSelfTroops row out index");
    
    return m_oppTroops[row][col];
}

GameEntity* RealtimeBattleController::getEntityFromTroops(int col,int row,int side)
{
    switch (side) {
        case kSelfSide:
            return getEntityFromSelfTroops(col, row);
            break;
        case kOppSide:
            return getEntityFromOppTroops(col,row);
            break;
        default:
            return NULL;
            break;
    }
}

/**
 * @brief 添加到队伍
 */
void RealtimeBattleController::addEntityToTroops(GameEntity* entity,int col,int row,int side)
{
    switch (side) {
        case kSelfSide:
            return addEntityToSelfTroops(entity, col, row);
            break;
        case kOppSide:
            return addEntityToOppTroops(entity, col, row);
            break;
        default:
            break;
    }
}

/**
 * @brief 消除对方队伍里的成员
 */
void RealtimeBattleController::removeEntityFromTroops(GameEntity* entity,int side)
{
    switch (side) {
        case kSelfSide:
            return removeEntityFromSelfTroops(entity);
            break;
        case kOppSide:
            return removeEntityFromOppTroops(entity);
            break;
        default:
            break;
    }
}

/**
 * @brief 消除对方队伍里的成员
 */
void RealtimeBattleController::removeEntityFromTroops(int col,int row,int side)
{
    switch (side) {
        case kSelfSide:
            return removeEntityFromSelfTroops(col,row);
            break;
        case kOppSide:
            return removeEntityFromOppTroops(col,row);
            break;
        default:
            break;
    }
}

void RealtimeBattleController::delayStart()
{
    
}

void RealtimeBattleController::onDdelayStartUpdate(float delta)
{
    start();
}

void RealtimeBattleController::start()
{
    m_battleEnd=false;
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
                                                                   schedule_selector(RealtimeBattleController::battleUpdate), this, 0.2f, false);
//    parseRound();
}

void RealtimeBattleController::pause()
{
    
}

void RealtimeBattleController::stop()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(RealtimeBattleController::battleUpdate), this);
}

/**
 * 开始战斗单位的，战斗时间线
 */
void RealtimeBattleController::createTroopsBattleTimeline()
{
    GameEntity* entity=NULL;
    
    int k=0,l=0;
    
    float delay=2.0f;
    
    float sideDelay=2.5f;
    
    //队伍的战斗时间线
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            
            //己方
            entity=m_selfTroops[j][i];
            
            if (entity) {
                createEntityBattleTimeline(entity,-(k++*delay));
            }
            
            //对方
            entity=m_oppTroops[j][i];
            if (entity) {
                createEntityBattleTimeline(entity,-(l++*delay)-sideDelay);
            }
        }
    }
}

/**
 * 开启某个单位的战斗时间线
 */
void RealtimeBattleController::createEntityBattleTimeline(GameEntity* entity,float delay)
{
    UnitProperty* unitProperty=entity->getUnitProperty();
    
    TimelineNode* node=new TimelineNode();
    node->setDuration(1/unitProperty->getAttackSpeed());
    node->setGameEntity(entity);
    node->setElapsed(delay);
    
    std::string icon=unitProperty->getIcon();
    
    CCLOG("timeline:%s,%f",icon.c_str(),node->getDuration());
    
    if (icon.empty()) {
        icon="character_icon/1.png";
    }
    
    CCSprite* sprite=CCSprite::create(icon.c_str());
    node->setRenderer(sprite);
    m_timelineLayer->addChild(sprite);
    
    
    m_timelineNodes->addObject(node);
    
    node->release();
}

/**
 * 停止某个单位的战斗时间线
 */
void RealtimeBattleController::removeEntityBattleTimeline(GameEntity* entity)
{
    CCObject* obj=NULL;
    TimelineNode* node=NULL;
    int i=0;
    CCARRAY_FOREACH_REVERSE(m_timelineNodes, obj){
        node=static_cast<TimelineNode*>(obj);
        if (node->getGameEntity()==entity) {
            m_timelineLayer->removeChild(node->getRenderer());
            m_timelineNodes->removeObjectAtIndex(i);
            break;
        }
        i++;
    }
}

/**
 * 显示所有战斗单位的战斗时间线
 */
void RealtimeBattleController::showBattleTimeline()
{
    
}

void RealtimeBattleController::showBattleTimeline(TimelineNode* node)
{
    
    float posRate=node->getElapsed()/node->getDuration();
    posRate=posRate>1?1:posRate;
    
    
    CCSprite* renderer=node->getRenderer();
    renderer->setPosition(ccp(posRate*kTimelineWidth,0));
    
}

void RealtimeBattleController::battleUpdate(float delta)
{
    CCLOG("delta:%f",delta);
    
    CCObject* obj=NULL;
    TimelineNode* node=NULL;
    
    CCARRAY_FOREACH_REVERSE(m_timelineNodes, obj){
        node=static_cast<TimelineNode*>(obj);
        
        node->addElapsed(delta);
        
        showBattleTimeline(node);
        
        //这里不考虑超出好几个回合
        if (node->isTurn()) {
            
            node->fixTurn();
            
            //start attack
            entityAttack(node->getGameEntity());
        }
    }
    
    showBattleTimeline();
}

void RealtimeBattleController::parseRound()
{
    
    //哪方先攻击.TODO 根据属性计算
    m_stepSide=kSelfSide;
    
    m_selfStepIndex=0;
    m_oppStepIndex=0;

    parseNextStep();
}

bool RealtimeBattleController::trunSelfStep()
{
    GameEntity* entity=NULL;
    int col=0,row=0;
    if (m_selfStepIndex<kBattleCellSize) {
        //这一轮自己的队伍还有攻击完
        m_selfStepIndex=getSelfExistEntity(m_selfStepIndex, &entity);
        if (!entity) {
            //自己队伍已经被打光
            //战斗结束.用户失败
            doBattleEnd(false);
            return false;
        }
        
        //执行一次攻击
        col=m_selfStepIndex%kBattleCellCol;
        row=m_selfStepIndex/kBattleCellCol;
        entityAttack(entity, col, row, kSelfSide);
        
        ++m_selfStepIndex;
        return true;
    }
    
    return false;
}

bool RealtimeBattleController::trunOppStep()
{
    GameEntity* entity=NULL;
    int col=0,row=0;
    if (m_oppStepIndex<kBattleCellSize) {
        //这一轮自己的队伍还有攻击完
        m_oppStepIndex=getOppExistEntity(m_oppStepIndex, &entity);
        if (!entity) {
            //自己队伍已经被打光
            //战斗结束.用户失败
            doBattleEnd(false);
            return false;
        }
        
        //执行一次攻击
        col=m_oppStepIndex%kBattleCellCol;
        row=m_oppStepIndex/kBattleCellCol;
        entityAttack(entity, col, row, kOppSide);
        
        ++m_oppStepIndex;
        return true;
    }
    
    return false;
}



void RealtimeBattleController::parseNextStep()
{
    if (m_battleEnd) {
        return;
    }
    
    bool stepRet=true;
    
    if (m_stepSide==kSelfSide) {
        
        stepRet=trunSelfStep();
        
        //如果对手还可以攻击，则下个进行攻击的是对方
        if (m_oppStepIndex<kBattleCellSize) {
            m_stepSide=kOppSide;
        }
        
    }else if(m_stepSide==kOppSide){
        
        stepRet=trunOppStep();
        
        //如果对手还可以攻击，则下个进行攻击的是对方
        if (m_selfStepIndex<kBattleCellSize) {
            m_stepSide=kSelfSide;
        }
    }
    
    //没有攻击动作
    if (!stepRet) {
        doStepEnd();
    }
}


bool RealtimeBattleController::isRoundComplete()
{
    return m_selfStepIndex>=kBattleCellSize && m_oppStepIndex>=kBattleCellSize;
}

void RealtimeBattleController::doStepEnd()
{
    if (isRoundComplete()) {
        ++m_round;
        parseRound();
    }else{
        //继续下一步
        parseNextStep();
    }
}

int RealtimeBattleController::getExistEntityBySide(int index,int side,GameEntity** entity)
{
    switch (side) {
        case kSelfSide:
            return getSelfExistEntity(index, entity);
            break;
        case kOppSide:
            return getOppExistEntity(index, entity);
            break;
        default:
            return NULL;
            break;
    }
}


int RealtimeBattleController::getSelfExistEntity(int index,GameEntity** entity)
{
    CCAssert(index>=0&& index<kBattleCellSize, "RealtimeBattleController::getSelfExistEntity index outside");
    
    int col=0,row=0;
    
    GameEntity* searchEntity=NULL;
    for (; index<kBattleCellSize; ++index) {
        col=index%kBattleCellCol;
        row=index/kBattleCellCol;
        searchEntity=getEntityFromSelfTroops(col, row);
        if (searchEntity) {
            *entity=searchEntity;
            return index;
        }
    }
    
    //没有找到
    *entity=NULL;
    return index;
}

int RealtimeBattleController::getOppExistEntity(int index,GameEntity** entity)
{
    CCAssert(index>=0&& index<kBattleCellSize, "RealtimeBattleController::getSelfExistEntity index outside");
    
    int col=0,row=0;
    
    GameEntity* searchEntity=NULL;
    for (; index<kBattleCellSize; ++index) {
        col=index%kBattleCellCol;
        row=index/kBattleCellCol;
        searchEntity=getEntityFromOppTroops(col, row);
        if (searchEntity) {
            *entity=searchEntity;
            return index;
        }
    }
    
    //没有找到
    *entity=NULL;
    return index;
}

void RealtimeBattleController::entityAttack(GameEntity* entity,int col,int row,int side)
{
    CCLOG("entityAttack id:%d,col:%d,row:%d,side:%d",entity->m_uID,col,row,side);
    
    //取得普通攻击目标
    
    //取得对立的一方
    int oppSide=getOtherSide(side);
    
    GameEntity* target=getAttackTarget(col, row, oppSide);
    
    if (target) {
        MessageManager* messageManager=Game::getInstance()->getMessageManager();
        
        messageManager->registerReceiver(entity, kMSGEntityAttackComplete, NULL, message_selector(RealtimeBattleController::onEntityAttackComplete),this);
        
        messageManager->dispatchMessage(MSG_ATTACK, NULL, entity,target);
        
    }else{
        //如果没有目标，说明对方已经打光。
        doBattleEnd(side==kSelfSide);
    }
}

void RealtimeBattleController::entityAttack(GameEntity* entity)
{
    
    BattleProperty* battleProperty=entity->getBattleProperty();
    
    int col=battleProperty->getCol();
    int row=battleProperty->getRow();
    int side=battleProperty->getSide();
    
    CCLOG("entityAttack:[%d],cell=%d,%d side=%d",entity->m_uID,col,row,side);
    
//    return;
    
    //取得普通攻击目标
    
    //取得对立的一方
    int oppSide=getOtherSide(side);
    
    GameEntity* target=getAttackTarget(col, row, oppSide);
    
    if (target) {
        MessageManager* messageManager=Game::getInstance()->getMessageManager();
        
        messageManager->registerReceiver(entity, kMSGEntityAttackComplete, NULL, message_selector(RealtimeBattleController::onEntityAttackComplete),this);
        
        messageManager->dispatchMessage(MSG_ATTACK, NULL, entity,target);
        
    }else{
        //如果没有目标，说明对方已经打光。
        doBattleEnd(side==kSelfSide);
    }
}

/*取得攻击目标
  取得最前排的物体,满足以下条件。
       1.如果这一排和当前物体同列的物体不为空，则就是要找的物体。如果为空，则继续第2步。
       2.取得这一排索引号靠前的元素
*/
GameEntity* RealtimeBattleController::getAttackTarget(int col,int row,int side)
{
    GameEntity* firstEntity;
    
    //取得对方第一个不为空的物体。
    int index=getExistEntityBySide(0,side, &firstEntity);
    
    if (index<kBattleCellSize) {
        //计算第一个不为空的物体所在列。
        int firstEntityCol=index%kBattleCellCol;
        
        //如果正好和当前物体同一列，即要找的物体
        if (firstEntityCol==col) {
            return firstEntity;
        }else{
            //如果不是，则检查那一排和当前列号相同的物体
            int notEmptyRow=index/kBattleCellCol;
            
            GameEntity* sameColEntity=getEntityFromTroops(col, notEmptyRow,side);
            
            //如果找到，则直接返回。没有找到，则返回不为空的那一排的第一个元素。
            return sameColEntity?sameColEntity:firstEntity;
        }
    }
    
    //对方队伍已经打光。
    return NULL;
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
    
    cleanTroops();
    
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

//一个实体攻击完成
void RealtimeBattleController::onEntityAttackComplete(yhge::Message* message)
{
    
    GameEntity* entity=static_cast<GameEntity*>(message->getReceiver());
    
    CCLOG("RealtimeBattleController::onEntityAttackComplete:[%d]",entity->m_uID);
    
    Game::getInstance()->getMessageManager()->removeReceiver(entity, kMSGEntityAttackComplete);
    
//    //一步结束，中间有个小间隔，下个人物才开始行动
//    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
//            schedule_selector(RealtimeBattleController::onEntityAttackCompleteDelay), this, 0.5f, 0, 0.0f, false);
    
}

//一个实体攻击完成
void RealtimeBattleController::onEntityAttackCompleteDelay(float delta)
{
    //检查这一轮是否结束，即这一轮所有用户能参与战斗
    doStepEnd();
}

//一个实体死亡
void RealtimeBattleController::onEntityDie(yhge::Message* message)
{
    GameEntity* entity=static_cast<GameEntity*>(message->getSender());
    
    //entity数据

    BattleProperty* battleProperty=entity->getBattleProperty();
    int side=battleProperty->getSide();
    
    //从战斗队列中移除
    removeEntityFromTroops(entity, side);
    
    //移除消息处理
    removeEntityMessage(entity);
    
//    //从显示队列里移除
//    entity->getRendererComponent()->getRenderer()->removeFromParent();
    
}

void RealtimeBattleController::onSkip(CCObject* pSender)
{
    cleanTroops();
    
    //goto before battle scene
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

void RealtimeBattleController::onStart(CCObject* pSender)
{
//    start();
}

bool RealtimeBattleController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void RealtimeBattleController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void RealtimeBattleController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void RealtimeBattleController::registerEntityMessage(GameEntity* entity)
{
    MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, entity, message_selector(RealtimeBattleController::onEntityDie), this);
}

void RealtimeBattleController::removeEntityMessage(GameEntity* entity)
{
    MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, entity);
    
    //防止中途退出没有消除消息
    messageManager->removeReceiver(entity, kMSGEntityAttackComplete);
}

NS_CC_GE_END