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

void BattleManager::enterStage(yhge::Json::Value& stageInfo,GameEntityVector& heroList,bool isBot,int startWaveId)
{
    
}

NS_CC_GE_END
