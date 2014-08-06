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
,m_positionComponent(NULL)
,m_walkVelocity(CCPointZero)
,m_knockupVelocity(CCPointZero)
,m_battleProperty(NULL)
,m_unitProperty(NULL)
,m_moveable(false)
,m_moveDirection(0)
,m_rendererComponent(NULL)
{
    
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::setup()
{
    Component::setup();

    m_positionComponent=static_cast<SimplePositionComponent*>(m_owner->getComponent("PositionComponent"));
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
    
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
//    CCLOG("MoveComponent::update");

//    if (m_moveable) {
        CCPoint pos=m_positionComponent->getPosition();
        
        pos.x+=(m_walkVelocity.x+m_knockupVelocity.x)*delta*m_moveDirection;
        pos.y+=(m_walkVelocity.y+m_knockupVelocity.y)*delta*m_moveDirection;
    
        m_positionComponent->setPosition(pos);
//    }
}

void MoveComponent::tinyUpdate(float delta)
{
    CCPoint pos=m_positionComponent->getPosition();
    
    pos.x+=(m_walkVelocity.x+m_knockupVelocity.x)*delta*m_moveDirection;
    pos.y+=(m_walkVelocity.y+m_knockupVelocity.y)*delta*m_moveDirection;
    
    m_positionComponent->setPosition(pos);
}

void MoveComponent::startMove(int direction)
{
    m_moveDirection=direction;
    
    //改变角色动作
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
    
    //改变人物朝向
    if(m_rendererComponent)
        m_rendererComponent->getSpriteRenderer()->setFlipX(direction<0);
    
    Game::getInstance()->getEngine()->getBattleUpdateManager()->addUpdaterToGroup(m_owner->m_uID, this, schedule_selector(MoveComponent::update),kMoveUpdate);
}

void MoveComponent::stopMove()
{
    Game::getInstance()->getEngine()->getBattleUpdateManager()->removeUpdaterFromGroup(m_owner->m_uID, this);
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
}

NS_CC_GE_END

