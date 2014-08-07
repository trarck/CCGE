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
:Component("MoveComponent")
,m_walkVelocity(CCPointZero)
,m_knockupVelocity(CCPointZero)
,m_moveable(false)
,m_direction(CCPointZero)
,m_battleProperty(NULL)
,m_unitProperty(NULL)
,m_positionComponent(NULL)
,m_rendererComponent(NULL)
{
    
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::setup()
{
    Component::setup();

    GameEntity* entity=static_cast<GameEntity*>(m_owner);
    
    m_battleProperty=entity->getBattleProperty();
    m_unitProperty=entity->getUnitProperty();
    
    //for test
    m_walkVelocity=ccp(70, 0);
}

void MoveComponent::cleanup()
{
    Component::cleanup();
    m_positionComponent=NULL;
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

    float x=m_battleProperty->getX();
    float y=m_battleProperty->getY();
    
    x+=m_walkVelocity.x*delta;
    y+=m_walkVelocity.y*delta;
    
    m_battleProperty->setX(x);
    m_battleProperty->setY(y);
}

void MoveComponent::moveTo(const CCPoint& dest)
{
    CCPoint pos=ccp(m_battleProperty->getX(),m_battleProperty->getY());
    
    pos=ccpSub(dest, pos);
    
    pos=ccpNormalize(pos);
    
    m_walkVelocity=ccpMult(pos, m_unitProperty->getWalkSpeed());
    
    Game::getInstance()->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(m_owner->m_uID, this, schedule_selector(MoveComponent::update),kMoveUpdate);
}

void MoveComponent::stopMove()
{
    m_walkVelocity=CCPointZero;
    
    Game::getInstance()->getEngine()->getBattleUpdateManager()->removeUpdaterFromGroup(m_owner->m_uID, this);
}

NS_CC_GE_END

