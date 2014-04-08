#include "HurtComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

HurtComponent::HurtComponent()
:m_rendererComponent(NULL)
,Component("HurtComponent")
{
    
}

HurtComponent::~HurtComponent()
{
}

void HurtComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
    
}

void HurtComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool HurtComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGAttackDamage, NULL,
                                         message_selector(HurtComponent::onAttackDamage),this);
        
        return true;
    }
    return false;
}

void HurtComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), kMSGAttackDamage, m_owner);
    
    Component::cleanupMessages();
}

void HurtComponent::onAttackDamage(yhge::Message* message)
{
    
    CCInteger* damageValue=static_cast<CCInteger*>(message->getData());
    if (damageValue) {
        
        CCString* damageString=CCString::createWithFormat("-%d",damageValue->getValue());
        
        //show damage tip
        CCLabelBMFont* label=CCLabelBMFont::create(damageString->getCString(), "fonts/Red_36.fnt");
        
        CCSize size=m_rendererComponent->getRenderer()->getContentSize();
        CCPoint pos=m_rendererComponent->getRenderer()->getPosition();
        
//        CCLog("tt:%f,%f aa:%f,%f",pos.x,pos.y,m_rendererComponent->getRenderer()->getPosition().x,m_rendererComponent->getRenderer()->getPosition().y);
        
        label->setPosition(ccp(pos.x,pos.y+size.height+50));
        
//        label->setScale(0.8);
        
        //action
        CCAction* effect=CCSequence::createWithTwoActions(CCMoveBy::create(0.4f, ccp(0,40.0f)), CCRemoveSelf::create());
        
        //TODO 添加到场境的前层
        m_rendererComponent->getRenderer()->getParent()->addChild(label,1000);
        
        label->runAction(effect);
    }
}


NS_CC_GE_END

