
#ifndef CCGE_ENTITYCOMPONENT_STATES_ENTITYSTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_ENTITYSTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "BaseState.h"

NS_CC_GE_BEGIN

class EntityState:public BaseState
{
public:
    
	EntityState();
    
	~EntityState();
    
};


class EntityIdleState:public BaseState
{
public:
    
	EntityIdleState();
    
	~EntityIdleState();
    
};

class EntityAttackState:public BaseState
{
public:
    
	EntityAttackState();
    
	~EntityAttackState();
    
};

class EntityBeAttackState:public BaseState
{
public:
    
	EntityBeAttackState();
    
	~EntityBeAttackState();
    
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_ENTITYSTATE_H_
