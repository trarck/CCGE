#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "MoveComponent.h"
#include "EntityComponent/Properties/BattleProperty.h"
#include "EntityComponent/Properties/UnitProperty.h"
#include "EntityComponent/Properties/MoveProperty.h"
#include "EntityComponent/Components/GameComponent.h"
#include "SkillComponent.h"

NS_CC_GE_BEGIN

/**
 * AI组件
 * 处理自动战斗逻辑
 */
class AIComponent : public GameComponent
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
    
    SkillComponent* findSkillToCast();
    
    void walkTo(GameEntity* dest);
    
    void walkTo(const CCPoint& dest);
    
    void walkStop();
    
public:
    
    inline void setWillCastManualSkill(bool willCastManualSkill)
    {
        m_willCastManualSkill = willCastManualSkill;
    }
    
    inline bool isWillCastManualSkill()
    {
        return m_willCastManualSkill;
    }
    
    void setTarget(GameEntity* target);
    
    inline GameEntity* getTarget()
    {
        return m_target;
    }
    
//    void setDestination(GameEntity* destination);
//    
//    inline GameEntity* getDestination()
//    {
//        return m_destination;
//    }
    
protected:
    
    int m_state;
    
    bool m_willCastManualSkill;
    
    GameEntity* m_target;
    
    UnitProperty* m_unitProperty;
    MoveProperty* m_moveProperty;
    
    MoveComponent* m_moveComponent;
    
    float m_temp;

};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_AICOMPONENT_H_
