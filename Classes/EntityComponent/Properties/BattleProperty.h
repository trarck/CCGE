#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BattleProperty : public yhge::Property
{
public:
    
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

protected:
    int m_row;
    int m_col;
    int m_side;

};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BattleProperty_H_
