#include "BattleState.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


void BattleState::enter()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_ATTACK, NULL,
                                     message_selector(BattleState::onAttack),this);
}

void BattleState::exit()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_ATTACK,message_selector(BattleState::onAttack));

}

void BattleState::onAttack(yhge::Message* message)
{
    Entity* target= static_cast<Entity*>(message->getData());
    if(target){
        CCLOG("onAttack:target[%d]",target->m_uID);
        
        m_gameEntity->getAttackComponent()->setTarget(target);
        
        //change state to move
        BattleMoveState* state=static_cast<BattleMoveState*>(m_fSMMachine->getState(kMoveState));
        state->setMoveType(BattleMoveState::kMoveToTarget);
        m_fSMMachine->changeState(state);
    }
    //没有目标，什么都不做。
    
}

//是否可以被普通攻击
bool BattleState::isAttackable()
{
    return true;
}

//是否可以被技能攻击
bool BattleState::isSkillAttackable()
{
    return true;
}

bool BattleState::isNormalDamageable()
{
    return true;
}

void BattleIdleState::enter()
{
    CCLOG("BattleIdleState enter:[%d]",m_gameEntity->m_uID);
    BattleState::enter();
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_BEATTACK, NULL,
                                     message_selector(BattleIdleState::onBeAttack),this);

    //显示空闲动画
    showIdleAnimation();
}

void BattleIdleState::exit()
{
    CCLOG("BattleIdleState exit:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();

    messageManager->removeReceiver(m_gameEntity, MSG_BEATTACK,message_selector(BattleIdleState::onBeAttack));
    
    BattleState::exit();
}

void BattleIdleState::update(float delta)
{
    
}

void BattleIdleState::onMessage(yhge::Message* message)
{
    int msg=message->getType();
    
    CCLOG("BattleIdleState msg:%d",msg);
}

//void BattleIdleState::onAttack(yhge::Message* message)
//{
//    Entity* target= static_cast<Entity*>(message->getData());
//    if(target){
//        m_gameEntity->getAttackComponent()->setTarget(target);
//    }
//    
//    //change state to move
//    
//    BattleMoveState* state=static_cast<BattleMoveState*>(m_fSMMachine->getState(kMoveState));
//    state->setMoveType(BattleMoveState::kMoveToTarget);
//    m_fSMMachine->changeState(state);
//}

void BattleIdleState::onBeAttack(yhge::Message* message)
{
    //change state to beattack
    m_fSMMachine->changeState(kBeAttackState);
}

void BattleIdleState::showIdleAnimation()
{
    m_gameEntity->getAttackComponent()->showIdleAnimation();
}


void BattleMoveState::enter()
{
    CCLOG("BattleMoveState enter:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, kMSGBattleMoveComplete, NULL,
                                     message_selector(BattleMoveState::onMoveComplete),this);
    
    if (m_moveType==kMoveToTarget) {
        m_gameEntity->getAttackComponent()->moveToTargetFront();
    }else{
        m_gameEntity->getAttackComponent()->moveBackOrigin();
    }
}

void BattleMoveState::exit()
{
    CCLOG("BattleMoveState exit:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, kMSGBattleMoveComplete,message_selector(BattleMoveState::onMoveComplete));
}

void BattleMoveState::update(float delta)
{
    
}

void BattleMoveState::onMoveComplete(yhge::Message* message)
{
    if (m_moveType==kMoveToTarget) {
        m_fSMMachine->changeState(kAttackState);
    }else{
        m_fSMMachine->changeState(kIdleState);
    }
}


bool BattleMoveState::isAttackable()
{
    return false;
}

bool BattleMoveState::isNormalDamageable()
{
    return false;
}

void BattleAttackState::enter()
{
    CCLOG("BattleAttackState enter:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE, NULL, message_selector(BattleAttackState::onAttackAnimationComplete),this);
    
    //显示攻击动画
    showAttackAnimation();
    
    //处理伤害
    m_gameEntity->getAttackComponent()->parseTargetDamage();
}

void BattleAttackState::exit()
{
    CCLOG("BattleAttackState exit:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE,message_selector(BattleAttackState::onAttackAnimationComplete));
}

void BattleAttackState::onAttackAnimationComplete(yhge::Message* message)
{
//    m_gameEntity->getAttackComponent()->parseTargetDamage();
    
    //改变到移回去状态
    BattleMoveState* state=static_cast<BattleMoveState*>(m_fSMMachine->getState(kMoveState));
    state->setMoveType(BattleMoveState::kMoveBack);
    m_fSMMachine->changeState(state);
}

void BattleAttackState::showAttackAnimation()
{
    m_gameEntity->getAttackComponent()->showAttackAnimation();
}

//是否可以被普通攻击.正在普通攻击中不能被攻击。
bool BattleAttackState::isAttackable()
{
    return false;
}

bool BattleAttackState::isNormalDamageable()
{
    return false;
}

void BattleBeAttackState::enter()
{
 
    CCLOG("BattleBeAttackState enter:[%d]",m_gameEntity->m_uID);
    
    BattleState::enter();
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_BEATTACK_FINISH, NULL,
                                     message_selector(BattleBeAttackState::onBeAttackFinish),this);
    
    showBeAttackAnimation();
    
}

void BattleBeAttackState::exit()
{
    CCLOG("BattleBeAttackState exit:[%d]",m_gameEntity->m_uID);
    
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_BEATTACK_FINISH,message_selector(BattleBeAttackState::onBeAttackFinish));
    
    BattleState::exit();
}

void BattleBeAttackState::onBeAttackFinish(yhge::Message* message)
{
    //被攻击完成
    //恢复到攻击前的状态
    m_fSMMachine->changeToLastState();
}

void BattleBeAttackState::showBeAttackAnimation()
{
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_BEATTACK), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    
    //目标做被攻击动画
    Game::getInstance()->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, m_gameEntity, data);
    
    data->release();
}

NS_CC_GE_END
