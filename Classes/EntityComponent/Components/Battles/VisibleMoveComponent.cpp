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
:GameComponent("VisibleMoveComponent")
,m_velocity(CCPointZero)
,m_position(CCPointZero)
,m_rendererComponent(NULL)
,m_tick(-1)
,m_moving(false)
,m_direction(0)
,m_moveProperty(NULL)
{
    
}

VisibleMoveComponent::~VisibleMoveComponent()
{

}

void VisibleMoveComponent::setup()
{
    GameComponent::setup();
    m_moveProperty=static_cast<MoveProperty*>(m_owner->getProperty(CCGE_PROPERTY_MOVE));
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void VisibleMoveComponent::cleanup()
{
    if (m_moving) {
        Game::getInstance()->getEngine()->getUpdateManager()->removeUpdater(this);
    }
    
    GameComponent::cleanup();
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
        m_position.x+=m_velocity.x*delta;
        m_position.y+=m_velocity.y*delta;
    }
    
    m_rendererComponent->getRenderer()->setPosition(m_position);
}


void VisibleMoveComponent::syncProperty()
{
    m_tick=Game::getInstance()->getEngine()->getBattleUpdateManager()->getTicks();
    
    m_direction=m_moveProperty->getDirection();
    m_velocity=m_moveProperty->getVelocity();
    m_position=m_moveProperty->getPosition();
    
//    CCLOG("syncProperty[%p]:%f,%f",this,m_velocity.x,m_velocity.y);
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
    
    //改变人物朝向
    if(m_rendererComponent)
        m_rendererComponent->getSpriteRenderer()->setFlipX(m_direction<0);
    
    if(!m_moving){
        CCLOG("startMove[%p]:%f,%f",this,m_velocity.x,m_velocity.y);
                
        Game::getInstance()->getEngine()->getUpdateManager()->addUpdater(this, schedule_selector(VisibleMoveComponent::update),kVisibleMoveUpdate);
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

