#include "UnitState.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "Consts/PropertyDefine.h"

#include "EntityComponent/Properties/UnitProperty.h"
#include "EntityComponent/Properties/BattleProperty.h"
#include "EntityComponent/Properties/MoveProperty.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

UnitState::UnitState()
:m_target(NULL)
{
    
}

UnitState::~UnitState()
{
    CC_SAFE_RELEASE_NULL(m_target);
}

void UnitState::update(float delta)
{
    //lookup target to attack
    GameEntity* target=searchTarget();
    if (target) {
        setTarget(target);
        SkillComponent* skill=findSkillToCast();
        
        if (skill){
            //transitive to attack state
            
            UnitAttackState* attackState=static_cast<UnitAttackState*>(m_fSMMachine->getState(kAttackState));
            attackState->setTarget(target);
            attackState->setSkill(skill);
            
            m_fSMMachine->changeState(attackState);
        }else{
            walkTo(target);
        }
    }else{
        m_fSMMachine->changeState(kIdleState);
    }
}

void UnitState::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

void UnitState::setUnitAction(const std::string& action)
{
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(action), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_gameEntity,data);
}


GameEntity* UnitState::searchTarget()
{
    return NULL;
}

SkillComponent* UnitState::findSkillToCast()
{
    return NULL;
}


void UnitState::walkTo(GameEntity* dest)
{
    MoveProperty* moveProperty=static_cast<MoveProperty*>(dest->getProperty(CCGE_PROPERTY_MOVE));
    CCPoint destPos=moveProperty->getPosition();
    walkTo(destPos);
}

void UnitState::walkTo(const CCPoint& dest)
{
    MoveProperty* moveProperty=static_cast<MoveProperty*>(m_gameEntity->getProperty(CCGE_PROPERTY_MOVE));
    CCPoint pos=moveProperty->getPosition();
    
    UnitProperty* unitProperty=static_cast<UnitProperty*>(m_gameEntity->getProperty(CCGE_PROPERTY_UNIT));
    
    float attackRange=unitProperty->getAttackRange();
    float distanceSQ=(pos-dest).getLengthSq();
    //    CCLOG("dis[%d]:%f,%f,%f:%f,%f",m_uID,dest.x,pos.x,dest.x-pos.x,distanceSQ,attackRange*attackRange);
    if (distanceSQ<=attackRange*attackRange) {
        //transitive to idle state
        m_fSMMachine->changeState(kIdleState);
        return;
    }
    
    //transitive to move state
    UnitWalkState* walkState=static_cast<UnitWalkState*>(m_fSMMachine->getState(kWalkState));
    walkState->setDest(dest);
    m_fSMMachine->changeState(walkState);
}

void UnitIdleState::enter()
{
    CCLOG("UnitIdleState enter:[%d]",m_gameEntity->m_uID);
    UnitState::enter();

    //clear walk speed
    MoveProperty* moveProperty=static_cast<MoveProperty*>(m_gameEntity->getProperty(CCGE_PROPERTY_MOVE));
    moveProperty->setWalkVelocity(CCPointZero);
    
    //显示空闲动画
    setUnitAction(CCGE_ANIMATION_IDLE);
    
    //check update
    //if not ai update then add
}

void UnitIdleState::exit()
{
    CCLOG("UnitIdleState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}

void UnitIdleState::update(float delta)
{
    UnitState::update(delta);
}

void UnitIdleState::onMessage(yhge::Message* message)
{
    int msg=message->getType();
    
    CCLOG("UnitIdleState msg:%d",msg);
}

void UnitIdleState::onHurt(yhge::Message* message)
{
    //change state to beattack
    m_fSMMachine->changeState(kHurtState);
}

void UnitWalkState::enter()
{
    CCLOG("UnitMoveState enter:[%d]",m_gameEntity->m_uID);
    UnitState::enter();
    
    MoveComponent* moveComponent=static_cast<MoveComponent*>(m_gameEntity->getComponent("MoveComponent"));
    moveComponent->moveTo(m_dest);
    
    Game::getInstance()->getMessageManager()->dispatchMessage(MSG_MOVE_TO, this, m_gameEntity,CCPointValue::create(m_dest));
    
    setUnitAction(CCGE_ANIMATION_MOVE);
}

void UnitWalkState::exit()
{
    CCLOG("UnitMoveState exit:[%d]",m_gameEntity->m_uID);
}

void UnitAttackState::enter()
{
    CCLOG("UnitAttackState enter:[%d]",m_gameEntity->m_uID);

    UnitState::enter();
    
    //clear walk speed
    MoveProperty* moveProperty=static_cast<MoveProperty*>(m_gameEntity->getProperty(CCGE_PROPERTY_MOVE));
    moveProperty->setWalkVelocity(CCPointZero);
    
    m_skill->start(m_target);
    
}

void UnitAttackState::exit()
{
    CCLOG("UnitAttackState exit:[%d]",m_gameEntity->m_uID);

    UnitState::exit();
}

void UnitHurtState::enter()
{
    CCLOG("UnitBeAttackState enter:[%d]",m_gameEntity->m_uID);
    
    UnitState::enter();
    
    //interrupt skill
    
    //interrupt sound
    
    //clear walk speed
    MoveProperty* moveProperty=static_cast<MoveProperty*>(m_gameEntity->getProperty(CCGE_PROPERTY_MOVE));
    moveProperty->setWalkVelocity(CCPointZero);
    
    setUnitAction(CCGE_ANIMATION_BEATTACK);
    
}

void UnitHurtState::exit()
{
    CCLOG("UnitBeAttackState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}

void UnitDeadState::enter()
{
    
    CCLOG("UnitDeadState enter:[%d]",m_gameEntity->m_uID);
    
    UnitState::enter();
    
    setUnitAction(CCGE_ANIMATION_BEATTACK);
    
}

void UnitDeadState::exit()
{
    CCLOG("UnitDeadState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}


void UnitBirthState::enter()
{
    
    CCLOG("UnitBirthState enter:[%d]",m_gameEntity->m_uID);
    
    UnitState::enter();
    
    setUnitAction(CCGE_ANIMATION_BIRTH);
    
}

void UnitBirthState::exit()
{
    CCLOG("UnitBirthState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}

void UnitDyingState::enter()
{
    
    CCLOG("UnitDyingState enter:[%d]",m_gameEntity->m_uID);
    
    UnitState::enter();
    
    setUnitAction(CCGE_ANIMATION_BEATTACK);
    
}

void UnitDyingState::exit()
{
    CCLOG("UnitBeAttackState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}

NS_CC_GE_END
