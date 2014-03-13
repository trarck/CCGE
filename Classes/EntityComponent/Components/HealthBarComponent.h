#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_HEALTHBARCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_HEALTHBARCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

class HealthBar:public CCNode
{
public:
    
    HealthBar();
    
    void draw();
    
public:
    
    inline void setMaxValue(float maxValue)
    {
        m_maxValue = maxValue;
    }
    
    inline float getMaxValue()
    {
        return m_maxValue;
    }
    
    inline void setCurrentValue(float currentValue)
    {
        m_currentValue = currentValue;
    }
    
    inline float getCurrentValue()
    {
        return m_currentValue;
    }

protected:
    
    float m_maxValue;
    
    float m_currentValue;

};

/**
 * 血条组件
 */
class HealthBarComponent : public yhge::Component
{
public:
    
    HealthBarComponent();
    
    ~HealthBarComponent();
    
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
    
    void setMaxHp(float maxHp);
    
    void setCurrentHp(float hp);
    
    void onHealthChange(yhge::Message* message);
    
    inline void setHealthBar(HealthBar* healthBar)
    {
        CC_SAFE_RETAIN(healthBar);
        CC_SAFE_RELEASE(m_healthBar);
        m_healthBar = healthBar;
    }
    
    inline HealthBar* getHealthBar()
    {
        return m_healthBar;
    }
    
protected:
    
    //保存对显示组件的引用
    yhge::RendererComponent* m_rendererComponent;
    
    HealthBar* m_healthBar;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_HEALTHBARCOMPONENT_H_
