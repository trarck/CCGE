
#ifndef CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_
#define CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BaseState:public yhge::FSMState
{
public:
    
	BaseState();
    
	~BaseState();
        
private:

};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_STATES_BASESTATE_H_
