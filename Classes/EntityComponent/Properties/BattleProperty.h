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
    :m_side(0)
    ,m_scale(1.0f)
    ,m_x(0.0f)
    ,m_y(0.0f)
    ,m_camp(0)
    ,m_alive(true)
    {
        
    }
    
    inline void setSide(int side)
    {
        m_side = side;
    }
    
    inline int getSide()
    {
        return m_side;
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
        m_x = x;
    }
    
    inline float getX()
    {
        return m_x;
    }
    
    inline void setY(float y)
    {
        m_y = y;
    }
    
    inline float getY()
    {
        return m_y;
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

protected:

    int m_side;
    
    //缩放
    float m_scale;

    //坐标
    float m_x;
    float m_y;
    
    //阵营
    int m_camp;
    
    //是否活着
    bool m_alive;
    
    
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
