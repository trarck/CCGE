#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "MoveComponent.h"
#include "EntityComponent/Properties/UnitProperty.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * 移动组件
 * 处理单位移动逻辑
 */
class VisibleMoveComponent : public yhge::Component
{
public:
    
    VisibleMoveComponent();
    
    ~VisibleMoveComponent();
    
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
        
    virtual void startMove();
    
    virtual void stopMove();
    
    void onMoveTo(yhge::Message* message);
    
    void onMoveStop(yhge::Message* message);
    
public:
    
    inline void setWalkVelocity(const CCPoint& walkVelocity)
    {
        m_walkVelocity = walkVelocity;
    }
    
    inline const CCPoint& getWalkVelocity()
    {
        return m_walkVelocity;
    }
    
    inline void setPosition(const CCPoint& position)
    {
        m_position = position;
    }
    
    inline const CCPoint& getPosition()
    {
        return m_position;
    }
    
protected:
    void syncProperty();
    
protected:
    
    //移动速度
    CCPoint m_walkVelocity;
    
    CCPoint m_position;
    
    int m_tick;
    
    bool m_moving;
    
    BattleProperty* m_battleProperty;
    
    UnitProperty* m_unitProperty;
    
    MoveComponent* m_moveComponent;
    yhge::SpriteRendererComponent* m_rendererComponent;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_
