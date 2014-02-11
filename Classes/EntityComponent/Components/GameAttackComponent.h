#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/Properties/UnitProperty.h"

NS_CC_GE_BEGIN

class GameEntity;

class GameAttackComponent : public yhge::AttackComponent
{
public:
    
    GameAttackComponent();
    ~GameAttackComponent();
    
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
    
    /**
     * 攻击
     */
    virtual void attack();
    
    /**
     * 使用技能攻击
     */
    virtual void attackWithSkillId(int skillId);

    /**
     * 处理目标伤害
     */
    void parseTargetDamage();
    
    /**
     * 计算伤害值
     * 公式是固定的
     */
    int calcDamage(UnitProperty* targetUnitProperty);

    inline void setDamageFormulaParameterOne(float damageFormulaParameterOne)
    {
        m_damageFormulaParameterOne = damageFormulaParameterOne;
    }
    
    inline float getDamageFormulaParameterOne()
    {
        return m_damageFormulaParameterOne;
    }
    
protected:
    
    yhge::AnimationComponent* m_animationComponent;
    
    float m_damageFormulaParameterOne;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_
