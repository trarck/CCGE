#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BattleProperty : public yhge::Property
{
public:
    
    inline BattleProperty()
    :m_scale(1.0f)
    ,m_position(CCPointZero)
    ,m_camp(0)
    ,m_alive(true)
    ,m_attackRange(false)
    ,m_globalCd(0)
    ,m_state(0)
    ,m_walkVelocity(CCPointZero)
    ,m_knockupVelocity(CCPointZero)
    {
        
    }
    
    
    inline void setScale(float scale)
    {
        m_scale = scale;
    }
    
    inline float getScale()
    {
        return m_scale;
    }
    
    inline void setX(float x)
    {
        m_position.x = x;
    }
    
    inline float getX()
    {
        return m_position.x;
    }
    
    inline void setY(float y)
    {
        m_position.y = y;
    }
    
    inline float getY()
    {
        return m_position.y;
    }
    
    inline void setPosition(const CCPoint& position)
    {
        m_position = position;
    }
    
    inline const CCPoint& getPosition()
    {
        return m_position;
    }
    

    inline void setCamp(int camp)
    {
        m_camp = camp;
    }
    
    inline int getCamp()
    {
        return m_camp;
    }
    
    inline void setAlive(bool alive)
    {
        m_alive = alive;
    }
    
    inline bool isAlive()
    {
        return m_alive;
    }

    inline void setAttackRange(float attackRange)
    {
        m_attackRange = attackRange;
    }
    
    inline float getAttackRange()
    {
        return m_attackRange;
    }
    
    inline void setGlobalCd(float globalCd)
    {
        m_globalCd = globalCd;
    }
    
    inline float getGlobalCd()
    {
        return m_globalCd;
    }
    
    inline void addGlobalCd(float delta)
    {
        m_globalCd+=delta;
    }
    
    inline void setState(int state)
    {
        m_state = state;
    }
    
    inline int getState()
    {
        return m_state;
    }
    
    inline void setWalkVelocity(const CCPoint& walkVelocity)
    {
        m_walkVelocity = walkVelocity;
    }
    
    inline const CCPoint& getWalkVelocity()
    {
        return m_walkVelocity;
    }
    
    inline void setKnockupVelocity(const CCPoint& knockupVelocity)
    {
        m_knockupVelocity = knockupVelocity;
    }
    
    inline const CCPoint& getKnockupVelocity()
    {
        return m_knockupVelocity;
    }

protected:
    
    //缩放
    float m_scale;

    //坐标
    CCPoint m_position;
    
    //阵营
    int m_camp;
    
    //是否活着
    bool m_alive;
    
    //攻击距离
    float m_attackRange;
    
    //释放技能的间隔cd
    float m_globalCd;
    
    int m_state;
    
    //移动速度
    CCPoint m_walkVelocity;
    
    //击退速度。有些技能有击退功能
    CCPoint m_knockupVelocity;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
