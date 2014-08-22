
#ifndef CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

class BaseState:public yhge::FSMState
{
public:
    
	BaseState();
    
	~BaseState();
    
public:
    
    inline void setGameEntity(GameEntity* gameEntity)
    {
        m_gameEntity = gameEntity;
    }
    
    inline GameEntity* getGameEntity()
    {
        return m_gameEntity;
    }
        
protected:
    //对GameEntity的弱引用
    GameEntity* m_gameEntity;
    
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_
