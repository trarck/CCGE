#include "GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameEntity::GameEntity()
:m_rendererComponent(NULL)
{
    CCLOG("GameEntity create[%d]",m_uID);
}

GameEntity::~GameEntity()
{
    CCLOG("GameEntity destroy[%d]",m_uID);
}

NS_CC_GE_END
