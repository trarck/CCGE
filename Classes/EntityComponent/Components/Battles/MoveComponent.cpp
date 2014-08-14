#include "MoveComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MoveComponent::MoveComponent()
:GameComponent("MoveComponent")
,m_moveable(false)
,m_direction(CCPointZero)
{
    
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::setup()
{
    GameComponent::setup();

}

void MoveComponent::cleanup()
{
    GameComponent::cleanup();
}

bool MoveComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(MoveComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void MoveComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void MoveComponent::update(float delta)
{
    BattleProperty* battleProperty=m_entityOwner->getBattleProperty();
    
    CCPoint pos=battleProperty->getPosition();
    
    CCPoint walkVelocity=battleProperty->getWalkVelocity();
    
    pos.x+=walkVelocity.x*delta;
    pos.y+=walkVelocity.y*delta;
    
    battleProperty->setPosition(pos);
}

void MoveComponent::moveTo(const CCPoint& dest)
{
    CCPoint pos=m_entityOwner->getBattleProperty()->getPosition();
    
    pos=ccpSub(dest, pos);
    
    if (pos.x==0 and pos.y==0) {
        m_entityOwner->getBattleProperty()->setWalkVelocity(CCPointZero);
    }else{
        pos=ccpNormalize(pos);
        m_entityOwner->getBattleProperty()->setWalkVelocity(ccpMult(pos, m_entityOwner->getUnitProperty()->getWalkSpeed()));
    }
    
    if(!m_moveable){
        Game::getInstance()->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(m_owner->m_uID, this, schedule_selector(MoveComponent::update),kMoveUpdate);
        m_moveable=true;
    }
}

void MoveComponent::stopMove()
{
    m_entityOwner->getBattleProperty()->setWalkVelocity(CCPointZero);
    if (m_moveable) {
        Game::getInstance()->getEngine()->getBattleUpdateManager()->removeUpdaterFromGroup(m_owner->m_uID, this);
        m_moveable=false;
    }
}

NS_CC_GE_END

