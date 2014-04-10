#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLEPOSITIONCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLEPOSITIONCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 伤害组件
 * 主要显示伤害的数值
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
    
    void updateRendererPosition();
    
    void onUpdatePosition(yhge::Message* message);
    
protected:
    
    //保存对显示组件的引用
    yhge::SpriteRendererComponent* m_rendererComponent;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLEPOSITIONCOMPONENT_H_
