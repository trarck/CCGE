#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "SimplePositionComponent.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * 移动组件
 * 处理单位移动逻辑
 */
class MoveComponent : public yhge::Component
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
    
public:
    
    inline void setWalkVelocity(const CCPoint& walkVelocity)
    {
        m_walkVelocity = walkVelocity;
    }
    
    inline const CCPoint& getWalkVelocity()
    {
        return m_walkVelocity;
    }
    
    inline void setKnockupVelocity(const CCPoint& knockupVelocity)
    {
        m_knockupVelocity = knockupVelocity;
    }
    
    inline const CCPoint& getKnockupVelocity()
    {
        return m_knockupVelocity;
    }
    
protected:
    
    //移动速度
    CCPoint m_walkVelocity;
    
    //击退速度。有些技能有击退功能
    CCPoint m_knockupVelocity;
    
    SimplePositionComponent* m_positionComponent;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_MOVECOMPONENT_H_
