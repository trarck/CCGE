#include "BuffComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BuffComponent::BuffComponent()
:Component("BuffComponent")
{
    
}

BuffComponent::~BuffComponent()
{

}

void BuffComponent::setup()
{
    Component::setup();

}

void BuffComponent::cleanup()
{
    Component::cleanup();
}

bool BuffComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(BuffComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void BuffComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void BuffComponent::update(float delta)
{
    
}

NS_CC_GE_END

