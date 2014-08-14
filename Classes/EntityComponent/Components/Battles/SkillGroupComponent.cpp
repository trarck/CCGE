#include "SkillComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

SkillComponent::SkillComponent()
:Component("SkillComponent")
{
    
}

SkillComponent::~SkillComponent()
{

}

void SkillComponent::setup()
{
    Component::setup();

}

void SkillComponent::cleanup()
{
    Component::cleanup();
}

bool SkillComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(SkillComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void SkillComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void SkillComponent::update(float delta)
{
    
}

NS_CC_GE_END

