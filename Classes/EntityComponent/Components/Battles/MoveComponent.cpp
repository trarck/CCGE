#include "MoveComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MoveComponent::MoveComponent()
:Component("MoveComponent")
,m_positionComponent(NULL)
,m_walkVelocity(CCPointZero)
,m_knockupVelocity(CCPointZero)
{
    
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::setup()
{
    Component::setup();

    m_positionComponent=static_cast<SimplePositionComponent*>(m_owner->getComponent("PositionComponent"));
}

void MoveComponent::cleanup()
{
    Component::cleanup();
    m_positionComponent=NULL;
}

bool MoveComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(MoveComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void MoveComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void MoveComponent::update(float delta)
{
    CCLOG("MoveComponent::update:%d,%f",this,delta);
    CCPoint pos=m_positionComponent->getPosition();

    pos.x+=(m_walkVelocity.x+m_knockupVelocity.x)*delta;
    pos.y+=(m_walkVelocity.y+m_knockupVelocity.y)*delta;

    m_positionComponent->setPosition(pos);

}

NS_CC_GE_END

