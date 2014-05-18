
#ifndef CCGE_ENTITYCOMPONENT_STATES_BATTLESTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_BATTLESTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "BaseState.h"

NS_CC_GE_BEGIN

class BattleState:public BaseState
{
public:
    
//	BattleState();
//    
//	~BattleState();
    
    enum BattleStateType
    {
        kIdleState,
        kMoveState,
        kAttackState,
        kBeAttackState,
        kPrepareSkillState,
        kFireSkillState
    };
    
    virtual void enter();
    
    virtual void exit();
    
    //是否可以被普通攻击.如果允许移动，那么移动出去攻击别人就不能被攻击。
    virtual bool isAttackable();
    
    //是否可以被技能攻击
    virtual bool isSkillAttackable();
    
    //是否被普通攻击伤害.如果人物不在原来的位置，那么普通攻击伤害。
    virtual bool isNormalDamageable();
    
    virtual void onAttack(yhge::Message* message);
};

/**
 * 空闲状态
 */
class BattleIdleState:public BattleState
{
public:

    virtual void enter();
    virtual void exit();
	virtual void update(float delta);
    virtual void onMessage(yhge::Message* message);
//    virtual void onAttack(yhge::Message* message);
    virtual void onBeAttack(yhge::Message* message);
    
protected:
    
    void showIdleAnimation();
};

/**
 * 移动状态
 */
class BattleMoveState:public BattleState
{
public:
    
    enum MoveType
    {
        kMoveToTarget,
        kMoveBack
    };
    
    BattleMoveState()
    :m_moveType(kMoveToTarget)
    {
        
    }
  
    virtual void enter();
    virtual void exit();
	virtual void update(float delta);
    
    virtual void onMoveComplete(yhge::Message* message);

    //是否可以被普通攻击.移动中不能被攻击
    virtual bool isAttackable();
    
    //是否被普通攻击伤害.移动中不受伤害。
    virtual bool isNormalDamageable();
    
    inline void setMoveType(int moveType)
    {
        m_moveType = moveType;
    }
    
    inline int getMoveType()
    {
        return m_moveType;
    }
    
protected:
    int m_moveType;

};

/**
 * 攻击状态
 */
class BattleAttackState:public BattleState
{
public:
    
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
class BattleBeAttackState:public BattleState
{
public:
    
    virtual void enter();
    
    virtual void exit();
    
    virtual void onBeAttackFinish(yhge::Message* message);
    
protected:
    
    void showBeAttackAnimation();

};

/**
 * 释放技能的吟唱阶段
 */
class BattlePrepareSkillkState:public BattleState
{
public:
    
};

/**
 * 释放技能的施放阶段
 * 有些技能会施放一段时间，有些怪施放一次。
 */
class BattleFireSkillkState:public BattleState
{
public:

};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_BATTLESTATE_H_
