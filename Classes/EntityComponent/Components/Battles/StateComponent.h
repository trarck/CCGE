#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/Properties/UnitProperty.h"
#include "EntityComponent/Properties/MoveProperty.h"

#include "GameComponent.h"

NS_CC_GE_BEGIN

class SkillComponent;

/**
 * 状态组件
 */
class StateComponent : public GameComponent
{
public:
    
    StateComponent();
    
    ~StateComponent();
    
    bool init();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();

    void idle();
    
    void walk(const CCPoint& dest);
    
    void castSkill(SkillComponent* skill,GameEntity* target);
    
    void castManualSkill();
    
    void die(GameEntity* killer);
    
    void hurt();
    
protected:
    
    void setAction(const std::string& name);
    
protected:
    
    UnitProperty* m_unitProperty;
    MoveProperty* m_moveProperty;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_STATECOMPONENT_H_
