
#ifndef CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "BaseState.h"

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
    
//    virtual void enter();
//    
//    virtual void exit();
    
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
    
protected:
    
    void showIdleAnimation();
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
	virtual void update(float delta);
    
protected:


};

/**
 * 攻击状态
 */
class UnitAttackState:public UnitState
{
public:
    
    UnitAttackState()
    {
        m_type=kAttackState;
    }
    
    virtual void enter();
    
    virtual void exit();

    virtual void onAttackAnimationComplete(yhge::Message* message);
    
    //是否可以被普通攻击.正在普通攻击中不能被攻击。
    virtual bool isAttackable();
    
    //是否被普通攻击伤害.攻击中不受伤害。
    virtual bool isNormalDamageable();
    
protected:
    
    void showAttackAnimation();
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
    
protected:
    
    void showHurtAnimation();

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
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_UNITSTATE_H_
