#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SIMPLEPOSITIONCOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SIMPLEPOSITIONCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/Properties/BattleProperty.h"

NS_CC_GE_BEGIN

/**
 * 位置组件
 * 主要处理地图位置到屏幕位置的转换
 */
class SimplePositionComponent : public yhge::Component
{
public:
    
    SimplePositionComponent();
    
    ~SimplePositionComponent();
    
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
    
    CCPoint getPositionFromProperty();
    
    void setPosition(const CCPoint & pos);
    
    void setPosition(float x,float y);
    
    CCPoint getPosition();
    
    void updateRendererPosition();
    
    void onUpdatePosition(yhge::Message* message);
    
protected:
    
    //保存对显示组件的引用
    yhge::SpriteRendererComponent* m_rendererComponent;
    
    BattleProperty* m_battleProperty;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_SIMPLEPOSITIONCOMPONENT_H_
