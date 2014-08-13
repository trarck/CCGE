#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "MoveComponent.h"
#include "EntityComponent/Properties/BattleProperty.h"


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
    
    GameEntity* searchTarget();
    
    void walkTo(GameEntity* dest);
    
    void walkTo(const CCPoint& dest);
    
    void walkStop();
    
public:
    
    void setTarget(GameEntity* target);
    
    inline GameEntity* getTarget()
    {
        return m_target;
    }
    
    void setDestination(GameEntity* destination);
    
    inline GameEntity* getDestination()
    {
        return m_destination;
    }
    
protected:
    
    int m_state;
    
    GameEntity* m_target;
    
    GameEntity* m_destination;
    
    MoveComponent* m_moveComponent;
    
    float m_temp;

};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_
