#include "UnitState.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


void UnitIdleState::enter()
{
    CCLOG("UnitIdleState enter:[%d]",m_gameEntity->m_uID);
    UnitState::enter();

    //显示空闲动画
    showIdleAnimation();
    
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

void UnitIdleState::showIdleAnimation()
{
//    m_gameEntity->getAttackComponent()->showIdleAnimation();
}


void UnitWalkState::enter()
{
    CCLOG("UnitMoveState enter:[%d]",m_gameEntity->m_uID);

}

void UnitWalkState::exit()
{
    CCLOG("UnitMoveState exit:[%d]",m_gameEntity->m_uID);
}

void UnitWalkState::update(float delta)
{
    
}

void UnitAttackState::enter()
{
    CCLOG("UnitAttackState enter:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE, NULL, message_selector(UnitAttackState::onAttackAnimationComplete),this);
    
    //显示攻击动画
    showAttackAnimation();
    
    //处理伤害
//    m_gameEntity->getAttackComponent()->parseTargetDamage();
    
    //check update
    //if have ai update then remove
}

void UnitAttackState::exit()
{
    CCLOG("UnitAttackState exit:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE,message_selector(UnitAttackState::onAttackAnimationComplete));
}

void UnitAttackState::onAttackAnimationComplete(yhge::Message* message)
{

}

void UnitAttackState::showAttackAnimation()
{
    
}

//是否可以被普通攻击.正在普通攻击中不能被攻击。
bool UnitAttackState::isAttackable()
{
    return false;
}

bool UnitAttackState::isNormalDamageable()
{
    return false;
}

void UnitHurtState::enter()
{
 
    CCLOG("UnitBeAttackState enter:[%d]",m_gameEntity->m_uID);
    
    UnitState::enter();
    
    showHurtAnimation();
    
}

void UnitHurtState::exit()
{
    CCLOG("UnitBeAttackState exit:[%d]",m_gameEntity->m_uID);
    
    UnitState::exit();
}

void UnitHurtState::showHurtAnimation()
{
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_BEATTACK), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    
    //目标做被攻击动画
    Game::getInstance()->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, m_gameEntity, data);
    
    data->release();
}

NS_CC_GE_END
