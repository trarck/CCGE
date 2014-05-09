
#ifndef CCGE_SYSTEMS_BATTLES_BATTLESYSTEM_H_
#define CCGE_SYSTEMS_BATTLES_BATTLESYSTEM_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

struct Operation
{
    int waveId;
    int frame;
    int unitIndex;
};

/**
 * 一场战斗分为几波
 */
class BattleSystem:public CCObject
{
public:
    
	BattleSystem();
    
	~BattleSystem();
    
    /**
     * @brief 重制一场战斗
     */
    void resetBattle();
    
    /**
     * @brief 重制战斗的一波
     */
    void resetWave();
    
    void setupWave(const yhge::Json::Value& waveInfo);
        
    void start();
    
    void exit();
    
    void update(float delta);
    
    void tick();
    
    void onBattleEnd();
    
public:
    
    inline void setFrame(int frame)
    {
        m_frame = frame;
    }
    
    inline int getFrame()
    {
        return m_frame;
    }
    
    inline void setFrameInterval(float frameInterval)
    {
        m_frameInterval = frameInterval;
    }
    
    inline float getFrameInterval()
    {
        return m_frameInterval;
    }
    
    inline void setNextTick(float nextTick)
    {
        m_nextTick = nextTick;
    }
    
    inline float getNextTick()
    {
        return m_nextTick;
    }
    
    inline void setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }
    
    inline bool isEnabled()
    {
        return m_enabled;
    }
    
    inline void setNextOperationIndex(int nextOperationIndex)
    {
        m_nextOperationIndex = nextOperationIndex;
    }
    
    inline int getNextOperationIndex()
    {
        return m_nextOperationIndex;
    }
    
    inline void setRunning(bool running)
    {
        m_running = running;
    }
    
    inline bool isRunning()
    {
        return m_running;
    }
    
    inline void setTimeLimit(float timeLimit)
    {
        m_timeLimit = timeLimit;
    }
    
    inline float getTimeLimit()
    {
        return m_timeLimit;
    }
    
    inline void setAliveAllianceCount(int aliveAllianceCount)
    {
        m_aliveAllianceCount = aliveAllianceCount;
    }
    
    inline int getAliveAllianceCount()
    {
        return m_aliveAllianceCount;
    }
    
    inline void setAliveEnemyCount(int aliveEnemyCount)
    {
        m_aliveEnemyCount = aliveEnemyCount;
    }
    
    inline int getAliveEnemyCount()
    {
        return m_aliveEnemyCount;
    }
    
    inline void setFreezeLevel(int freezeLevel)
    {
        m_freezeLevel = freezeLevel;
    }
    
    inline int getFreezeLevel()
    {
        return m_freezeLevel;
    }
    
protected:
    //是否可用
    bool m_enabled;
    //战斗帧序列
    int m_frame;
    
    //战斗帧的时长
    float m_frameInterval;
    
    //计数时否进入战斗帧
    float m_nextTick;
    
    //下一个操作索引
    int m_nextOperationIndex;
    
    //是否在在进行
    bool m_running;
    
    //战斗总时间.单位秒
    float m_timeLimit;
    
    //自方存活数量
    int m_aliveAllianceCount;
    //对手存活数量
    int m_aliveEnemyCount;
    //冻结等级，放大招的时候，战斗逻辑停止。同时有多个人物放的时候，要加一下，结束的时候再减一。当为0的时候再恢复
    int m_freezeLevel;
    
    
    std::vector<Operation> m_operationList;
};

NS_CC_GE_END



#endif // CCGE_SYSTEMS_BATTLES_BATTLESYSTEM_H_
