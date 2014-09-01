
#ifndef CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "BaseState.h"

#include "EntityComponent/Components/Battles/SkillComponent.h"

NS_CC_GE_BEGIN

class UnitState:public BaseState
{
public:
    
    enum UnitStateType
    {
        kIdleState,
        kWalkState,
        kAttackState,
        kHurtState,
        kDeadState,
        kBirthState,
        kDyingState
    };
    
    UnitState();
    
    ~UnitState();
    
    virtual void update(float delta);
    
public:
    
    void setTarget(GameEntity* target);
    
    inline GameEntity* getTarget()
    {
        return m_target;
    }
    
protected:
    
    void setUnitAction(const std::string& action);
    
    GameEntity* searchTarget();
    
    SkillComponent* findSkillToCast();  
    
    void walkTo(GameEntity* dest);
    
    void walkTo(const CCPoint& dest);
    
protected:
    
    GameEntity* m_target;
    
};

/**
 * 空闲状态
 * 当处于空闲状态的时候会去寻找目标
 */
class UnitIdleState:public UnitState
{
public:

    UnitIdleState()
    {
        m_type=kIdleState;
    }
    
    virtual void enter();
    virtual void exit();
	virtual void update(float delta);
    virtual void onMessage(yhge::Message* message);
    virtual void onHurt(yhge::Message* message);

};

/**
 * 移动状态
 */
class UnitWalkState:public UnitState
{
public:
    
    UnitWalkState()
    {
        m_type=kWalkState;
    }
  
    virtual void enter();
    virtual void exit();
    
    inline void setDest(const CCPoint& dest)
    {
        m_dest = dest;
    }
    
    inline const CCPoint& getDest()
    {
        return m_dest;
    }
    
protected:

    CCPoint m_dest;

};

/**
 * 攻击状态
 */
class UnitAttackState:public UnitState
{
public:
    
    UnitAttackState()
    :m_skill(NULL)
    {
        m_type=kAttackState;
    }
    
    ~UnitAttackState()
    {
        CC_SAFE_RELEASE_NULL(m_skill);
    }
    
    virtual void enter();
    
    virtual void exit();

public:
    
    inline void setSkill(SkillComponent* skill)
    {
        CC_SAFE_RETAIN(skill);
        CC_SAFE_RELEASE(m_skill);
        m_skill = skill;
    }
    
    inline SkillComponent* getSkill()
    {
        return m_skill;
    }
    
protected:
    SkillComponent* m_skill;
    
};

/**
 * 被攻击状态
 */
class UnitHurtState:public UnitState
{
public:
    
    UnitHurtState()
    {
        m_type=kHurtState;
    }
    
    virtual void enter();
    
    virtual void exit();
};

/**
 * 死亡状态
 */
class UnitDeadState:public UnitState
{
public:
    UnitDeadState()
    {
        m_type=kDeadState;
    }
    
    virtual void enter();
    
    virtual void exit();
};

/**
 * 重生状态
 */
class UnitBirthState:public UnitState
{
public:

    UnitBirthState()
    {
        m_type=kBirthState;
    }
    
    virtual void enter();
    
    virtual void exit();
};

/**
 * 再在死亡状态
 */
class UnitDyingState:public UnitState
{
public:
    
    UnitDyingState()
    {
        m_type=kDyingState;
    }
    
    virtual void enter();
    
    virtual void exit();
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_
