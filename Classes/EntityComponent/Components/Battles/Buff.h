#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BUFFCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BUFFCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * buff组件
 *
 */
class BuffComponent : public yhge::Component
{
public:
    
    BuffComponent();
    
    ~BuffComponent();
    
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
    
    void apply();
    
    void applyEffect(const std::string& effect);
    
    void applyEffect(int effectType);
    
    static bool checkAddBuff(const yhge::Json::Value& buffInfo,int level,GameEntity* target);
    
public:
    
    inline void setInfo(const yhge::Json::Value& info)
    {
        m_info = info;
    }
    
    inline const yhge::Json::Value& getInfo()
    {
        return m_info;
    }
    
protected:
    
    yhge::Json::Value m_info;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_BUFFCOMPONENT_H_
