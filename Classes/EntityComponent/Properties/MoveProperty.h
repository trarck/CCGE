#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_MOVEPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_MOVEPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class MoveProperty : public yhge::Property
{
public:
    
    MoveProperty()
    :m_position(CCPointZero)
    ,m_previousPosition(CCPointZero)
    ,m_walkVelocity(CCPointZero)
    ,m_knockupTime(0.0f)
    ,m_knockupVelocity(CCPointZero)
    ,m_velocity(CCPointZero)
    ,m_direction(0)
    {
        
    }
    
    
    inline void setPosition(const CCPoint& position)
    {
        m_position = position;
    }
    
    inline const CCPoint& getPosition()
    {
        return m_position;
    }
    
    inline void setPreviousPosition(const CCPoint& previousPosition)
    {
        m_previousPosition = previousPosition;
    }
    
    inline const CCPoint& getPreviousPosition()
    {
        return m_previousPosition;
    }
    
    inline void setWalkVelocity(const CCPoint& walkVelocity)
    {
        m_walkVelocity = walkVelocity;
    }
    
    inline const CCPoint& getWalkVelocity()
    {
        return m_walkVelocity;
    }
    
    inline void setKnockupTime(float knockupTime)
    {
        m_knockupTime = knockupTime;
    }
    
    inline float getKnockupTime()
    {
        return m_knockupTime;
    }
    
    inline void setKnockupVelocity(const CCPoint& knockupVelocity)
    {
        m_knockupVelocity = knockupVelocity;
    }
    
    inline const CCPoint& getKnockupVelocity()
    {
        return m_knockupVelocity;
    }
    
    inline void setVelocity(const CCPoint& velocity)
    {
        m_velocity = velocity;
    }
    
    inline const CCPoint& getVelocity()
    {
        return m_velocity;
    }
    
    inline void setDirection(int direction)
    {
        m_direction = direction;
    }
    
    inline int getDirection()
    {
        return m_direction;
    }
    
protected:
    CCPoint m_position;
    CCPoint m_previousPosition;
    CCPoint m_walkVelocity;
    float m_knockupTime;
    CCPoint m_knockupVelocity;
    
    CCPoint m_velocity;
    //移动方向。正值朝右，负值朝左
    int m_direction;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_MOVEPROPERTY_H_
