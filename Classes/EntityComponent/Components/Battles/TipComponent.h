#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_TIPCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_TIPCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 战斗提示组件
 * 伤害的数值，状态的提示
 */
class TipComponent : public yhge::Component
{
public:
    
    TipComponent();
    
    ~TipComponent();
    
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
    
public:
    
    inline void setContainer(CCNode* container)
    {
        CC_SAFE_RETAIN(container);
        CC_SAFE_RELEASE(m_container);
        m_container = container;
    }
    
    inline CCNode* getContainer()
    {
        return m_container;
    }
    
protected:
    //tip显示的容器
    CCNode* m_container;
    //保存对显示组件的引用
    yhge::SpriteRendererComponent* m_rendererComponent;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_TIPCOMPONENT_H_
