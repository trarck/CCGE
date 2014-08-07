
#ifndef CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEUPDATEMANAGER_H_
#define CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEUPDATEMANAGER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"


NS_CC_GE_BEGIN

/**
 * 战斗更新管理器
 */
class BattleUpdateManager : public yhge::UpdateManager
{
public:
    
    BattleUpdateManager();
    
    virtual ~BattleUpdateManager();
    
    virtual void update(float delta);
    
public:
    
    inline void setElapsed( float elapsed)
    {
        m_elapsed = elapsed;
    }
    
    inline  float getElapsed()
    {
        return m_elapsed;
    }
    
    inline void setInterval(float interval)
    {
        m_interval = interval;
    }
    
    inline float getInterval()
    {
        return m_interval;
    }
    
    inline void setTicks(int ticks)
    {
        m_ticks = ticks;
    }
    
    inline int getTicks()
    {
        return m_ticks;
    }
    
protected:
    
    float m_elapsed;
    float m_interval;
    
    int m_ticks;
    
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_BATTLEUPDATEMANAGER_H_
