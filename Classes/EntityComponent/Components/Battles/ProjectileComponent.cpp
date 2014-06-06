#include "ProjectileComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

ProjectileComponent::ProjectileComponent()
:Component("ProjectileComponent")
{
    
}

ProjectileComponent::~ProjectileComponent()
{

}

void ProjectileComponent::setup()
{
    Component::setup();

}

void ProjectileComponent::cleanup()
{
    Component::cleanup();
}

bool ProjectileComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(ProjectileComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void ProjectileComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void ProjectileComponent::update(float delta)
{
    
}

NS_CC_GE_END
