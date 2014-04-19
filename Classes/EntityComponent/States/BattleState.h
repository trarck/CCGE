
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
    virtual void onAttack(yhge::Message* message);
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
