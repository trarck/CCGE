#include "BattleController.h"
#include <yhgui/yhgui.h>
#include <yhge/yhge.h>
#include "Game.h"
#include "Consts/PropertyDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/Components/BattlePositionComponent.h"
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

BattleController::BattleController(void)
:m_mapId(0)
,m_zoneId(0)
,m_round(0)
,m_stepSide(0)
,m_selfStepIndex(0)
,m_oppStepIndex(0)
,m_battleEnd(false)
,m_win(false)
,m_battleWorld(NULL)
{
    m_sName="BattleController";
}

BattleController::~BattleController(void)
{
    CCLOG("BattleController destroy");
    
    CC_SAFE_RELEASE_NULL(m_battleWorld);
}

bool BattleController::init()
{
    if (BaseController::init()) {
        
        initTroops();
        
        return true;
    }
    
    return false;
}

void BattleController::viewDidLoad()
{
    loadBattleGround();
    
    //create battle layer
    loadBattleWorld();
    
    loadEntities();
    
//    showCoordinate();
    
    //create test button
    
    CCMenuItemLabel *skipBtn=CCMenuItemLabel::create(CCLabelTTF::create("skip", "Arial", 34),
                                                   this,
                                                   menu_selector(BattleController::onSkip));
    
    CCMenuItemLabel *startBtn=CCMenuItemLabel::create(CCLabelTTF::create("start", "Arial", 34),
                                                     this,
                                                     menu_selector(BattleController::onStart));

    CCMenu* menu=CCMenu::create(skipBtn,startBtn,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
    
}

void BattleController::onViewEnter()
{
    Controller::onViewEnter();
    delayStart();
}

void BattleController::onViewExit()
{
    CCLOG("BattleController::onViewExit %d",this->retainCount());
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Controller::onViewExit();
}

void BattleController::loadBattleGround()
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

void BattleController::loadBattleWorld()
{
    m_battleWorld=new CCLayer();
    m_battleWorld->setPosition(ccp(0,100));
    m_view->addChild(m_battleWorld);
}

void BattleController::showCoordinate()
{
    //show coordinate line
    DimetricCoordinateLayer* coordLayer=new DimetricCoordinateLayer();
    coordLayer->setMapWidth(20);
    coordLayer->setMapHeight(20);
    coordLayer->setAnchorPoint(ccp(0,0));
    coordLayer->setPosition(ccp(0,1));
    
    m_view->addChild(coordLayer);
    
    coordLayer->release();
}

void BattleController::loadEntities()
{
    //加载自己
    this->loadSelfEntities();
    
    //加载对方
    this->loadOppEntities();
    

}


void BattleController::convertIndexToCell(int index,int* col,int* row)
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

void BattleController::convertCoord(int index,int* col,int* row,int* x,int* y)
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
void BattleController::convertOppCoord(int index,int* col,int* row,int* x,int* y)
{
    *col=index%kBattleCellCol;
    *row=index/kBattleCellCol;
    
    //x=kBattleCellCol-row-1
    //y=kBattleCellRow-col-1;
    *x=*row;
    *y=kBattleCellCol-*col-1;
}

void BattleController::loadSelfEntities()
{
    BattleService* battleService=ServiceFactory::getInstance()->getPveBattleService();

    std::vector<int> troops=battleService->getSelfTroops();
    
    int teamSize=troops.size();
    
    int entityId=0;
    
    for (int i=0; i<teamSize; ++i) {
        
        entityId=troops[i];
        
        if (entityId) {
                        
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

void BattleController::loadOppEntities()
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
void BattleController::initTroops()
{
    for (int j=0; j<kBattleCellRow; ++j) {
        for (int i=0; i<kBattleCellCol; ++i) {
            m_selfTroops[j][i]=NULL;
            m_oppTroops[j][i]=NULL;
        }
    }
}

//消除战斗双方的队伍
void BattleController::cleanTroops()
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
GameEntity* BattleController::createSelfTroopEntity(int entityId,int index)
{
    
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    //取得坐标.index转化成9宫格的坐标
    convertCoord(index, &col, &row, &x, &y);
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    
    //创建实体
    GameEntity* entity=Game::getInstance()->getEngine()->getEntityFactory()->createEntity(entityId);
    
    //设置实体属性
    
    CharacterDAO* characterDAO=Game::getInstance()->getDataFactory()->getCharacterDAO();
    
    Json::Value characterConfig=characterDAO->getDataById(entityId);
    
    int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
    float scale=characterConfig[CCGE_PLAYER_SCALE].asDouble();
    int level=characterConfig[CCGE_PLAYER_LEVEL].asInt();
    
    //取得配置
    UnitDAO* unitDAO=Game::getInstance()->getDataFactory()->getUnitDAO();

    Json::Value unitConfig=unitDAO->getDataById(unitId);

    
    //设置单位属性
    UnitProperty* unitProperty=unitService->createUnitPropertyFromLevel(level, unitConfig);
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
//    entity->setUnitProperty(unitProperty);
    
    //设置战斗属性
//    Game::getInstance()->getEngine()->getEntityFactory()->getEntityPropertyFactory()->addBattleProperty(entity,col,row,kSelfSide,scale);
    
    //添加组件
    Game::getInstance()->getEngine()->getEntityFactory()->addBattleComponents(entity);
    
    RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
    m_battleWorld->addChild(rendererComponent->getRenderer());
    
    
    addEntityToSelfTroops(entity, col, row);
    
    return entity;
}

GameEntity* BattleController::createOppTroopEntity(int entityId,int index)
{
    
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    //取得坐标.index转化成9宫格的坐标
    convertOppCoord(index, &col, &row, &x, &y);
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    
    //创建实体
    GameEntity* entity=Game::getInstance()->getEngine()->getEntityFactory()->createEntity(entityId);
    
    //设置实体属性
    
    MonsterDAO* monsterDAO=Game::getInstance()->getDataFactory()->getMonsterDAO();
    
    Json::Value monsterConfig=monsterDAO->getDataById(entityId);
    
    int unitId=monsterConfig[CCGE_MONSTER_UNIT_ID].asInt();
    float scale=monsterConfig[CCGE_MONSTER_SCALE].asDouble();
    int level=monsterConfig[CCGE_MONSTER_LEVEL].asInt();
    
    //取得配置
    UnitDAO* unitDAO=Game::getInstance()->getDataFactory()->getUnitDAO();
    
    Json::Value unitConfig=unitDAO->getDataById(unitId);
    
    //设置单位属性
    UnitProperty* unitProperty=unitService->createUnitPropertyFromLevel(level, unitConfig);
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
//    entity->setUnitProperty(unitProperty);
    
    //设置战斗属性
//    Game::getInstance()->getEngine()->getEntityFactory()->getEntityPropertyFactory()->addBattleProperty(entity,col,row,kOppSide,scale);
    
    //添加组件
    Game::getInstance()->getEngine()->getEntityFactory()->addBattleComponents(entity);
    
    RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
    m_battleWorld->addChild(rendererComponent->getRenderer());
    
    addEntityToOppTroops(entity, col, row);
    
    return entity;
}


void BattleController::addEntityToSelfTroops(GameEntity* entity,int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    if (m_selfTroops[row][col]) {
        m_selfTroops[row][col]->release();
    }
    m_selfTroops[row][col]=entity;
    CC_SAFE_RETAIN(entity);
}

void BattleController::removeEntityFromSelfTroops(GameEntity* entity)
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

void BattleController::removeEntityFromSelfTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    if (m_selfTroops[row][col]) {
        m_selfTroops[row][col]->release();
        m_selfTroops[row][col]=NULL;
    }
}

GameEntity* BattleController::getEntityFromSelfTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    return m_selfTroops[row][col];
}

void BattleController::addEntityToOppTroops(GameEntity* entity,int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    if (m_oppTroops[row][col]) {
        m_oppTroops[row][col]->release();
    }
    m_oppTroops[row][col]=entity;
    CC_SAFE_RETAIN(entity);
}

void BattleController::removeEntityFromOppTroops(GameEntity* entity)
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

void BattleController::removeEntityFromOppTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    if (m_oppTroops[row][col]) {
        m_oppTroops[row][col]->release();
        m_oppTroops[row][col]=NULL;
    }
}

GameEntity* BattleController::getEntityFromOppTroops(int col,int row)
{
    CCAssert(col>=0 && col<kBattleCellCol, "BattleController::addEntityToSelfTroops col out index");
    CCAssert(row>=0 && row<kBattleCellRow, "BattleController::addEntityToSelfTroops row out index");
    
    return m_oppTroops[row][col];
}

GameEntity* BattleController::getEntityFromTroops(int col,int row,int side)
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
void BattleController::addEntityToTroops(GameEntity* entity,int col,int row,int side)
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
void BattleController::removeEntityFromTroops(GameEntity* entity,int side)
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
void BattleController::removeEntityFromTroops(int col,int row,int side)
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

void BattleController::delayStart()
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BattleController::onDdelayStartUpdate), this, 1.0f, 0, 0.0, false);
}

