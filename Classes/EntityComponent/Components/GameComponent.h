#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_GAMECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_GAMECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class GameEntity;

/**
 * 游戏基础组件
 */
class GameComponent : public yhge::Component
{
public:
    
    GameComponent();
    
    GameComponent(const std::string& name);
    
    ~GameComponent();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();    
    
protected:
    
    GameEntity* m_entityOwner;
    
    //TODO add engine weak ref
    
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_GAMECOMPONENT_H_
