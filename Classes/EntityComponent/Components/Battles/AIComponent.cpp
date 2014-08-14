#include "AIComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

AIComponent::AIComponent()
:GameComponent("AIComponent")
,m_state(0)
,m_target(NULL)
//,m_destination(NULL)
,m_moveComponent(NULL)
,m_willCastManualSkill(true)
{
    
}

AIComponent::~AIComponent()
{
    CC_SAFE_RELEASE_NULL(m_target);
//    CC_SAFE_RELEASE_NULL(m_destination);
}

void AIComponent::setup()
{
    GameComponent::setup();
    m_moveComponent=static_cast<MoveComponent*>(m_owner->getComponent("MoveComponent"));

}

void AIComponent::cleanup()
{
    GameComponent::cleanup();
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
    CCAssert(m_entityOwner!=NULL, "AIComponent::update owner is null");
    
    //减少公司cd时间
    m_entityOwner->getBattleProperty()->addGlobalCd(-delta);
    
    GameEntity* target=searchTarget();
    if (target) {
        setTarget(target);
        
        SkillComponent* skill=findSkillToCast();
        if (skill) {
            //TODO cast skill
            walkStop();
            
            skill->cast(target);
            
        }else{
            //work to target
            walkTo(target);
        }
        
//    }else if(m_destination){
//        walkTo(m_destination);
    }else{
        //idle
        
    }
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

SkillComponent* AIComponent::findSkillToCast()
{
    GameEntity* owner=static_cast<GameEntity*>(m_owner);
    
//    CCLOG("gcd:%f",owner->getBattleProperty()->getGlobalCd());
    //如果技能公用cd没结束，则不能施放技能
    if (owner->getBattleProperty()->getGlobalCd()>0) {
        return NULL;
    }
    
    std::vector<SkillComponent*> skills=owner->getSkillComponents();
    
    SkillComponent* skill=NULL;
    
    for(std::vector<SkillComponent*>::iterator iter=skills.begin();iter!=skills.end();++iter){
        skill=*iter;
        if (skill->isUpdate() && (m_willCastManualSkill || !skill->isManual())) {
            
            bool cast=skill->canCastWithTarget(m_target);
            
            if (cast && skill->willCast()) {
                return skill;
            }
        }
    }
    
    return NULL;
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

//inline void AIComponent::setDestination(GameEntity* destination)
//{
//    CC_SAFE_RETAIN(destination);
//    CC_SAFE_RELEASE(m_destination);
//    m_destination = destination;
//}

NS_CC_GE_END

