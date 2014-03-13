#include "HealthBarComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

HealthBar::HealthBar()
:m_currentValue(1)
,m_maxValue(1)
{
    
}

void HealthBar::draw()
{
    float currentWidth=kBarWidth*m_currentValue/m_maxValue;
    
    ccDrawSolidRect(CCPointZero, ccp(currentWidth,kBarHeight), ccc4f(1.0, 0, 0, 1.0));
    ccDrawColor4F(1.0, 0, 0, 1.0);
    ccDrawRect(CCPointZero, ccp(kBarWidth,kBarHeight));
}

HealthBarComponent::HealthBarComponent()
:m_rendererComponent(NULL)
,Component("HealthBarComponent")
,m_healthBar(NULL)
{
    
}

HealthBarComponent::~HealthBarComponent()
{
    CC_SAFE_RELEASE_NULL(m_healthBar);
}

void HealthBarComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
    
    m_healthBar=new HealthBar();
    m_healthBar->init();
    
    m_rendererComponent->getRenderer()->addChild(m_healthBar);
}

void HealthBarComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool HealthBarComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(
                                         messageManager->getGlobalObject(), kMSGEntityHealthChange, m_owner,
                                         message_selector(HealthBarComponent::onHealthChange),this);
        
        return true;
    }
    return false;
}

void HealthBarComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), kMSGEntityHealthChange, m_owner);
    
    Component::cleanupMessages();
}

void HealthBarComponent::setMaxHp(float maxHp)
{
    m_healthBar->setMaxValue(maxHp);
}

void HealthBarComponent::setCurrentHp(float hp)
{
    m_healthBar->setCurrentValue(hp);
}

void HealthBarComponent::onHealthChange(yhge::Message* message)
{
    CCLOGINFO("HealthBarComponent::onHealthChange");
    
    CCFloat* currentHpValue=static_cast<CCFloat*>(message->getData());
    if (currentHpValue) {
        m_healthBar->setCurrentValue(currentHpValue->getValue());
    }
}


NS_CC_GE_END

