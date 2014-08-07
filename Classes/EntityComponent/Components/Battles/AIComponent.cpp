#include "AIComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

AIComponent::AIComponent()
:Component("AIComponent")
,m_temp(0)
,m_state(0)
{
    
}

AIComponent::~AIComponent()
{

}

void AIComponent::setup()
{
    Component::setup();
    
    m_moveComponent=static_cast<MoveComponent*>(m_owner->getComponent("MoveComponent"));

}

void AIComponent::cleanup()
{
    Component::cleanup();
}

bool AIComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(AIComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void AIComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void AIComponent::update(float delta)
{
//    CCLOG("AIComponent::update:%d,%f",this,delta);
    
    if (m_state==0) {
        walkTo(ccp(600,0));
        m_state=1;
    }else if(m_state==1){
        m_temp+=delta;
        if (m_temp>6) {
            walkStop();
            m_temp=0;
            m_state=2;
        }
    }else if(m_state==2){
        m_temp+=delta;
        if (m_temp>3) {
            walkTo(ccp(0,0));
            m_temp=0;
            m_state=3;
        }
    }else if(m_state==3){
        m_temp+=delta;
        if (m_temp>6) {
            walkStop();
            m_temp=0;
            m_state=0;
        }
    }
}

void AIComponent::searchTarget()
{
    
}

void AIComponent::walkTo(const CCPoint& dest)
{
    m_moveComponent->moveTo(dest);
    this->getMessageManager()->dispatchMessage(MSG_MOVE_TO, this, m_owner,CCPointValue::create(dest));
}

void AIComponent::walkStop()
{
    m_moveComponent->stopMove();
    this->getMessageManager()->dispatchMessage(MSG_MOVE_STOP, this, m_owner);
}

NS_CC_GE_END

