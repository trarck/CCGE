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
    UnitProperty* unitProperty=static_cast<UnitProperty*>(entity->getProperty(CCGE_PROPERTY_UNIT));
    int camp=unitProperty->getCamp();
    
    if(unitProperty->isAlive()){
        m_aliveUnits[camp].push_back(entity);
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
    resetStage();
    
    setupSelfEntities(heroList,heroIsBot);
    
    setupEnemyEntities(enemyList, enemyIsBot);
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
    heroList=sortEntity(heroList);
    
    int i=0;
    float x=0,y=0;
    
    for (HeroVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {
        x=i*-80;
        y=i&1?-40:40;
        (*iter)["position_x"]=x;
        
        (*iter)["position_y"]=y;
        
//        CCLOG("pos:%d,%f,%f",i,x,y);
        
        ++i;
        
        GameEntity* heroEntity=createEntity(*iter);
        
        if (heroEntity) {
            
            addUnit(heroEntity);
            
            
        }else{
            CCAssert(false, "BattleManager::setupSelfEntities create entity faile");
        }
    }
}

// 初始化敌方战斗单位
void BattleManager::setupEnemyEntities(HeroVector& heroList,bool isBot)
{
    heroList=sortEntity(heroList);
    
    int i=0;
    for (HeroVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {

        (*iter)["position_x"]=800+i*80;
        
        (*iter)["position_y"]=i&1?-40:40;
        
        ++i;
        
        GameEntity* heroEntity=createEntity(*iter);
        
        if (heroEntity) {
            
            addUnit(heroEntity);
        
        }else{
            CCAssert(false, "BattleManager::setupSelfEntities create entity faile");
        }
    }
}


HeroVector BattleManager::sortEntity(const HeroVector& entityList)
{
    HeroVector sortedList;

    DataFactory* dataFactory=Game::getInstance()->getDataFactory();
    UnitDAO* unitDAO=dataFactory->getUnitDAO();
    SkillDAO* skillDAO=dataFactory->getSkillDAO();
    CharacterDAO* characterDAO=dataFactory->getCharacterDAO();
    
    int entityId=0;
    
    //calc attack range
    std::map<int, float> entityRange;
    
    for (HeroVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        entityId=(*iter)["id"].asInt();
        
        Json::Value characterConfig=characterDAO->getDataById(entityId);
        
        int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
        
        Json::Value unitProto=unitDAO->getDataById(unitId);

        
        int baseSkillId=unitProto["basic_skill"].asInt();
        Json::Value skillProto=skillDAO->getDataById(baseSkillId);
        float attackRange=skillProto["max_range"].asDouble();
        
        entityRange[entityId]=attackRange;
    }
    
    int innerEntityId=0;
    float attackRange=0,innerAttackRange=0;
    bool haveInserted=false;
    
    for (HeroVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        entityId=(*iter)["id"].asInt();
        attackRange=entityRange[entityId];
        haveInserted=false;
        
        for (HeroVector::iterator inner=sortedList.begin(); inner!=sortedList.end(); ++inner) {
            innerEntityId=(*inner)["id"].asInt();
            innerAttackRange=entityRange[innerEntityId];
            
            if (attackRange<innerAttackRange) {
                sortedList.insert(inner, *iter);
                haveInserted=true;
                break;
            }
        }
        
        if (!haveInserted) {
            sortedList.push_back(*iter);
        }
    }
    
    return sortedList;
}

GameEntity* BattleManager::createEntity(yhge::Json::Value& hero)
{
    GameEntity* entity=NULL;
    
    EntityFactory* entityFactory=Game::getInstance()->getEngine()->getEntityFactory();
    DataFactory* dataFactory=Game::getInstance()->getDataFactory();
    
    UnitService* unitService=ServiceFactory::getInstance()->getUnitService();
    CharacterDAO* characterDAO=dataFactory->getCharacterDAO();
    
    UnitDAO* unitDAO=dataFactory->getUnitDAO();
    SkillDAO* skillDAO=dataFactory->getSkillDAO();
    
    int entityId=hero["id"].asInt();
    
    float x=hero["position_x"].asDouble();
    float y=hero["position_y"].asDouble();
    int camp=hero["camp"].asInt();
    
    entity=entityFactory->createEntity(entityId);
    

    
    Json::Value characterConfig=characterDAO->getDataById(entityId);
    
    int unitId=characterConfig[CCGE_PLAYER_UNIT_ID].asInt();
    float scale=characterConfig[CCGE_PLAYER_SCALE].asDouble();
    int level=characterConfig[CCGE_PLAYER_LEVEL].asInt();
    int rank=2;
    int stars=3;

    //设置单位属性
    Json::Value unitConfig;
    Json::Value unitInfo=unitDAO->getDataById(unitId);
    
    unitConfig[CCGE_UNIT_CAMP]=camp;
    unitConfig[CCGE_COMMON_LEVEL]=level;
    unitConfig[CCGE_COMMON_RANK]=rank;
    unitConfig[CCGE_COMMON_STARS]=stars;
    unitConfig[CCGE_UNIT_SIZE_MOD]=scale;
    
    //get attack range for sort hero
    int baseSkillId=unitInfo[CCGE_UNIT_BASIC_SKILL].asInt();
    Json::Value skillProto=skillDAO->getDataById(baseSkillId);
    float attackRange=skillProto[CCGE_SKILL_MAX_RANGE].asDouble();
    unitConfig[CCGE_UNIT_ATTACK_RANGE]=attackRange;
    
    entityFactory->getEntityPropertyFactory()->addUnitProperty(entity, unitConfig, unitInfo);

    //设置战斗属性
    Json::Value battleConfig;
    battleConfig[CCGE_COMMON_LEVEL]=level;
    battleConfig[CCGE_COMMON_RANK]=rank;
    battleConfig[CCGE_COMMON_STARS]=stars;
    
    entityFactory->getEntityPropertyFactory()->addRealtimeBattleProperty(entity,battleConfig,unitInfo);
    
    //设置移动属性
    Json::Value moveConfig;
    moveConfig[CCGE_COMMON_X]=x;
    moveConfig[CCGE_COMMON_Y]=y;
    moveConfig[CCGE_UNIT_CAMP]=camp;
    
    entityFactory->getEntityPropertyFactory()->addMoveProperty(entity, moveConfig);
    
    //添加组件
    entityFactory->addRealtimeBattleComponents(entity);
    
    return entity;
}

NS_CC_GE_END
