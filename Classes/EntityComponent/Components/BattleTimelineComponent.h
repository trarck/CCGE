#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 战斗时间线组件
 */
class BattleTimelineComponent : public yhge::Component
{
public:
    
    BattleTimelineComponent();
    
    ~BattleTimelineComponent();
    
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
    
    void onAttackDamage(yhge::Message* message);
    
    
protected:
    
    //保存对显示组件的引用
    yhge::RendererComponent* m_rendererComponent;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_
