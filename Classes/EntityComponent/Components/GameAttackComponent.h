#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameAttackComponent : public yhge::AttackComponent
{
public:
    
    GameAttackComponent();
    ~GameAttackComponent();
    
//    virtual bool init();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    /**
     * 攻击
     */
    virtual void attack();
    
    /**
     * 使用技能攻击
     */
    virtual void attackWithSkillId(int skillId);

    /**
     * 处理攻击消息
     */
    virtual void onAttack(yhge::Message *message);
    
    /**
     * 处理设置目标消息
     */
    virtual void onSetAttackTarget(yhge::Message *message);
    
    /**
     * 处理目标死亡消息
     */
    virtual void onTargetDie(yhge::Message *message);
    
public:
    
    
protected:
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_
