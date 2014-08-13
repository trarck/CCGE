#include "VisibleMoveComponent.h"
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

VisibleMoveComponent::VisibleMoveComponent()
:Component("VisibleMoveComponent")
,m_walkVelocity(CCPointZero)
,m_position(CCPointZero)
,m_battleProperty(NULL)
,m_unitProperty(NULL)
,m_moveComponent(NULL)
,m_rendererComponent(NULL)
,m_tick(-1)
,m_moving(false)
{
    
}

VisibleMoveComponent::~VisibleMoveComponent()
{

}

void VisibleMoveComponent::setup()
{
    Component::setup();

    m_moveComponent=static_cast<MoveComponent*>(m_owner->getComponent("MoveComponent"));
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
    
    GameEntity* entity=static_cast<GameEntity*>(m_owner);
    
    m_battleProperty=entity->getBattleProperty();
    
    m_unitProperty=entity->getUnitProperty();
    
    //for test
    m_walkVelocity=ccp(70, 0);
}

void VisibleMoveComponent::cleanup()
{
    Component::cleanup();
    m_moveComponent=NULL;
    m_rendererComponent=NULL;
}

bool VisibleMoveComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, MSG_MOVE_TO, NULL,message_selector(VisibleMoveComponent::onMoveTo),this);
        messageManager->registerReceiver(m_owner, MSG_MOVE_STOP, NULL,message_selector(VisibleMoveComponent::onMoveStop),this);
        return true;
    }
    
    return false;
}

void VisibleMoveComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, MSG_MOVE_TO, NULL,message_selector(VisibleMoveComponent::onMoveTo),this);
    
    messageManager->removeReceiver(m_owner, MSG_MOVE_STOP, NULL,message_selector(VisibleMoveComponent::onMoveStop),this);
    
    Component::cleanupMessages();
}

void VisibleMoveComponent::update(float delta)
{
    if (m_tick!=Game::getInstance()->getEngine()->getBattleUpdateManager()->getTicks()) {
        
        syncProperty();
        
    }else{
        m_position.x+=m_walkVelocity.x*delta;
        m_position.y+=m_walkVelocity.y*delta;
    }
    
    m_rendererComponent->getRenderer()->setPosition(m_position);
}


void VisibleMoveComponent::syncProperty()
{
    m_tick=Game::getInstance()->getEngine()->getBattleUpdateManager()->getTicks();
    
    m_walkVelocity=m_moveComponent->getWalkVelocity();
    m_position.x=m_battleProperty->getX();
    m_position.y=m_battleProperty->getY();
}

void VisibleMoveComponent::startMove()
{
    syncProperty();

    m_rendererComponent->getRenderer()->setPosition(m_position);
    
    //改变角色动作
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_MOVE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
    
    int direction=m_walkVelocity.x;//*m_battleProperty->getCamp();
    
    //改变人物朝向
    if(m_rendererComponent)
        m_rendererComponent->getSpriteRenderer()->setFlipX(direction<0);
    
    if(!m_moving){
        CCLOG("startMove[%p]",this);
        Game::getInstance()->getEngine()->getUpdateManager()->addUpdater(this, schedule_selector(VisibleMoveComponent::update),kRendererMoveUpdate);
        m_moving=true;
    }
}

void VisibleMoveComponent::stopMove()
{
    if (m_moving) {
        CCLOG("stopMove[%p]",this);
        Game::getInstance()->getEngine()->getUpdateManager()->removeUpdater(this);
        m_moving=false;
    }
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
}

void VisibleMoveComponent::onMoveTo(yhge::Message* message)
{
    //clac direction
    startMove();
}

void VisibleMoveComponent::onMoveStop(yhge::Message* message)
{
    stopMove();
}

NS_CC_GE_END

