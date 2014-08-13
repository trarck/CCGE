#include "GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameEntity::GameEntity()
:m_rendererComponent(NULL)
,m_isoPositionComponent(NULL)
,m_attackComponent(NULL)
,m_unitProperty(NULL)
,m_battleProperty(NULL)
,m_healthBarComponent(NULL)
,m_battlePositionComponent(NULL)
,m_battleStateMachineComponent(NULL)
{
    CCLOG("GameEntity create[%d]",m_uID);
}

GameEntity::~GameEntity()
{
    CCLOG("GameEntity destroy[%d]",m_uID);
}

NS_CC_GE_END
