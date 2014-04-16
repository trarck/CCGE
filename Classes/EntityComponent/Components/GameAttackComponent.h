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
     * 普通攻击
     */
    virtual void attack();
    
    /**
     * 使用技能攻击
     */
    virtual void attackWithSkillId(int skillId);
    
    /**
     * @brief 移动到攻击目标的前面
     */
    void moveToTargetFront();
    
    /**
     * @brief 回到原来的位置
     */
    void moveBackOrigin();
    
    /**
     * 处理目标伤害
     */
    void parseTargetDamage();
    
    /**
     * 计算伤害值
     * 公式是固定的
     */
    int calcDamage(UnitProperty* targetUnitProperty);

    /**
     * @brief 移动到目录前面结束
     */
    void onMoveToTargetFrontComplete();
    
    /**
     * @brief 移动到原来位置结束
     */
    void onMoveBackOriginComplete();
    
    /**
     * @brief 普通攻击动画完成
     */
    void onAttackAnimationComplete(yhge::Message* message);
    
protected:
    
    /**
     * @brief 显示攻击动画
     */
    void showAttackAnimation();
    
    /**
     * @brief 显示空闲动画
     */
    void showIdleAnimation();
    
public:

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
    
    yhge::RendererComponent* m_rendererComponent;
    
    float m_damageFormulaParameterOne;
    
    CCPoint m_originalPosition;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_GAMEATTACKCOMPONENT_H_
