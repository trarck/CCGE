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
    :m_col(0)
    ,m_row(0)
    ,m_side(0)
    ,m_scale(1.0f)
    ,m_x(0)
    ,m_y(0)
    {
        
    }
    
    inline void setRow(float row)
    {
        m_row = row;
    }
    
    inline float getRow()
    {
        return m_row;
    }
    
    inline void setCol(float col)
    {
        m_col = col;
    }
    
    inline float getCol()
    {
        return m_col;
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

protected:
    
    float m_row;
    float m_col;
    int m_side;

    float m_scale;
    
    float m_x;
    float m_y;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
