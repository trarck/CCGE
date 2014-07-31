#include "BattleManager.h"
#include "Consts/GameDefine.h"

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
void BattleManager::enterStage(yhge::Json::Value& stageInfo,GameEntityVector& heroList,bool isBot,int startWaveId)
{
    resetStage();
    
    setupSelfEntities(heroList,isBot);
    
}

//进入竞技场
void BattleManager::enterArena(GameEntityVector& heroList,GameEntityVector& enemyList,bool heroIsBot,bool enemyIsBot)
{
    
}

//进入远程

void BattleManager::enterCrusade(GameEntityVector& heroList,GameEntityVector& enemyList,bool enemyisBot,yhge::Json::Value& selfCrusade,yhge::Json::Value& enemyCrusade,int stageId)
{
    
}

//进入矿场
void BattleManager::enterExcavate(GameEntityVector& heroList,GameEntityVector& enemyList,bool enemyisBot,yhge::Json::Value& selfDynaList,yhge::Json::Value& enemyDynaList,int stageId)
{
    
}

//初始化己方战斗单位
void BattleManager::setupSelfEntities(GameEntityVector& heroList,bool isBot)
{
    //short hero by attack range
    
    for (GameEntityVector::iterator iter=heroList.begin(); iter!=heroList.end(); ++iter) {
        
    }
}

// 初始化敌方战斗单位
void BattleManager::setupEnemyEntities(GameEntityVector& heroList)
{
    
}

GameEntityVector BattleManager::sortEntity(const GameEntityVector& entityList)
{
    GameEntityVector sortedList;
    
    GameEntity* entity=NULL;
    
    for (GameEntityVector::const_iterator iter=entityList.begin();iter!=entityList.end(); ++iter) {
        
        entity=*iter;
        
        entity->getUnitProperty()->getatt
    }
    
    return sortedList;
}
NS_CC_GE_END
