#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * 技能组件
 * 1.为了简单把普通攻击也做为技能攻击
 * 2.技能的伤害:物理伤害,魔法伤害，神圣伤害
 */
class SkillComponent : public yhge::Component
{
public:
    
    SkillComponent();
    
    ~SkillComponent();
    
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
    
protected:
    
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SKILLCOMPONENT_H_
