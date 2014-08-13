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
    
    
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
