#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * AI组件
 * 处理自动战斗逻辑
 */
class AIComponent : public yhge::Component
{
public:
    
    AIComponent();
    
    ~AIComponent();
    
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
    
    virtual void update(float delta);
    
protected:
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_