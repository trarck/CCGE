#include "BattleSystem.h"
#include "Consts/GameDefine.h"

USING_NS_CC;

USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BattleSystem::BattleSystem()
:m_enabled(true)
,m_frame(0)
,m_frameInterval(kFrameInterval)
,m_nextTick(0)
,m_nextOperationIndex(0)
,m_running(false)
,m_timeLimit(kBattleTime)
{
    
}

BattleSystem::~BattleSystem()
{
    CCLOG("BattleSystem destroy");
}

void BattleSystem::resetBattle()
{
    m_enabled=true;
    m_frame=0;
    m_frameInterval=kFrameInterval;
    m_nextOperationIndex=0;
    
    resetWave();
}

void BattleSystem::resetWave()
{
    m_nextTick=0;
    m_timeLimit=kBattleTime;
    m_freezeLevel=0;
    m_running=true;
    m_aliveAllianceCount=0;
    m_aliveEnemyCount=0;
    
}

void BattleSystem::setupWave(const yhge::Json::Value& waveInfo)
{
    for (int i=0; i<kBattleTeamMaxCount; ++i) {
        
    }
}


void BattleSystem::start()
{
    resetBattle();
}

void BattleSystem::exit()
{
    
}

void BattleSystem::update(float delta)
{
    if(m_running){
        
        m_nextTick-=delta;
        
        if (m_nextTick<=0) {
            
            //执行一个frame
            tick();
            
            //有的时候，delta会很大。比如卡了一下。这里按忽略处理。即不跳帧(通常动画可以跳帧，但战斗帧都不跳).
            //修复计时器.如果正好为0，则要设置为帧间隔。
            while (m_nextTick<=0) {
                m_nextTick+=m_frameInterval;
            }
        }
    }
}

void BattleSystem::tick()
{
    if (!m_running) {
        return;
    }
    
    //计算战斗剩余时间
    m_timeLimit-=m_frameInterval;
    //处理手动技能
    
    while (m_nextOperationIndex<m_operationList.size()) {
        Operation op=m_operationList[m_nextOperationIndex];
        if (op.frame==m_frame) {
            //get unit
            
            //fire manual skill
            ++m_nextOperationIndex;
        }else if(op.frame<m_frame){
            //show error
        }else{
            break;
        }
    }
    
    //call entity update
    
    ++m_frame;
    
    //check battle end
    if (m_timeLimit<=0) {
        //timeout
    }else if (m_aliveEnemyCount==0){
        //win
    }else if (m_aliveAllianceCount==0){
        //fail
        
    }
    
}

NS_CC_GE_END
