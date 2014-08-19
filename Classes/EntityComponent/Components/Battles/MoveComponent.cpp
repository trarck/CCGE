#include "MoveComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/Properties/UnitProperty.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MoveComponent::MoveComponent()
:GameComponent("MoveComponent")
,m_moveable(false)
,m_moveProperty(NULL)
{
    
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::setup()
{
    GameComponent::setup();

    m_moveProperty=static_cast<MoveProperty*>(m_owner->getProperty(CCGE_PROPERTY_MOVE));
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
    CCPoint pos=m_moveProperty->getPosition();
    
    CCPoint walkVelocity=m_moveProperty->getWalkVelocity();
    
    CCPoint knockupVeclocity=m_moveProperty->getKnockupVelocity();
    
    CCPoint velocity=walkVelocity+knockupVeclocity;
    
    bool moveable=true;
    
    //计算人物朝向
    int direction=0;
    if (moveable && velocity.x !=0 ) {
        direction = velocity.x>0?1:(velocity.x<0?-1:0);
    }else if (false){
        //check skill direction
    }
    
    int originDir=m_moveProperty->getDirection();
    
    if (0 > direction * originDir ) {
        m_moveProperty->setDirection(originDir * -1);
    }
    
    //检查被打飞时间
    float knockupTime=m_moveProperty->getKnockupTime();
    if(knockupTime>0){
        knockupTime-=delta;
        if (knockupTime<=0) {
            m_moveProperty->setKnockupVelocity(CCPointZero);
        }
    }
    
    //检查是否超出舞台
    if ((pos.x > kStageRect.getMaxX()-kStageSideDistanceX && 0< velocity.x) ||
        (pos.x < kStageRect.getMinX()+kStageSideDistanceX && 0> velocity.x)) {
        velocity.x=0;
    }
    
    m_moveProperty->setVelocity(velocity);
    
    //更新位置
    pos.x+=velocity.x*delta;
    pos.y+=velocity.y*delta;
    m_moveProperty->setPosition(pos);
    
    //TODO fix each unit between distance
    
}

void MoveComponent::moveTo(const CCPoint& dest)
{
    CCPoint pos=m_moveProperty->getPosition();
    
    pos=ccpSub(dest, pos);
    
    if (pos.x==0 and pos.y==0) {
        m_moveProperty->setWalkVelocity(CCPointZero);
    }else{
        
        UnitProperty* unitProperty=static_cast<UnitProperty*>(m_owner->getProperty(CCGE_PROPERTY_UNIT));
        
        pos=ccpNormalize(pos);
        m_moveProperty->setWalkVelocity(ccpMult(pos,unitProperty->getWalkSpeedFromInfo()));
    }
}

void MoveComponent::stopMove()
{
    m_moveProperty->setWalkVelocity(CCPointZero);
}

NS_CC_GE_END

