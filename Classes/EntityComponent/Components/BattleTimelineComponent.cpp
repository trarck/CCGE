#include "BattleTimelineComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

BattleTimelineComponent::BattleTimelineComponent()
:m_rendererComponent(NULL)
,Component("BattleTimelineComponent")
{
    
}

BattleTimelineComponent::~BattleTimelineComponent()
{
}

void BattleTimelineComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
    
}

void BattleTimelineComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool BattleTimelineComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGAttackDamage, NULL,
                                         message_selector(BattleTimelineComponent::onAttackDamage),this);
        
        return true;
    }
    return false;
}

void BattleTimelineComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(messageManager->getGlobalObject(), kMSGAttackDamage, m_owner);
    
    Component::cleanupMessages();
}

void BattleTimelineComponent::onAttackDamage(yhge::Message* message)
{
    
    CCInteger* damageValue=static_cast<CCInteger*>(message->getData());
    if (damageValue) {
        
        CCString* damageString=CCString::createWithFormat("-%d",damageValue->getValue());
        
        //show damage tip
        CCLabelBMFont* label=CCLabelBMFont::create(damageString->getCString(), "fonts/Red_36.fnt");
        
        CCSize size=m_rendererComponent->getRenderer()->getContentSize();
        CCPoint pos=CCPointZero;//m_rendererComponent->getRenderer()->getPosition();
        
//        label->setPosition(ccp(pos.x,pos.y+size.height+50));
        
        float scale=m_rendererComponent->getRenderer()->getScale();
        
        label->setPosition(ccp(size.width/(2*scale),pos.y+(size.height/scale)+40));
        
        label->setScale(1/scale);
        
        //action
        CCAction* effect=CCSequence::createWithTwoActions(CCMoveBy::create(0.4f, ccp(0,40.0f)), CCRemoveSelf::create());
        
        //和renderer在一个结点。如果renderer移动，则显示会跟着移动，看起来真些。
//        m_rendererComponent->getRenderer()->getParent()->addChild(label,1000);
        m_rendererComponent->getRenderer()->addChild(label,1000);
        
        label->runAction(effect);
    }
}


NS_CC_GE_END

