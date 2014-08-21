#include "TipComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

TipComponent::TipComponent()
:Component("TipComponent")
,m_container(NULL)
,m_rendererComponent(NULL)

{
    
}

TipComponent::~TipComponent()
{
    CC_SAFE_RELEASE_NULL(m_container);
}

void TipComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void TipComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool TipComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGAttackDamage, NULL,
                                         message_selector(TipComponent::onAttackDamage),this);
        
        return true;
    }
    return false;
}

void TipComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, kMSGAttackDamage);
    
    Component::cleanupMessages();
}

void TipComponent::onAttackDamage(yhge::Message* message)
{
    CCInteger* damageValue=static_cast<CCInteger*>(message->getData());
    if (damageValue) {
        
        CCString* damageString=CCString::createWithFormat("-%d",damageValue->getValue());
        
        //show damage tip
        CCLabelBMFont* label=CCLabelBMFont::create(damageString->getCString(), "fonts/Red_36.fnt");
        
        CCSize size=m_rendererComponent->getSpriteRenderer()->getContentSize();
        CCPoint pos=m_rendererComponent->getRenderer()->getPosition();
        
//        CCLOG("size:%f,%f",size.width,size.height);
//        label->setPosition(ccp(pos.x,pos.y+size.height+50));
        
        float scale=m_rendererComponent->getRenderer()->getScale();
        
        label->setAlignment(kCCTextAlignmentCenter);
        
        label->setPosition(ccp(pos.x+size.width/(2*scale)-18,pos.y+size.height*scale));
        
//        label->setScale(1.5/scale);
        
        //action
        CCAction* effect=CCSequence::createWithTwoActions(CCMoveBy::create(0.4f, ccp(0,40.0f)), CCRemoveSelf::create());
        
        //和renderer在一个结点。如果renderer移动，则显示会跟着移动，看起来真些。
//        m_rendererComponent->getRenderer()->getParent()->addChild(label,1000);
//        m_rendererComponent->getRenderer()->addChild(label,1000);
        if (m_container) {
            m_container->addChild(label);
        }
        
        label->runAction(effect);
    }
}


NS_CC_GE_END

