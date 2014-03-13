#include "DieComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

DieComponent::DieComponent()
:m_rendererComponent(NULL)
,Component("DieComponent")
{
    
}

DieComponent::~DieComponent()
{

}

void DieComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void DieComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool DieComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(DieComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void DieComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void DieComponent::onEntityDie(yhge::Message* message)
{
    CCLOGINFO("DieComponent::onEntityDie");
    
    CCFadeOut* fadeOut= CCFadeOut::create(0.6f);
    
    CCFiniteTimeAction* action=CCSequence::createWithTwoActions(fadeOut, CCCallFunc::create(this, callfunc_selector(DieComponent::onEntityDisappear)));
    m_rendererComponent->getRenderer()->runAction(action);
}

void DieComponent::onEntityDisappear()
{
    m_rendererComponent->getRenderer()->removeFromParent();
}

NS_CC_GE_END

