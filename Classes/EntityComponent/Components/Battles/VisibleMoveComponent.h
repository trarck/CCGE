#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "../GameComponent.h"
#include "EntityComponent/Properties/MoveProperty.h"

NS_CC_GE_BEGIN

/**
 * 移动组件
 * 处理单位移动逻辑
 */
class VisibleMoveComponent : public GameComponent
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
    
    inline void setVelocity(const CCPoint& velocity)
    {
        m_velocity = velocity;
    }
    
    inline const CCPoint& getVelocity()
    {
        return m_velocity;
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
    CCPoint m_velocity;
    
    CCPoint m_position;
    
    int m_tick;
    
    bool m_moving;
    
    int m_direction;
    
    MoveProperty* m_moveProperty;
    
    yhge::SpriteRendererComponent* m_rendererComponent;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_VisibleMOVECOMPONENT_H_
