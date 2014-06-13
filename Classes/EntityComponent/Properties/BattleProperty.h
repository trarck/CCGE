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
    {
        
    }
    
    inline void setRow(int row)
    {
        m_row = row;
    }
    
    inline int getRow()
    {
        return m_row;
    }
    
    inline void setCol(int col)
    {
        m_col = col;
    }
    
    inline int getCol()
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
    
    inline void setScale(float scale)
    {
        m_scale = scale;
    }
    
    inline float getScale()
    {
        return m_scale;
    }

protected:
    
    int m_row;
    int m_col;
    int m_side;

    float m_x;
    float m_y;
    
    float m_scale;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