void BattleController::onDdelayStartUpdate(float delta)
{
    start();
}

void BattleController::start()
{
    m_battleEnd=false;
    parseRound();
}

void BattleController::pause()
{
    
}

void BattleController::stop()
{
    
}

void BattleController::parseRound()
{
    
    //哪方先攻击.TODO 根据属性计算
    m_stepSide=kSelfSide;
    
    m_selfStepIndex=0;
    m_oppStepIndex=0;

    parseNextStep();
}

bool BattleController::trunSelfStep()
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

bool BattleController::trunOppStep()
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


void BattleController::battleUpdate(float delta)
{
    
}

void BattleController::parseNextStep()
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


bool BattleController::isRoundComplete()
{
    return m_selfStepIndex>=kBattleCellSize && m_oppStepIndex>=kBattleCellSize;
}

void BattleController::doStepEnd()
{
    if (isRoundComplete()) {
        ++m_round;
        parseRound();
    }else{
        //继续下一步
        parseNextStep();
    }
}

int BattleController::getExistEntityBySide(int index,int side,GameEntity** entity)
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


int BattleController::getSelfExistEntity(int index,GameEntity** entity)
{
    CCAssert(index>=0&& index<kBattleCellSize, "BattleController::getSelfExistEntity index outside");
    
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

int BattleController::getOppExistEntity(int index,GameEntity** entity)
{
    CCAssert(index>=0&& index<kBattleCellSize, "BattleController::getSelfExistEntity index outside");
    
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

void BattleController::entityAttack(GameEntity* entity,int col,int row,int side)
{
    CCLOG("entityAttack id:%d,col:%d,row:%d,side:%d",entity->m_uID,col,row,side);
    
    //取得普通攻击目标
    
    //取得对立的一方
    int oppSide=getOtherSide(side);
    
    GameEntity* target=getAttackTarget(col, row, oppSide);
    
    if (target) {
        MessageManager* messageManager=Game::getInstance()->getMessageManager();
        
        messageManager->registerReceiver(entity, kMSGEntityAttackComplete, NULL, message_selector(BattleController::onEntityAttackComplete),this);
        
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
GameEntity* BattleController::getAttackTarget(int col,int row,int side)
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
void BattleController::doBattleEnd(bool win)
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
                                        CCCallFunc::create(this, callfunc_selector(BattleController::onEndTipCallback)),
                                        NULL);
    
    tempLabel->runAction(action);
}

void BattleController::onEndTipCallback()
{
    
    cleanTroops();
    
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

//一个实体攻击完成
void BattleController::onEntityAttackComplete(yhge::Message* message)
{
    
    GameEntity* entity=static_cast<GameEntity*>(message->getReceiver());
    
    CCLOG("BattleController::onEntityAttackComplete:%d",entity->m_uID);
    
    Game::getInstance()->getMessageManager()->removeReceiver(entity, kMSGEntityAttackComplete);
    
    //一步结束，中间有个小间隔，下个人物才开始行动
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
            schedule_selector(BattleController::onEntityAttackCompleteDelay), this, 0.5f, 0, 0.0f, false);
    
}

//一个实体攻击完成
void BattleController::onEntityAttackCompleteDelay(float delta)
{
    //检查这一轮是否结束，即这一轮所有用户能参与战斗
    doStepEnd();
}

//一个实体死亡
void BattleController::onEntityDie(yhge::Message* message)
{
    GameEntity* entity=static_cast<GameEntity*>(message->getSender());
    
    //entity数据

//    BattleProperty* battleProperty=static_cast<BattleProperty*>(entity->getProperty(CCGE_PROPERTY_BATTLE));
//    int side=battleProperty->getCamp();
//    
//    //从战斗队列中移除
//    removeEntityFromTroops(entity, side);
//    
//    //移除消息处理
//    removeEntityMessage(entity);
    
//    //从显示队列里移除
//    entity->getRendererComponent()->getRenderer()->removeFromParent();
    
}

void BattleController::onSkip(CCObject* pSender)
{
    cleanTroops();
    
    //goto before battle scene
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

void BattleController::onStart(CCObject* pSender)
{
//    start();
}

bool BattleController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BattleController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void BattleController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void BattleController::registerEntityMessage(GameEntity* entity)
{
    MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, entity, message_selector(BattleController::onEntityDie), this);
}

void BattleController::removeEntityMessage(GameEntity* entity)
{
    MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, entity);
    
    //防止中途退出没有消除消息
    messageManager->removeReceiver(entity, kMSGEntityAttackComplete);
}

NS_CC_GE_END