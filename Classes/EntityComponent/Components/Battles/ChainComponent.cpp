#include "ChainComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

ChainComponent::ChainComponent()
:Component("ChainComponent")
{
    
}

ChainComponent::~ChainComponent()
{

}

void ChainComponent::setup()
{
    Component::setup();

}

void ChainComponent::cleanup()
{
    Component::cleanup();
}

bool ChainComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(ChainComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void ChainComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void ChainComponent::update(float delta)
{
    
}

NS_CC_GE_END

