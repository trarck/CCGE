#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BATTLEPOSITIONCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BATTLEPOSITIONCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 位置组件
 * 主要处理地图位置到屏幕位置的转换
 */
class BattlePositionComponent : public yhge::Component
{
public:
    
    BattlePositionComponent();
    
    ~BattlePositionComponent();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    CCPoint getPositionFromProperty();
    
    CCPoint getPositionFromCell();
    
    void updateRendererPosition();
    
    void onUpdatePosition(yhge::Message* message);
    
protected:
    
    //保存对显示组件的引用
    yhge::SpriteRendererComponent* m_rendererComponent;
    
    CCPoint m_rendererPosition;
    
    float m_lastCol;
    float m_lastRow;
    
    float m_lastX;
    
    float m_lastY;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BATTLEPOSITIONCOMPONENT_H_
