#include "BattleState.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


void BattleIdleState::enter()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_ATTACK, NULL,
                                     message_selector(BattleIdleState::onAttack),this);
    
    messageManager->registerReceiver(m_gameEntity, MSG_BEATTACK, NULL,
                                     message_selector(BattleIdleState::onBeAttack),this);

    //显示空闲动画
    showIdleAnimation();
}

void BattleIdleState::exit()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_ATTACK,message_selector(BattleIdleState::onAttack));
    messageManager->removeReceiver(m_gameEntity, MSG_BEATTACK,message_selector(BattleIdleState::onBeAttack));
}

void BattleIdleState::update(float delta)
{
    
}

void BattleIdleState::onMessage(yhge::Message* message)
{
    int msg=message->getType();
    
    CCLOG("BattleIdleState msg:%d",msg);
}

void BattleIdleState::onAttack(yhge::Message* message)
{
    Entity* target= static_cast<Entity*>(message->getData());
    if(target){
        m_gameEntity->getAttackComponent()->setTarget(target);
    }
    
    //change state to move
    
    BattleMoveState* state=static_cast<BattleMoveState*>(m_fSMMachine->getState(kMoveState));
    state->setMoveType(BattleMoveState::kMoveToTarget);
    m_fSMMachine->changeState(state);
}

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

void BattleAttackState::enter()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE, NULL, message_selector(BattleAttackState::onAttackAnimationComplete),this);
    
    //显示攻击动画
    showAttackAnimation();
}

void BattleAttackState::exit()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_ANIMATION_COMPLETE,message_selector(BattleAttackState::onAttackAnimationComplete));
}

void BattleAttackState::onAttackAnimationComplete(yhge::Message* message)
{
    m_gameEntity->getAttackComponent()->parseTargetDamage();
    
    //改变到移回去状态
    BattleMoveState* state=static_cast<BattleMoveState*>(m_fSMMachine->getState(kMoveState));
    state->setMoveType(BattleMoveState::kMoveBack);
    m_fSMMachine->changeState(state);
}

void BattleAttackState::showAttackAnimation()
{
    m_gameEntity->getAttackComponent()->showAttackAnimation();
}

void BattleBeAttackState::enter()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    
    messageManager->registerReceiver(m_gameEntity, MSG_BEATTACK_FINISH, NULL,
                                     message_selector(BattleBeAttackState::onBeAttackFinish),this);
    
    showBeAttackAnimation();
    
}

void BattleBeAttackState::exit()
{
    yhge::MessageManager* messageManager=Game::getInstance()->getMessageManager();
    messageManager->removeReceiver(m_gameEntity, MSG_BEATTACK_FINISH,message_selector(BattleBeAttackState::onBeAttackFinish));
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
