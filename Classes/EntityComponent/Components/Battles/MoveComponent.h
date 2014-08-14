#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "../GameComponent.h"


NS_CC_GE_BEGIN

/**
 * 移动组件
 * 处理单位移动逻辑
 */
class MoveComponent : public GameComponent
{
public:
    
    MoveComponent();
    
    ~MoveComponent();
    
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
        
    virtual void moveTo(const CCPoint& dest);
    
    virtual void stopMove();
    
protected:
    
    bool m_moveable;
    
    CCPoint m_direction;

};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_
