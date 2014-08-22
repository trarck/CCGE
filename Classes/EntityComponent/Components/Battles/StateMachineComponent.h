#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATEMACHINECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATEMACHINECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 战斗状态组件
 * 实现一个状态管理器
 */
class StateMachineComponent : public yhge::Component
{
public:
    
    StateMachineComponent();
    
    ~StateMachineComponent();
    
    bool init();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
        
    /**
     * 设置战斗中用到的状态
     */
    void setupStates();
    
public:
    
    inline void setFSMMachine(yhge::FSMMachine* fSMMachine)
    {
        CC_SAFE_RETAIN(fSMMachine);
        CC_SAFE_RELEASE(m_fSMMachine);
        m_fSMMachine = fSMMachine;
    }
    
    inline yhge::FSMMachine* getFSMMachine()
    {
        return m_fSMMachine;
    }
    
protected:
    
    yhge::FSMMachine* m_fSMMachine;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATEMACHINECOMPONENT_H_
