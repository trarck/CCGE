#include "AIComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

AIComponent::AIComponent()
:Component("AIComponent")
,m_state(0)
,m_target(NULL)
,m_destination(NULL)
,m_moveComponent(NULL)
{
    
}

AIComponent::~AIComponent()
{
    CC_SAFE_RELEASE_NULL(m_target);
    CC_SAFE_RELEASE_NULL(m_destination);
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
    
    GameEntity* target=searchTarget();
    if (target) {
        setTarget(target);
        
        //work to target
        walkTo(target);
        
        
    }else if(m_destination){
        walkTo(m_destination);
    }else{
        //idle
        
    }
    
    
    
//    if (m_state==0) {
//        walkTo(ccp(600,0));
//        m_state=1;
//    }else if(m_state==1){
//        m_temp+=delta;
//        if (m_temp>6) {
//            walkStop();
//            m_temp=0;
//            m_state=2;
//        }
//    }else if(m_state==2){
//        m_temp+=delta;
//        if (m_temp>3) {
//            walkTo(ccp(0,0));
//            m_temp=0;
//            m_state=3;
//        }
//    }else if(m_state==3){
//        m_temp+=delta;
//        if (m_temp>6) {
//            walkStop();
//            m_temp=0;
//            m_state=0;
//        }
//    }
}

GameEntity* AIComponent::searchTarget()
{
    GameEntity* owner=static_cast<GameEntity*>(m_owner);
    
    BattleManager* battleManager=Game::getInstance()->getEngine()->getBattleManager();
    
    std::map<int, GameEntityVector > aliveUnits=battleManager->getAliveUnits();
    
    int oppCamp=-owner->getBattleProperty()->getCamp();
    
    GameEntityVector unitList=aliveUnits[oppCamp];
    


    CCPoint pos=owner->getBattleProperty()->getPosition();
    
    CCPoint oppPos;
    GameEntity* entity=NULL;
    GameEntity* target=NULL;

    float minDistanSQ=MAXFLOAT;
    float distanceSQ=0;
    
    for (GameEntityVector::iterator iter=unitList.begin(); iter!=unitList.end(); ++iter) {
        
        entity=*iter;
        //TODO use buff property checkable
        if (entity!=m_owner) {
            oppPos=entity->getBattleProperty()->getPosition();
            
            distanceSQ=ccpDistanceSQ(pos, oppPos);
            if(minDistanSQ>distanceSQ){
                minDistanSQ=distanceSQ;
                target=entity;
            }
        }
    }
    
    return target;
}

void AIComponent::walkTo(GameEntity* dest)
{
    CCPoint destPos=dest->getBattleProperty()->getPosition();
    walkTo(destPos);
}

void AIComponent::walkTo(const CCPoint& dest)
{
    GameEntity* owner=static_cast<GameEntity*>(m_owner);
    
    BattleProperty* battleProperty=owner->getBattleProperty();
    
    CCPoint pos=battleProperty->getPosition();
    
    float attackRange=battleProperty->getAttackRange();
    float distanceSQ=(pos-dest).getLengthSq();
//    CCLOG("dis[%d]:%f,%f,%f:%f,%f",m_uID,dest.x,pos.x,dest.x-pos.x,distanceSQ,attackRange*attackRange);
    if (distanceSQ<=attackRange*attackRange) {
        //TODO idle state
        walkStop();
        return;
    }
    
    m_moveComponent->moveTo(dest);
    this->getMessageManager()->dispatchMessage(MSG_MOVE_TO, this, m_owner,CCPointValue::create(dest));
}

void AIComponent::walkStop()
{
    m_moveComponent->stopMove();
    this->getMessageManager()->dispatchMessage(MSG_MOVE_STOP, this, m_owner);
}

void AIComponent::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

inline void AIComponent::setDestination(GameEntity* destination)
{
    CC_SAFE_RETAIN(destination);
    CC_SAFE_RELEASE(m_destination);
    m_destination = destination;
}

NS_CC_GE_END

