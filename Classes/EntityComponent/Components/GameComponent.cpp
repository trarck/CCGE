#include "GameComponent.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameComponent::GameComponent()
:m_entityOwner(NULL)
{
    
}

GameComponent::GameComponent(const std::string& name)
:Component(name)
,m_entityOwner(NULL)
{
    
}

GameComponent::~GameComponent()
{
}

void GameComponent::setup()
{
    Component::setup();
    m_entityOwner=static_cast<GameEntity*>(m_owner);
}

void GameComponent::cleanup()
{
    m_entityOwner=NULL;
    Component::cleanup();
}
NS_CC_GE_END

