#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 战斗时间线组件
 * 用于不需要显示人物的时间线。直接使用间隔时间做定时器的更新时间。
 */
class BattleTimelineComponent : public yhge::Component
{
public:
    
    BattleTimelineComponent();
    
    ~BattleTimelineComponent();
    
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
     * 开始攻击定时器
     */
    void startAttackSchedule();
    
    /**
     * 停止攻击定时器
     */
    void stopAttackSchedule();
    
    void attackUpdate(float delta);
    
    void onAttackStart(yhge::Message* message);
    
    void onAttackStop(yhge::Message* message);
    
public:
    
    inline void setAttackSpeed(float attackSpeed)
    {
        CCAssert(attackSpeed!=0, "setAttackSpeed attack speed must big then zero");
        m_attackSpeed = attackSpeed;
        m_attackDuration=1/m_attackSpeed;
    }
    
    inline float getAttackSpeed()
    {
        return m_attackSpeed;
    }
    
protected:
    
    //保存对显示组件的引用
    yhge::RendererComponent* m_rendererComponent;
    
    float m_attackSpeed;
    
    float m_attackDuration;
    
    bool m_attackScheduleStarted;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BattleTimelineComponent_H_
