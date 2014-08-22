#include "BaseState.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BaseState::BaseState()
:m_gameEntity(NULL)
{
    
}

BaseState::~BaseState()
{
    CCLOG("BaseState destroy");
}

NS_CC_GE_END
