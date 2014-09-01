#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATEMACHINECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATEMACHINECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 状态机组件
 * 实现一个状态管理器，而这个状态管理器其实就是AI.
 * 每个状态其实就是一个AI的一部分，实现相应的逻辑。也就是说状态机组件和AI组件只能存在一个。
 * AI组件使用state变量来控制游戏对象的行为，而状态机使用状态对象来控制游戏对象行为。
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
