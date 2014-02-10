#include "GameAttackComponent.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameAttackComponent::GameAttackComponent()
{
    
}

GameAttackComponent::~GameAttackComponent()
{
    CC_SAFE_RELEASE_NULL(m_target);
}
//
//bool GameAttackComponent::init()
//{
//    return true;
//}

bool GameAttackComponent::registerMessages()
{
    if(AttackComponent::registerMessages()){
    
//        yhge::MessageManager* messageManager=this->getMessageManager();
//        
//        messageManager->registerReceiver(m_owner, MSG_SET_ATTACK_TARGET, NULL, message_selector(GameAttackComponent::onSetAttackTarget),this);
//        
//        messageManager->registerReceiver(m_owner, MSG_ATTACK, NULL, message_selector(GameAttackComponent::onAttack),this);
//        
        return true;
    }
    return false;
}

void GameAttackComponent::cleanupMessages()
{
    
    AttackComponent::cleanupMessages();
}

void GameAttackComponent::attack()
{
    if(m_target){
        CCLOG("GameAttackComponent::startAttack");
        int targetHp=10;//m_target->getHealth();
        CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
//        m_target->setHealth(targetHp-1);
    }else {
        CCLOG("GameAttackComponent::startAttack no target");
    }
}

void GameAttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

/**
 * 处理攻击消息
 */
void GameAttackComponent::onAttack(Message *message)
{
    CCObject* target=message->getData();
    if(target){
        setTarget(target);
    }
    attack();
}

/**
 * 处理设置目标消息
 */
void GameAttackComponent::onSetAttackTarget(Message *message)
{
    CCObject* target=message->getData();
    
    this->getMessageManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(GameAttackComponent::onTargetDie));
    setTarget(target);
    this->getMessageManager()->registerReceiver(this, MSG_TARGET_DIE, m_target, message_selector(GameAttackComponent::onTargetDie));
}

/**
 * 处理目标死亡消息
 */
void GameAttackComponent::onTargetDie(Message *message)
{
    CCLOG("target is die");
    this->getMessageManager()->removeReceiver(this, MSG_TARGET_DIE, m_target, message_selector(GameAttackComponent::onTargetDie));
    CC_SAFE_RELEASE(m_target);
    m_target=NULL;
}

NS_CC_GE_END

