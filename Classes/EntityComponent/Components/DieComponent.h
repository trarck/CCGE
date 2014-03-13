#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_DIECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_DIECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

//TODO 加入死亡动画，现在是一个渐隐效果。
class DieComponent : public yhge::Component
{
public:
    
    DieComponent();
    
    ~DieComponent();
    
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
    
    void onEntityDie(yhge::Message* message);
    
    void onEntityDisappear();
    
protected:
    
    //保存对显示组件的引用
    yhge::RendererComponent* m_rendererComponent;
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_DIECOMPONENT_H_
