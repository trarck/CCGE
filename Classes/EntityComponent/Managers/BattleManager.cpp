#include "BattleManager.h"
#include "Consts/GameDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/PropertyDefine.h"
#include "Game.h"
#include "Services/ServiceFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


BattleManager::BattleManager()
:m_aliveAllianceCount(0)
,m_aliveEnemyCount(0)
,m_deadAllianceCount(0)
,m_deadEnemyCount(0)
,m_arenaMode(false)
,m_crusadeMode(false)
,m_excavateMode(false)
,m_guildInstanceMode(false)
,m_replayMode(false)
,m_stageRect(CCRectMake(0, -120, 800, 240))
{
    YHDEBUG("UpdateManager create");
}

BattleManager::~BattleManager()
{
    YHDEBUG("UpdateManager destroy");
}

bool BattleManager::init()
{
    if (ECManager::init()) {
        
        reset();
        
        return true;
    }
    
    return false;
}

void BattleManager::reset()
{
    resetUnits();
    resetAliveUnits();
    
    m_aliveAllianceCount=0;
    m_aliveEnemyCount=0;
    m_deadAllianceCount=0;
    m_deadEnemyCount=0;
    
    m_arenaMode=false;
    m_crusadeMode=false;
    m_excavateMode=false;
    m_replayMode=false;
    m_guildInstanceMode=false;
    
    //清除操作列表
    m_oprationList.clear();
}

void BattleManager::resetUnits()
{
    m_units.clear();
}

void BattleManager::resetAliveUnits()
{
    m_aliveUnits.clear();
    
    m_aliveUnits[kCampPlayer]=GameEntityVector();
    m_aliveUnits[kCampEnemy]=GameEntityVector();
    m_aliveUnits[kCampBoth]=GameEntityVector();
}

void BattleManager::resetStage()
{
    
}

void BattleManager::addUnit(GameEntity* entity)
{
    m_units.push_back(entity);
    
    //TODO if alive then add to alive list
    BattleProperty* battleProperty=entity->getBattleProperty();
    int camp=battleProperty->getCamp();
    
    if(battleProperty->isAlive()){
        m_aliveUnits[battleProperty->getCamp()].push_back(entity);
        if (camp==kCampPlayer) {
            ++m_aliveAllianceCount;
        }else if (camp==kCampEnemy){
            ++m_aliveEnemyCount;
        }
    }else{
        if (camp==kCampPlayer) {
            ++m_deadAllianceCount;
        }else if (camp==kCampEnemy){
            ++m_deadEnemyCount;
        }
    }
}

//进入关卡
void BattleManager::enterStage(yhge::Json::Value& stageInfo,HeroVector& heroList,bool isBot,int startWaveId)
{
    resetStage();
    
    setupSelfEntities(heroList,isBot);
    
}

//进入竞技场
void BattleManager::enterArena(HeroVector& heroList,HeroVector& enemyList,bool heroIsBot,bool enemyIsBot)
{
    
}

//进入远程

void BattleManager::enterCrusade(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfCrusade,yhge::Json::Value& enemyCrusade,int stageId)
{
    
}

//进入矿场
void BattleManager::enterExcavate(HeroVector& heroList,HeroVector& enemyList,bool enemyisBot,yhge::Json::Value& selfDynaList,yhge::Json::Value& enemyDynaList,int stageId)
{
    
}

//初始化己方战斗单位
void BattleManager::setupSelfEntities(HeroVector& heroList,bool isBot)
{
    //short hero by attack range
    
    for (HeroVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {
        
        GameEntity* heroEntity=createEntity(*iter);
        
        if (heroEntity) {
            
            addUnit(heroEntity);
            
            
        }else{
            CCAssert(false, "BattleManager::setupSelfEntities create entity faile");
        }
    }
}

// 初始化敌方战斗单位
void BattleManager::setupEnemyEntities(HeroVector& heroList)
{
    
}

HeroVector BattleManager::sortEntity(const HeroVector& entityList)
{
    HeroVector sortedList;

    for (HeroVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        
        //look up skill table
    }
    
    return sortedList;
}

GameEntity* BattleManager::createEntity(yhge::Json::Value& hero)
{
    GameEntity* entity=NULL;
    
    EntityFactory* entityFactory=Game::getInstance()->getEngine()->getEntityFactory();
    DataFactory* dataFactory=Game::getInstance()->getDataFactory();
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    
    int entityId=hero["id"].asInt();
    
    float x=hero["position_x"].asDouble();
    float y=hero["position_y"].asDouble();
    int camp=hero["camp"].asInt();
    
    entity=entityFactory->createEntity(entityId);
    
    CharacterData* characterData=dataFactory->getCharacterData();
    
    Json::Value characterConfig=characterData->getDataById(entityId);
    
    int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
    float scale=characterConfig[CCGE_PLAYER_SCALE].asDouble();
    int level=characterConfig[CCGE_PLAYER_LEVEL].asInt();

    UnitData* unitData=dataFactory->getUnitData();
    
    Json::Value unitProto=unitData->getDataById(unitId);
    
    //设置单位属性
    UnitProperty* unitProperty=unitService->createUnitPropertyFromLevel(level, unitProto);
    entity->addProperty(unitProperty, CCGE_PROPERTY_UNIT);
    entity->setUnitProperty(unitProperty);

    //设置战斗属性
    entityFactory->getEntityPropertyFactory()->addRealtimeBattleProperty(entity,x,y,camp,scale);
    
    //添加组件
    entityFactory->addRealtimeBattleComponents(entity);
    
    return entity;
}

NS_CC_GE_END
