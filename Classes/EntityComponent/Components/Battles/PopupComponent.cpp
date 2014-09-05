#include "PopupComponent.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

PopupComponent::PopupComponent()
:Component("PopupComponent")
,m_container(NULL)
,m_rendererComponent(NULL)
{
    
}

PopupComponent::~PopupComponent()
{
    CC_SAFE_RELEASE_NULL(m_container);
}

void PopupComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void PopupComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool PopupComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGAttackDamage, NULL,
                                         message_selector(PopupComponent::onAttackDamage),this);
        
        messageManager->registerReceiver(m_owner, kMSGBattlePopup, NULL,
                                         message_selector(PopupComponent::onBattlePopup),this);
        
        return true;
    }
    return false;
}

void PopupComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, kMSGAttackDamage);
    messageManager->removeReceiver(m_owner, kMSGBattlePopup);
    
    Component::cleanupMessages();
}

void PopupComponent::showPopup(const std::string& text,const std::string& color,int style,bool crit)
{
    //TODO use queue
    
    CCNode* labelNode=NULL;
    
    //TODO use color font
    if (style==kBattlePopupTypeText) {
        CCLabelTTF* label=CCLabelTTF::create(text.c_str(), "", 32);
        labelNode=label;
    }else{
        CCLabelBMFont* label=CCLabelBMFont::create(text.c_str(), "fonts/Red_36.fnt");
        label->setAlignment(kCCTextAlignmentCenter);
        labelNode=label;
    }
    
    CCSize size=m_rendererComponent->getSpriteRenderer()->getContentSize();
    CCPoint pos=m_rendererComponent->getRenderer()->getPosition();
    
    float scale=m_rendererComponent->getRenderer()->getScale();
    
    
    labelNode->setPosition(ccp(pos.x+size.width/(2*scale)-18,pos.y+size.height*scale));
    
    //action
    CCAction* effect=CCSequence::createWithTwoActions(CCMoveBy::create(0.4f, ccp(0,40.0f)), CCRemoveSelf::create());
    
    if (m_container) {
        m_container->addChild(labelNode);
    }
    labelNode->runAction(effect);
}

void PopupComponent::onAttackDamage(yhge::Message* message)
{
    CCInteger* damageValue=static_cast<CCInteger*>(message->getData());
    if (damageValue) {
        
        CCString* damageString=CCString::createWithFormat("-%d",damageValue->getValue());
        
        showPopup(damageString->getCString(), "red",kBattlePopupTypeDamage);
    }
}

void PopupComponent::onBattlePopup(yhge::Message* message)
{
    CCDictionary* data=message->getDictionary();
    CCString* text=static_cast<CCString*>(data->objectForKey("text"));
    CCString* color=static_cast<CCString*>(data->objectForKey("color"));
    

    int type=kBattlePopupTypeDamage;
    bool crit=false;
    
    CCInteger* typeValue=static_cast<CCInteger*>(data->objectForKey("type"));
    if (typeValue) {
        type=typeValue->getValue();
    }
    
    CCBool* critValue=static_cast<CCBool*>(data->objectForKey("crit"));
    if (critValue) {
        crit=critValue->getValue();
    }
    
    showPopup(text->getCString(), color->getCString(), type,crit);
    
}


NS_CC_GE_END

